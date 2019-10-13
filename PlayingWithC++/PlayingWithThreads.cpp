#include <iostream>
#include <thread>
#include <chrono>

int main()
{
	{
		int result = 0;
		std::thread square([](int a, int& result)-> void{
			result = 0;
			for (size_t i = 0; i < a; i++)
			{
				result += a;
				std::this_thread::sleep_for(std::chrono::microseconds(2));
				}
			std::cout << "Inner: " << result << std::endl;
		},7,std::ref(result));
		//std::cout << "Square: " << result << std::endl;
		//std::this_thread::sleep_for(std::chrono::microseconds(2));
		//std::cout << "Square: " << result << std::endl;
		//std::this_thread::sleep_for(std::chrono::microseconds(2));
		//std::cout << "Square: " << result << std::endl;
		square.join();

		std::cout << "Square: " << result << std::endl;
	}
	{
	auto start = std::chrono::system_clock::now();

	std::thread th1([](int val) -> void{
		std::cout << "Secondary thread id: " << std::this_thread::get_id() << std::endl;
		for (size_t i = 0; i < val; i++)
		{
			std::cout << "One: " << i << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(2));
		}
		//std::cout << std::endl;
	}, 5);
	std::thread th2([](int val) -> void{
		std::cout << "Secondary thread id: " << std::this_thread::get_id() << std::endl;
		for (size_t i = 0; i < val; i++)
		{
			std::cout << "Two: " << val - i - 1 << std::endl;
			std::this_thread::sleep_for(std::chrono::microseconds(2));
		}
		std::cout << std::endl;
	}, 5);

	th1.join();
	th2.join();
	std::cout << "Main thread id: " << std::this_thread::get_id() << std::endl;
	auto end = std::chrono::system_clock::now();
}
	return 0;
}