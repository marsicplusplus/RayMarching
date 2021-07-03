#include "CPURenderer/job_system.hpp"
#include <iostream>

static int counter = 0;

JobManager::JobManager(int nW, int workGroup) : nWorkers(nW), workGroup(workGroup), done(false){
	std::cout << "Max threads: " << nWorkers << std::endl;
}

void JobManager::init() {
	done = false;
	for(int i = 0; i < nWorkers; ++i){
		threads.push_back(std::thread(&JobManager::doWork, this, i));
	}
}

void JobManager::join(){
	done = true;
	cv.notify_all();
	for (auto& thread : threads) {
		if (thread.joinable()) {
			thread.join();
		}
	}
}

void JobManager::doWork(int id){
	while(true){
		std::shared_ptr<IJob> job = nullptr;
		{
			std::unique_lock<std::mutex> g(qMutex);
			cv.wait(g, [&]{ return !queue.empty() || done; });
			if(!queue.empty()){
				job = queue.front();
				queue.pop();
			}
			if(done && queue.empty()) break;
		}
		if(job != nullptr) {
			job->start();
		}
	}
}

void JobManager::submit(std::shared_ptr<IJob> job) {
	counter++;
	std::lock_guard<std::mutex> g(qMutex);
	queue.push(job);
	cv.notify_one();
}
