#include "stdafx.h"
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;
mutex my_mutex;
const int carSize = 4;
int people;
#define P 10

void Nothing()
{
	do
	{
		int nothing = 12;
	} while (people != 0);
}

bool Car(int id)
{
	lock_guard<mutex>guard(my_mutex);
	if (people < carSize)
	{
		people++;
		cout << id << " " << "I'm ready\n";
		return true;
	}
	else
	{
		cout << id << " " << "I'm not ready\n";
		return false;
	}
}

void Attraction(int id)
{
	for (int i = 0; i < 10; i++)
	{
		if (Car(id))
			Nothing();

		if (people == carSize)
		{
			people = 0;
			cout << "Car has arrived\n";
		}
	}
}

int main()
{
	thread *passengers[P];

	for (int i = 0; i < P; i++)
	{
		passengers[i] = new thread(Attraction, i);
	}

	for (int i = 0; i < P; i++)
	{
		passengers[i]->join();
	}
	return 0;
}

