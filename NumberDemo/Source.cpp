#include <iostream>
#include <list>
#include <map>
#include <string>
class MyNumber
{
	int* _pVal;
	void swap(MyNumber& mn)
	{
		std::swap(_pVal, mn._pVal);
	}
public:
	MyNumber(int val = 0) :_pVal(new int(val)){}
	explicit operator int(){ return *_pVal; }
	~MyNumber(){ delete _pVal; }
	MyNumber(const MyNumber& mn);
	MyNumber(MyNumber&& mn){
		_pVal = mn._pVal;
		mn._pVal = nullptr;
	}
	MyNumber& operator=(const MyNumber& mn){
		MyNumber temp(mn);
		swap(temp);
		//if (this != &mn)
		//{
		//	delete _pVal;
		//	_pVal = new int;
		//	*_pVal = mn.getVal();
		//}
		return *this;
	}
	MyNumber& operator=(MyNumber&& mn)
	{
		swap(mn);
		return *this;
	}
	int getVal() const { return *_pVal; }
	void setVal(int n) { *_pVal = n; }
	MyNumber add(const MyNumber& rhs) const {
		//return MyNumber(*_pVal + *rhs._pVal);
		MyNumber mn;
		mn.setVal(*_pVal + *rhs._pVal);
		return mn;
	}
	bool less(const MyNumber& rhs) const
	{
		return getVal() < rhs.getVal();
	}
};
MyNumber::MyNumber(const MyNumber& mn)
{
	_pVal = new int(*mn._pVal);
}
inline MyNumber operator+(const MyNumber& lhs, const MyNumber& rhs)
{
	return lhs.add(rhs);
}
inline bool operator<(const MyNumber& lhs, const MyNumber& rhs)
{
	return lhs.less(rhs);
}
int main()
{
	{
		std::map<MyNumber, int> myNumInt;

		myNumInt[MyNumber(4)] = 4;

		std::cout << typeid(std::map<MyNumber, int>::value_type).name() << std::endl;

	}
	{
		int data[] {45, 45, 5, 6, 78, 3455, 6, 45, 345};
		std::cout << "Unsorted:" << std::endl;
		for (auto it = std::cbegin(data); it != std::cend(data); it++)
		{
			std::cout << *it << ", ";
		}
		std::cout << std::endl;
	}
	{
		std::list<MyNumber> data;

		for (size_t i = 0; i < 10; i += 2)
		{
			data.push_back(i);
			data.push_front(i + 1);
		}
		std::cout << "Unsorted:" << std::endl;
		for (auto it = std::cbegin(data); it != std::cend(data); it++)
		{
			std::cout << it->getVal() << ", ";
		}
		/*for (auto& item : data)
		{
		std::cout << item.getVal() << ", ";
		}*/
		std::cout << std::endl;
		//data.sort();
		std::cout << "Unsorted:" << std::endl;
		for (const auto& item : data)
		{
			std::cout << item.getVal() << ", ";
		}
		std::cout << std::endl;
	}
	{
		MyNumber mn1(234);
		MyNumber mn2(mn1);
		MyNumber mn3;
		MyNumber mn4(mn1 + mn2), mn5, mn6, mn7;
		mn3 = mn2;
		mn5 = mn1 + mn2;
		mn6 = mn1 + 54;
		mn7 = 765 + mn1;
		std::cout << mn1.getVal() << ", " << mn2.getVal() << ", " << mn3.getVal() << std::endl;
		std::cout << mn4.getVal() << ", " << mn5.getVal() << std::endl;
		std::cout << mn6.getVal() << ", " << mn7.getVal() << std::endl;
	}

	return 0;
}