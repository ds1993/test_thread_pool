.all: test

test:
	g++ -o test Condition.cpp CThread.cpp main.cpp Task.cpp ThreadPool.cpp -lpthread --std=c++11

clean:
	rm -rf test
