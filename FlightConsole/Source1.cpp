#include <iostream>
#include <string>
#include <locale>
#include <memory>
#include "DiagnosticCount.h"
#include "PassengerDetails.h"

void createObject()
{
	PassengerDetails pd("Fred", 2);
	pd.output(std::cout);
}