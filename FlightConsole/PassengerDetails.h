#pragma once
#ifndef PASSENGERDETAILS_H
#define PASSENGERDETAILS_H

class PassengerDetails : private DiagnosticCount<PassengerDetails>
{
	std::string name = "";
	int weight = 0;
public:
	std::string getName() const { return name; }
	PassengerDetails(const std::string& n, const int& w) :name(n), weight(w)
	{
	}
	explicit PassengerDetails(const std::string& n) :PassengerDetails(n, 0)
	{
		//name = "body";
		//weight = 12;
	}
	PassengerDetails() :PassengerDetails("delegating", 0)
	{
		//name = "body";
		//weight = 12;
	}
	virtual ~PassengerDetails() _NOEXCEPT
	{
		std::cout << "Destroying PassengerDetails!" << std::endl;
	}
	virtual auto input() -> void;
	virtual auto output(std::ostream& os)const->std::ostream&;
};
inline std::ostream& operator<<(std::ostream& os, const PassengerDetails& pd)
{
	return pd.output(os);
}
inline std::ostream& operator<<(std::ostream& os, const std::shared_ptr<PassengerDetails>& pd)
{
	return pd->output(os);
}

#endif