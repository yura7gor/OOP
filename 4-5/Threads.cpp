#include "Threads.h"
#include <chrono>

MultiThread::MultiThread(short thCount, std::ifstream &in, std::string &outName) :
	fileInput(in), outputName(outName), mode (work)
	
	
{
	fileOutput.open(outputName);
	short MAX_THREAD_COUNT = std::thread::hardware_concurrency();
	if (thCount > MAX_THREAD_COUNT)
	{
		std::cerr << "Your entered count of threads is too huge, it will be only " << MAX_THREAD_COUNT << " threads created\n";
		threadCount = MAX_THREAD_COUNT;
	}
	else
		threadCount = thCount;
}

MultiThread::~MultiThread()
{
	if (fileInput.is_open())
		fileInput.close();
	std::exit(0);
}


void MultiThread::control()
{
	std::string cmd;
	while (true)
	{
		std::cin >> cmd;
		if (cmd == "exit")
		{
			off();
			std::cout << "exit was writed\n";
		}
		if (cmd == "pause")
		{
			pause();
			std::cout << "was paused\n";
		}
		if (cmd == "resume")
		{
			resume();
			std::cout << "was resumed\n";
		}
	}
}

void MultiThread::startControlThread()
{
	std::thread ctrl(&MultiThread::control, this);
	ctrl.detach();
}

auto MultiThread::startDiffThread()
{
	ParseDig classForParall;
	while (fileInput.is_open() && mode != stoped)
	{
		std::unique_lock<std::mutex> input_File(input_File_mutex);
		uint64_t x;
		if (fileInput >> x)
		{
			input_File.unlock();
			classForParall.clear();
			classForParall.decompose(x);
			std::unique_lock<std::mutex> output_File(output_File_mutex);
			while (mode == paused)
			{
				cond_var.wait(output_File);
			}
			fileOutput << classForParall.short_print();
			output_File.unlock();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else
		{
			fileInput.close();
			input_File.unlock();
		}
	}
	
}

void MultiThread::startThreads()
{
	startControlThread();
	for (int i = 0; i < threadCount; i++)
	{
		threads.push_back(std::thread(&MultiThread::startDiffThread, this));
		std::cout << i << "started\n";
	}
	threadsJoin();
}

void MultiThread::threadsJoin()
{
	for (auto i = threads.begin(); i < threads.end(); i++)
		i->join();
}

void MultiThread::off()
{
	mode = stoped;
	if (fileInput.is_open())
		fileInput.close();
	cond_var.notify_all();
}

void MultiThread::pause()
{
	mode = paused;
	std::unique_lock<std::mutex> output_File(output_File_mutex);
	fileOutput.close();
	output_File.unlock();
}

void MultiThread::resume()
{
	fileOutput.open(outputName, std::ios::app);
	mode = work;
	cond_var.notify_all();
	std::cout << "all threads were woke up \n";
}
