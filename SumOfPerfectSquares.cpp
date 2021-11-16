// Exercises.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <map>
#include <vector>
#include <math.h>

int main()
{
	std::vector<int> numList{ 0,0,0,0,0 };
	std::vector<int> perfectSquares;
	
	int chosenNumber,sum = 0;

	std::cin >> chosenNumber;

	for (int i = 0; i <= chosenNumber; i++) { if (sqrt(i) == (int)sqrt(i)) { perfectSquares.push_back(i); } };

	for (auto& num : numList) 
	{
		for (auto& squares : perfectSquares) 
		{
			if (squares + sum <= chosenNumber)
			{
				num = squares;
			}
		}
		sum += num;
		std::cout << num << " + ";
	}
}