#include <iostream>
#include <vector>
#include <functional>
#include <string>

double info() { return 0.0; }
void autoDecltype()
{
	auto a = 23;
	auto b = "Hello World!";

	std::cout << a << ", " << b << std::endl;

	decltype(a) c = 54;
	decltype(a*1.0) d = 64;

	std::cout << c << ", " << d << std::endl;

	decltype(info) result1;
	decltype(info()) result2 = 1;
	std::cout << result2 << std::endl;

	decltype((a)) e = a;
	auto& ra = a;

	std::cout << e << ", " << ra << std::endl;
}
template<class T>
inline T myMax(T t1, T t2)
{
	static_assert(std::is_integral<T>::value ||
		std::is_floating_point<T>::value, "Not a number!");
	return t1 < t2 ? t2 : t1;
}
void usingType()
{
	using myInt = int;

	myInt num = 32;
}
void nullptrFun()
{
	int *pInt = nullptr;

	if (pInt)
	{
		std::cout << "Valid pointer" << std::endl;
	}
	else
	{
		std::cout << "Nullptr!" << std::endl;
	}
	delete pInt;
}
void doWork(int *pInt)
{
	std::cout << "Valid pointer" << *pInt << std::endl;
}
void doWork(nullptr_t)
{
	std::cout << "Null pointer" << std::endl;
}
void doWork(int a, int *pi, double *pd){}
void doWork(int a, double *pi, double *pd){}
void doWork(int a, nullptr_t, double *pd){}

void forFun()
{
	int data[] = { 324, 4, 3, 56, 67, 1, 345, 56, 5 };

	for (auto& i : data)
	{
		std::cout << i << std::endl;
	}
	std::vector<double> dData{ 43.5, 5.3, 4.76, 65.4, 6.0, 54, 6 };

	for (auto i : dData)
	{
		std::cout << i << ", ";
	}
	std::cout << std::endl;
	for (std::vector<double>::const_iterator it = dData.begin(); it != dData.end(); ++it)
	{
		std::cout << *it << ", ";
	}
	std::cout << std::endl;
}

double oldSquare(double d) { return d*d; }
auto newSquare(double d)-> double { return d*d; }
auto mult(double a, double b, double c) -> double{ return a*b*c; }

void strongEnumFun()
{
	enum class Number:unsigned int { One=1, Two=2, Three};
	Number n = Number::One;
	
	switch (n)
	{
	case Number::One:
		std::cout << "One" << std::endl;
		break;
	case Number::Two:
		std::cout << "Two" << std::endl;
		break;
	case Number::Three:
		std::cout << "Three" << std::endl;
		break;
	default:
		break;
	}	
}
void stringFun()
{
	std::string stringNum = "43.2";

	auto num = std::stod(stringNum);
	std::cout << "String: " << stringNum << ", Number: " << num << std::endl;

	auto innerCptr = stringNum.c_str();
	 
	stringNum.push_back('5');
	num = std::stod(stringNum);
	std::cout << "String: " << stringNum << ", Number: " << num << std::endl;
}
class Simple{
	//Simple()
	//{

	//}
};
//[[deprecated]]
void traitsFun()
{
	std::cout << std::boolalpha;
	std::cout << "trivial " << std::is_trivial<Simple>::value << std::endl;
	std::cout << "trivial assignable " << std::is_trivially_assignable<Simple,Simple>::value << std::endl;
	std::cout << "trivial constructor: " << std::is_trivially_constructible<Simple>::value << std::endl;
	std::cout << "trivial destructable: " << std::is_trivially_destructible<Simple>::value << std::endl;
	std::cout << "pod " << std::is_pod<Simple>::value << std::endl;
}

class AType
{
	int _n;
	std::vector<int> _vec1;
	std::vector<int> _vec2;
public:
	AType(int n):_n(n){}
	AType(std::initializer_list<int> data) :_vec1(data)
	{		
		for (auto it = data.begin(); it != data.end(); it++)
		{
			_vec2.push_back(*it);
		}
	}
	void output1()
	{
		for (auto& item : _vec1)
		{
			std::cout << item << ", ";
		}
		std::cout << std::endl;
	}
	void output2()
	{
		for (auto& item : _vec2)
		{
			std::cout << item << ", ";
		}
		std::cout << std::endl;
	}
};
class NoCopy final
{
	static int val;
public:
	NoCopy() = default;
	NoCopy(const NoCopy&) = delete;
	NoCopy& operator=(const NoCopy&) = delete;
	virtual void work()  {}
};
int NoCopy::val = 0;
//class Derived : public NoCopy
//{
//public:
//	void work() override {}
//};
int main()
{
	{
		//int final = 34;
		NoCopy nc1, nc2;
		//NoCopy nc3(nc1);

		//nc1 = nc2;
		//Derived d;

		//d.work();
	}
	{
		std::vector<int> vec(50, 4);

		std::cout << "Data" << std::endl;
		for (auto& i : vec)
		{
			std::cout << i << std::endl;
		}
		std::cout << "Next example!" << std::endl;
		AType at(32);
		AType at2 = 66;

		auto a(2);
		int b ( 23);

		std::cout << a << ", " << b << std::endl;
		auto c{ 54 };
		int d{ 65 };
		std::cout << ", " << d << std::endl;
	}
	{
		AType at1 = { 345, 56, 67, 34, 54, 5654, 6 };

		AType at2{ 75, 5, 7, 4, 5, 45, 45, 6 };

		at1.output1();
		at2.output2();
	}
	{
		traitsFun();
	}
	{
		stringFun();
	}
	{
		strongEnumFun();
	}
	{
		std::function<int(int)> calc = newSquare;

		std::cout << "square of 7 from wrapper: " << calc(7) << std::endl;
		std::function<double(double,double,double)> calc2 = mult;

		std::cout << "mult from wrapper: " << calc2(3.5,76.3,2.1) << std::endl;

	}
	{
		std::cout << "old square of 7: " << oldSquare(7) << std::endl;
		std::cout << "new square of 7: " << newSquare(7) << std::endl;
	}
	{
		forFun();
	}
	{
		auto a = 12;
		auto b = 765.2;
		doWork(34, &a, &b);
		doWork(34, nullptr, &b);
		doWork(&a);
		doWork(nullptr);
	}
	auto result1 = myMax(23.3, 1.6);
//	auto result2 = myMax("Hello", "Greetings");

	std::cout << result1 << std::endl;

	autoDecltype();

	return 0;
}