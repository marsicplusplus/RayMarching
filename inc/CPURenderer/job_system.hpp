#ifndef __JOB_SYSTEM_HPP__
#define __JOB_SYSTEM_HPP__

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

struct IJob {
	virtual void start() = 0;
};

class JobManager {
	public:
		int nWorkers;
		int workGroup;
		bool done;

	public:
		JobManager(int nWorkers, int workGroup);
		void init();
		void submit(std::shared_ptr<IJob> job);
		void join();

	private:
		void doWork(int id);

		std::queue<std::shared_ptr<IJob>> queue;
		std::vector<std::thread> threads;
		std::mutex qMutex;
		std::condition_variable cv;
		std::condition_variable emptyCv;
};

#endif
