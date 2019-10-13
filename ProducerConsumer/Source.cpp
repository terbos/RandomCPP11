#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <string>
#include <chrono>
#include <condition_variable>
#include <list>

int main()
{
	std::deque<std::string> messages;
	std::mutex mut;
	std::condition_variable cv;

	std::thread producer([&cv](std::mutex& mut, std::deque<std::string>& messages){
		std::string msg{ "Hello" };
		int cnt{ 0 };
		for (;cnt < 10;){
			msg += std::to_string(cnt++);
			{
				std::lock_guard<std::mutex> lock(mut);
				messages.push_back(msg);
			}
			cv.notify_one();
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}

	}, std::ref(mut), std::ref(messages));

	std::thread consumer([&cv](std::mutex& mut, std::deque<std::string>& messages){
		//	std::string msg{ "" };
		std::list<std::string> received;
		//for (size_t i = 0;i < 10; ++i){
		for (;;)
		{
			{
				std::unique_lock<std::mutex> lock(mut);
				cv.wait(lock, [&messages]() {return !messages.empty(); });
				//if (std::cv_status::no_timeout == cv.wait_for(lock, std::chrono::seconds(1)))
				{while (!messages.empty()){
					received.push_back(messages.front());
					messages.pop_front();
					//}
				}
				}
				for (auto msg : received)
				{
					std::cout << msg << std::endl;
				}
				received.clear();
			}
		}}, std::ref(mut), std::ref(messages));

	producer.join();
	consumer.join();
	return 0;
}