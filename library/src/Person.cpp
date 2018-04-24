#include "Person.h"
using namespace Hotel;
using namespace std;

string Person::info()
{
	string result="Dane osoby: \n";
	result+="Imie:\t" + firstName + "\nNazwisko:\t" + lastName + "\nPESEL:\t" + personalID + "\nAdres:\t" + adress + "\n";
	return result;
}
string Person::getFirstName()
{
	return firstName;
}
string Person::getLastName()
{
	return lastName;
}
string Person::getPersonalID()
{
	return personalID;
}

string Person::getAdress()
{
	return adress;
}
