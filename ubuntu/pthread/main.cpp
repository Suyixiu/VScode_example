#include "add.h"
#include "sub.h"
#include <iostream>
#include <pthread.h>
#include <windows.h>

using namespace std;

void *printf_sub(void *args)
{
	for (int i = 0; i < 10; i++)
	{
		Sleep(1000);
		cout << "  " << sub(9, 6) << endl;
	}
	return 0;
}

void *printf_add(void *args)
{
	for (int i = 0; i < 10; i++)
	{
		Sleep(1000);
		cout << "  " << add(6, 6) << endl;
	}
	return 0;
}

int main()
{
	pthread_t sub_thread;
	pthread_t add_thread;
	pthread_create(&sub_thread, NULL, printf_sub, NULL);
	pthread_create(&add_thread, NULL, printf_add, NULL);
	pthread_exit(NULL);
	system("pause");
	return 0;
}
