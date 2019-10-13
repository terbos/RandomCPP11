#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <tuple>
#include <map>
template<class AType>
void doWork(AType t)
{
	t.work(23, 45456);
}
template<class T>
inline T myMax(const T& x, const T& y)
{
	static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Not a number!");
	return x < y ? y : x;
}
template<class T, class U>
inline auto myMax(const T& x, const U& y) ->decltype(x+y)
{
	static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value
		&& std::is_integral<U>::value || std::is_floating_point<U>::value, "Not a number!");
	return x < y ? y : x;
}
inline const char* myMax(const char* x, const char* y)
{
	return strcmp(x, y) < 0 ? y: x;
}
class DataTypes
{
	std::vector<std::string> _types;
public:

	std::vector<std::string> getTypes(){ return _types; }

	template<typename T>
	void add(T t){ _types.push_back(typeid(T).name()); }
};
void fun(int& i, double& d)
{
	i *= 2;
	std::cout << "Ref: " << i << ", " << d << std::endl;
}
void fun(const int& i, const double& d)
{
	std::cout << "Const: " << i << ", " << d << std::endl;
}
template<typename T, typename R>
inline void wrapper1(T t, R r)
{
	std::cout << "Wrapper1:" << std::endl;
	fun(t, r);
}
template<typename T, typename R>
inline void wrapper2(T& t, R& r)
{
	std::cout << "Wrapper2:" << std::endl;
	fun(t, r);
}
template<typename T, typename R>
inline void wrapper3(T&& t, R&& r)
{
	std::cout << "Wrapper3:" << std::endl;
	fun(std::forward<T>(t), std::forward<R>(r));
}
template< typename T>
T sum(T t)
{
	return t;
}
template< typename T, typename... Rest>
auto sum(T t, Rest... rest) -> decltype(t + sum(rest...))
{
	return t + sum(rest...);
}
template<typename T>
void echo(T t){ std::cout << t << std::endl; }
template<typename... Rest>
void doEcho(Rest... rest)
{
	std::make_tuple((echo(std::forward<Rest>(rest)), 0)...);
}
template<typename AType>
void Traits()
{
	std::cout << std::boolalpha;
	std::cout << typeid(AType).name() << ": is_constructible" << std::is_constructible<AType>::value << std::endl;
	std::cout << typeid(AType).name() << ": is_copy_constructible" << std::is_copy_constructible<AType>::value << std::endl;
	std::cout << typeid(AType).name() << ": is_move_constructible" << std::is_move_constructible<AType>::value << std::endl;
}
class MyClass
{public:
	MyClass()
	{
	}

	~MyClass()
	{
	}
private:
};
int main()
{	
	{
		Traits<MyClass>();
		Traits<int>();
		Traits<std::vector<int>>();
	}
	{
		std::vector<int, std::allocator<int>> vec;
		std::map<int, double> m;
	}
	{
		doEcho(324, 56, 67, "Hello", 6554879879708L, 234.2);
		doEcho();
	}
	{
		auto result = sum(23, 4, 6.6, 546.3, 34, 5, 7,2.3,3l);
		std::cout << result << std::endl;

	}
	{
		int a = 23;
		double b = 654;
		wrapper1(a, b);
		std::cout << a << std::endl;
		wrapper1(1, 3.2);
		wrapper2(a, b);
		std::cout << a << std::endl;
		//wrapper2(1, 3.2);
		wrapper3(a, b);
		std::cout << a << std::endl;
		wrapper3(1, 3.2);
	}
	{
		std::string s("Hello");
		DataTypes dt;
		dt.add(34);
		dt.add(234.5);
		dt.add(1l);
		dt.add(s);
		for (auto& item : dt.getTypes())
		{
			std::cout << item << std::endl;
		}
	}
	{
		int a = 32, b = 65;
		//const int& ca = a; const int& cb = b;
		auto ans = myMax(67.3, a);
		std::cout << a << ", " << b << ", max: " << ans << std::endl;
	}
	{
		const char* a = "Hello", *b = "Greetings", *ans;

		ans = myMax(a, b);
		std::cout << a << ", " << b << ", max: " << ans << std::endl;
	}

	{
		double a = 345.1, b = 1.65, ans;

		ans = myMax(a, b);
		std::cout << a << ", " << b << ", max: " << ans << std::endl;
	}



	return 0;
}