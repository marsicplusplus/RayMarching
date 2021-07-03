CC=g++
SRC_DIR=src
INC=-Iinc
CFLAGS=-Wall -lpthread -O6

BUILD_DIR=build
OUT=marcher

#${OUT}: ${BUILD_DIR}/main.o ${BUILD_DIR}/ray.o ${BUILD_DIR}/world.o ${BUILD_DIR}/shader.o ${BUILD_DIR}/gpu_renderer.o
${OUT}: ${BUILD_DIR}/main.o ${BUILD_DIR}/ray.o ${BUILD_DIR}/world.o ${BUILD_DIR}/cpu_renderer.o ${BUILD_DIR}/job_system.o
	@mkdir -p ${BUILD_DIR}
	${CC} -o${BUILD_DIR}/${OUT} $^ ${CFLAGS} ${INC}

${BUILD_DIR}/job_system.o: ${SRC_DIR}/CPURenderer/job_system.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) -c -o$@ $< ${CFLAGS} ${INC}

${BUILD_DIR}/main.o: ${SRC_DIR}/main.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) -c -o$@ $< ${CFLAGS} ${INC}

${BUILD_DIR}/ray.o: ${SRC_DIR}/ray.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) -c -o$@ $< ${CFLAGS} ${INC}

#${BUILD_DIR}/shader.o: ${SRC_DIR}/shader.cpp
	#@mkdir -p ${BUILD_DIR}
	#$(CC) -c -o$@ $< ${CFLAGS} ${INC}

#${BUILD_DIR}/gpu_renderer.o: ${SRC_DIR}/gpu_renderer.cpp
	#@mkdir -p ${BUILD_DIR}
	#$(CC) -c -o$@ $< ${CFLAGS} ${INC}

${BUILD_DIR}/cpu_renderer.o: ${SRC_DIR}/cpu_renderer.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) -c -o$@ $< ${CFLAGS} ${INC}


${BUILD_DIR}/world.o: ${SRC_DIR}/world.cpp
	@mkdir -p ${BUILD_DIR}
	$(CC) -c -o$@ $< ${CFLAGS} ${INC}

clean:
	@rm ${BUILD_DIR}/* 
