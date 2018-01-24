#pragma once
#include <string>
#include "ParseDig.h"
#include <thread>
#include <mutex>
#include <condition_variable>

enum mode { stoped = 0, paused, work };

class MultiThread
{
	std::string outputName;
	std::ifstream &fileInput;
	std::ofstream fileOutput;
	short threadCount;
	std::vector<std::thread> threads;
	std::mutex input_File_mutex;
	std::mutex output_File_mutex;
	void MultiThread::control();
	void startControlThread();
	std::condition_variable cond_var;
	int mode;

public:
	MultiThread(short, std::ifstream &, std::string &);
	~MultiThread();
	void startThreads();
	auto startDiffThread();
	void threadsJoin();
	void off();
	void pause();
	void resume();
	
};
