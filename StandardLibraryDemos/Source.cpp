#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int toNumber(int a, int b, int c)
{
	return a + 10 * b + 100 * c;
}
struct FunctorToNumber
{
	int operator()(int a, int b, int c){ return a + 10 * b + 100 * c;	}
};

int main()
{
	{
		std::function<int(int)> fact =
			[&fact](int a) ->
			int { return a == 0 ? 1 : a*fact(a - 1); };


	}
	{
		auto fun = [](int n) -> bool{ return n < 10; };
		int n = 0;
		int m = 50;
		std::vector<int> data{ 2, 4, 56, 6, 6, 7, 326543, 65, 3, 55, 347 };
		std::cin >> n;
		auto small = std::count_if(std::cbegin(data), std::cend(data),
			[&n,m](int a) -> bool{ n = 42;
			return a < m; });
		std::cout << "Less: " << small << std::endl;
		std::cout << "n: " << n << std::endl;
	}{
		int n = 0;
		std::vector<int> data{ 2, 4, 56, 6, 6, 7, 326543, 65, 3, 55, 347 };
		std::cin >> n;
		auto small = std::count_if(std::cbegin(data), std::cend(data),
			std::bind(std::less<int>(), std::placeholders::_1, n));
		std::cout << "Less: " << small << std::endl;
	}
	{
		std::cout << toNumber(1, 2, 3) << std::endl;
		std::cout << "bind: " << std::bind(toNumber,
			std::placeholders::_3,
			std::placeholders::_2,
			std::placeholders::_1)(1, 2, 3) << std::endl;

		std::cout << FunctorToNumber()(1, 2, 3) << std::endl;
		std::cout << "bind: " << std::bind(FunctorToNumber(),
			std::placeholders::_3,
			std::placeholders::_2,
			std::placeholders::_1)(1, 2, 3) << std::endl;
	}

	return 0;
}