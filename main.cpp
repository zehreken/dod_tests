#include <iostream>
#include <time.h>
#include <stack>

const int CLUTTER_SIZE = 255;

class Big
{
	private:
		int actor; // 32b primitive type
		int clutter[CLUTTER_SIZE]; // (1KB - 32b) Size of big is exactly 1KB
	public:
		void setActor(int size);
		int getActor();
		float getSizeInKB();
		float getSizeInMB();
		void fillClutter();
};

void Big::setActor(int actor)
{
	this->actor = actor;
}

int Big::getActor()
{
	return this->actor;
}

float Big::getSizeInKB()
{
	return sizeof(Big) / 1024.f;
}

float Big::getSizeInMB()
{
	return sizeof(Big) / (1024.f * 1024.f);
}

void Big::fillClutter()
{
	for (int i = 0; i < 255; i++)
	{
		this->clutter[i] = 0xffffffff;
	}
}

class Small
{
	private:
		int actor;
	public:
		void setActor(int size);
		int getActor();
		float getSizeInKB();
		float getSizeInMB();
};

void Small::setActor(int actor)
{
	this->actor = actor;
}

int Small::getActor()
{
	return this->actor;
}

float Small::getSizeInKB()
{
	return sizeof(Small) / 1024.f;
}

float Small::getSizeInMB()
{
	return sizeof(Small) / (1024.f * 1024.f);
}

using namespace std;

float createAndLoopBigs(int size)
{
	Big* bigs = new Big[size];
	cout << "Address of bigs: " << bigs << endl;

	for (int i = 0; i < size; i++)
	{
		bigs[i].fillClutter();
	}

	clock_t t1, t2;
	t1 = clock();
	for (int i = 0; i < size; i++)
	{
		bigs[i].setActor(i);
	}
	t2 = clock();
	float time = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;

	return time;
}

float createAndLoopSmalls(int size)
{
	Small* smalls = new Small[size];
	cout << "Address of smalls: " << smalls << endl;

	clock_t t1, t2;
	t1 = clock();
	for (int i = 0; i < size; i++)
	{
		smalls[i].setActor(i);
	}
	t2 = clock();
	float time = ((float)t2 - (float)t1) / CLOCKS_PER_SEC;

	return time;
}

int main()
{
	const int SIZE = 50000;
	const int NUMBER_OF_TRIES = 100;
	float sum;
	for (int i = 0; i < NUMBER_OF_TRIES; i++)
	{
		sum += createAndLoopBigs(SIZE) / createAndLoopSmalls(SIZE);
	}

	// Big big;
	// cout << "Size of Big(KB): " << big.getSizeInKB() << endl;
	cout << "Average: " << sum / NUMBER_OF_TRIES << endl;

	return 0;
}
