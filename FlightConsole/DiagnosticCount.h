#pragma once
#ifndef DIAGNOSTIC_COUNT_H
#define DIAGNOSTIC_COUNT_H

template<typename T>
class DiagnosticCount
{
	static int _count;
	int _index;
public:
	DiagnosticCount() :_index(++_count)
	{
		std::cout << "Creating object no: " << _index << std::endl;
	}
	~DiagnosticCount()
	{
		std::cout << "Destroying object no: " << _index << std::endl;
	}
};
template<typename T>
int DiagnosticCount<T>::_count = 0;
void createObject();
#endif