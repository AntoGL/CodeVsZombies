#include "pch.h"
#include "Fibonachi.h"

Fibonachi::Fibonachi()
{
	numbers = { 0, 1, 1, 2, 3, 5, 8, 13 };
}

void Fibonachi::calculate(const int index)
{
	const int prev1 = number(index - 1);
	const int prev2 = number(index - 2);
	numbers.push_back(prev1 + prev2);
}

int Fibonachi::number(const int index)
{
	if (index >= static_cast<int>(numbers.size()))
		calculate(index);

	return numbers[index];
}

int Fibonachi::at(const int number)
{
	return get().number(number - 1);
}