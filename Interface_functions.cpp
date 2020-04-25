#include "Interface_functions.h"

void clearConsole()
{
	pressAnyKeyToContinue();
	//#ifdef _WIN64
	std::system("cls");
	//#else
		//std::system("clear");
	//#endif
}

void pressAnyKeyToContinue()
{
	system("pause");
}


void printTitel()
{
	std::cout << "________________________________________________________________________________________________\n";
	std::cout << " _____         _            _____                         \n";
	std::cout << "|  __ \\       | |          / ____|                        \n";
	std::cout << "| |__) | ___  | |_  __ _  | |  __   __ _  _ __ ___    ___ \n";
	std::cout << "|  _  / / _ \\ | __|/ _` | | | |_ | / _` || '_ ` _ \\  / _ \\\n";
	std::cout << "| | \\ \\| (_) || |_| (_| | | |__| || (_| || | | | | ||  __/\n";
	std::cout << "|_|  \\_\\\\___/  \\__|\\__,_|  \\_____| \\__,_||_| |_| |_| \\___|\n";
	std::cout << "________________________________________________________________________________________________\n\n";
}