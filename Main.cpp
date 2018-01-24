#include "Threads.h"

void main(int argc, char* argv[])
{
	std::ifstream in(argv[1]);
	std::ofstream out(argv[2]);
	MultiThread multi(3, in, std::string(argv[2]));
	multi.startThreads();
	multi.threadsJoin();
	if (in.is_open())
		in.close();
	if (out.is_open())
		out.close();
	std::thread th1(testFunc);
	std::thread th2(testFunc1);
	std::cout << "number of thread is" << th1.get_id();
	th1.join();	
	th2.join();
	std::cout << std::thread::hardware_concurrency() << "\n";
	std::cout << "number of thread is" << th1.get_id();
	
}
