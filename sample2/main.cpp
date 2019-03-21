#include "add.h"
#include "sub.h"
#include <iostream>
#include <pthread.h>
#include <windows.h>

using namespace std;


void* say_hello(void* args)
{
	for(int i = 0; i < 10; i++)
    {
        Sleep(1000);
        cout << "hello!" << endl;
    }
	return 0;
}

void* say_hi(void* args)
{
	for (int i = 0; i < 10; i++)
    {
        Sleep(1000);
		cout << "hi!" << endl;
    }
	return 0;
}

int main()
{
	pthread_t say_hello_thread;
	pthread_t say_hi_thread;
	pthread_create(&say_hello_thread, NULL, say_hello, NULL);
	pthread_create(&say_hi_thread, NULL, say_hi, NULL);
	pthread_exit(NULL);
	system("pause");
	return 0;
}
