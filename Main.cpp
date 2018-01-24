#include "Threads.h"


void main(int argc, char* argv[])
{
	std::ifstream in(argv[1]);
	
	MultiThread multi(3, in, std::string(argv[2]));
	multi.startThreads();
	
	if (in.is_open())
		in.close();
}
