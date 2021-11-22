#include <iostream>
#include <string>
#include <cstdlib>
//greatest common divisor

long long GCD(long a,long b) {
	long best = 0;
	for (int i = 0; i < (a + b); i++) {
		if (a % i == 0 && b % i == 0) {
			best = i;
		}
	}
	return best;
}

int main()
{
std::cout << GCD(rand() % 10000 + 1000,rand()%10000 +1000)
}


