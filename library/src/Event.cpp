#include "Event.h"
using namespace Hotel;
double Event::getBalance()
{
	return balance;
}

string Event::getDescription()
{
	return description;
}

spLDT Event::getLdt()
{
	return ldt;
}

string Event::eventInfo()
{
	string result;
	stringstream s1,s2;
	s1 <<  balance;
	s2 << *ldt;
	result="Opis:\n" + description + "\nKwota: \n" + s1.str() + "\nData:\n" + s2.str() + "\n";
	return result;
}
