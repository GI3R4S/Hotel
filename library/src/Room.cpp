#include "Room.h"
using namespace Hotel;
string Room::roomInfo()
{
	stringstream s1,s2,s3;
	s1<<id;
	s2<<maxCapacity;
	s3<<dailyCost;
	string result="\nNumer pokoju:\t "+ s1.str()+ "\nMaksymalna pojemnosc:\t"+ s2.str()+"\nDzienny koszt:\t"+s3.str()+"\nOpis pokoju:\n"+description+"\n";
	return result;
}

double Room::getDailyCost()
{
	return dailyCost;
}

int Room::getID()
{
	return id;
}

int Room::getMaxCapacity()
{
	return maxCapacity;
}

string Room::getDescription()
{
	return description;
}
