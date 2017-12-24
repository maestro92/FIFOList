#include <iostream>
#include "FIFOList.cpp"

using namespace std;

void test_wrap_around()
{
	FifoList<int> queueList = FifoList<int>();
	queueList.push(1);
	queueList.push(2);
	queueList.push(3);
	queueList.push(4);
	queueList.push(5);
	queueList.push(6);

	queueList.print();

	queueList.pop();
	queueList.pop();
	queueList.pop();

	queueList.push(7);
	queueList.push(8);
	queueList.push(9);

	queueList.print();
}


void test_push_and_resize()
{
	FifoList<int> queueList = FifoList<int>();

	queueList.push(1);
	queueList.push(2);
	queueList.push(3);
	queueList.push(4);
	queueList.push(5);
	queueList.push(6);

	queueList.print();

	queueList.pop();
	queueList.pop();
	queueList.pop();

	queueList.print();

	queueList.push(7);
	queueList.push(8);
	queueList.push(9);
	queueList.push(10);
	queueList.push(11);
	queueList.push(12);
	queueList.push(13);
	queueList.print();
}


void test_over_pop()
{
	FifoList<int> queueList = FifoList<int>();
	queueList.push(1);
	queueList.push(2);
	queueList.push(3);
	queueList.print();
	for (int i = 0; i < 4; i++)
	{
		queueList.pop();
	}
}

int main(int argc, char *argv[])
{
	cout << "		********* test_wrap_around *********" << endl;
	test_wrap_around();

	cout << "		********* test_push_and_resize *********" << endl;
	test_push_and_resize();

	cout << "		********* test_over_pop *********" << endl;
	test_over_pop();

	while (1)
	{}

	return 0;

}