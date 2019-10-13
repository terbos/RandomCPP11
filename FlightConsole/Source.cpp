#include <iostream>
#include <string>
#include <locale>
#include <memory>
#include <iterator>
#include <algorithm>
#include <vector>
#include "DiagnosticCount.h"
#include "PassengerDetails.h"
//using namespace std;

class SilverPassengerDetails : public PassengerDetails
{
public:
	~SilverPassengerDetails()
	{
		std::cout << "Destroying SilverPassengerDetails!" << std::endl;
	}

	auto input() -> void override;
	auto output(std::ostream& os) const->std::ostream& override;
};
//auto inputPassengerDetails(PassengerDetails& pd) -> void;
//auto outputPassengerDetails(const PassengerDetails& pd) -> void;
auto inputPassengerDetails(std::string& name, int& weight) -> void;
auto outputPassengerDetails(const std::string& name, const int& weight) -> void;

class AClass :private DiagnosticCount<AClass>
{};

int main()
{
	createObject();
	AClass ac1, ac2;
	//PassengerDetails pdOneParam("Hello");
	//std::string name;
	//auto weight = 0;
	//int override = 23;

	std::string opt;
	auto exit = false;
	enum class Option { Input = 'i', Silver = 's', Find='f', Output = 'o', All = 'a', Exit = 'x' };
	std::shared_ptr<PassengerDetails> pd = nullptr;// new PassengerDetails();
	const int MAXPASSENGERS = 5;
	std::vector<std::shared_ptr<PassengerDetails>> details;
	size_t cnt(0);
	do
	{
		std::cout << "i - input\no - output\na - all\nx - exit" << std::endl;
		std::cout << "Please enter an option:" << std::endl;
		std::cin >> opt;
		std::locale loc;
		auto option = std::tolower(opt[0], loc);
		Option eOpt = static_cast<Option>(option);
		switch (eOpt)
		{
		case Option::Input:
			try
			{
				pd = std::shared_ptr<PassengerDetails>(new PassengerDetails());
				pd->input();
				//details[cnt++] = pd;
				details.push_back(pd);
			}
			catch (const std::bad_alloc& ba)
			{
				std::cout << "Real problem: " << ba.what() << std::endl;
			}
			break;
		case Option::Silver:
			pd = std::shared_ptr<PassengerDetails>(new SilverPassengerDetails());
			pd->input();
			//details[cnt++] = pd;
			details.push_back(pd);
			break;
		case Option::Find:
		{
			std::string n;
			std::cout << "Please enter a name to find:";
			std::cin >> n;
			auto found = std::find_if(std::cbegin(details), std::cend(details),
				[n](const std::shared_ptr<PassengerDetails>& p)  {
				return p->getName() == n;
			});
			if (found != std::cend(details))
			{
				std::cout << "Found: ";
				(*found)->output(std::cout);
			}
		}
			break;
		case Option::All:
			for (size_t i = 0; i < cnt; i++)
			{
				//details[i]->output(std::cout);
				std::cout << *details[i];
			}
			{
			std::ostream_iterator<std::shared_ptr<PassengerDetails> > osit(std::cout, "\n");
			std::copy(std::cbegin(details), std::cend(details), osit);
			}
			break;
		case Option::Output:
			if (pd)
			{
				//pd->output(std::cout);
				std::cout << *pd;
			}
			break;
		case Option::Exit:
			exit = true;
			break;
		default:
			std::cout << "Invalid option, please try again!" << std::endl;
			break;
		}

	} while (!exit);

	/*for (size_t i = 0; i < cnt; i++)
	{
	delete details[i];
	}*/

	return 0;
}
auto SilverPassengerDetails::input() -> void
{
	std::cout << "Silver Club Passenger:" << std::endl;
	PassengerDetails::input();
}
auto SilverPassengerDetails::output(std::ostream& os) const -> std::ostream&
{
	os << "Silver Club Passenger:" << std::endl;
	return PassengerDetails::output(os);
}

auto PassengerDetails::input() -> void
{
	std::cout << "Please enter passenger name:" << std::endl;
	std::cin >> name;
	std::cout << "Please enter baggage weight:" << std::endl;
	std::cin >> this->weight;
}

auto PassengerDetails::output(std::ostream& os) const -> std::ostream&
{
	os << "Name: " << name << std::endl;
	return os << "Baggage weight: " << weight << std::endl;
}

auto inputPassengerDetails(std::string& name, int& weight) -> void
{
	std::cout << "Please enter passenger name:" << std::endl;
	std::cin >> name;
	std::cout << "Please enter baggage weight:" << std::endl;
	std::cin >> weight;
}
auto outputPassengerDetails(const std::string& name, const int& weight) -> void
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Baggage weight: " << weight << std::endl;
}
