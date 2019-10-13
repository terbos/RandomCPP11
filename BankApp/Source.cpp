#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <thread>
#include <chrono>
#include <mutex>
#include <atomic>
class Bank
{
	static std::atomic<int> _totalBalance;
public:
	static void modifyTotal(int n){_totalBalance.fetch_add(n); }
	static int getTotal() { return _totalBalance; }
};
class Account
{
	int _balance = 0;
	std::mutex *_mut;
public:
	Account() :_mut(new std::mutex()){}
	int getBalance() { return _balance; }
	void deposit(int n){
		if (n > 0){
			std::lock_guard<std::mutex> lock(*_mut);
			int temp = _balance ;
			temp += n;
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			_balance = temp;
			Bank::modifyTotal(n);
		}
	}
	void withdraw(int n){
		if (n > 0){
			std::lock_guard<std::mutex> lock(*_mut);
			int temp = _balance;
			temp -= n;
			std::this_thread::sleep_for(std::chrono::microseconds(1));
			_balance = temp;
			Bank::modifyTotal(-n);
		}
	}
};
class Teller
{
	std::vector<Account>& _accounts;
public:
	Teller(std::vector<Account>& accounts) :_accounts(accounts){}
	void work()
	{
		for (auto& acc : _accounts)
		{
			for (size_t i = 0; i < 100; i++)
			{
				acc.deposit(100);
				acc.withdraw(50);
			}
		}
	}
};
std::atomic<int> Bank::_totalBalance= 0;
int main()
{
	std::vector<Account> accounts(10);
	std::vector<Teller> tellers;
	for (size_t i = 0; i < 10; i++)
	{
		tellers.push_back(Teller(accounts));
	}
	std::thread th1([&tellers](){
		tellers[1].work();
	});
	std::thread th2([&tellers](){
		tellers[2].work();
	});
	std::thread th3([&tellers](){
		tellers[3].work();
	});
	std::thread th4([&tellers](){
		tellers[4].work();
	});
	std::thread th5([&tellers](){
		tellers[5].work();
	});
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();

	int total = std::accumulate(std::cbegin(accounts), std::cend(accounts), 0, [](int a, Account b) { return a + b.getBalance(); });
	std::cout << "Total from Accounts: " << total << std::endl;
	std::cout << "Total from Bank: " << Bank::getTotal() << std::endl;

	return 0;
}