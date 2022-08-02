#pragma once
#include <vector>

class Fibonachi
{
	std::vector<int> numbers;

	Fibonachi();

	static Fibonachi& get()
	{
		static Fibonachi instance;
		return instance;
	}

	void calculate(int number);
	int number(int index);

public:
	static int at(int number);
};