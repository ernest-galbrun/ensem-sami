#include "interface.h"

int main(int argc, char* argv[])

{
	void* p;
	LaunchKhepera(2,2,"10.10.10.1","20.20.20.20",&p);
	return 0;
}