#include "Rent.h"
#include <iostream>
using namespace Hotel;
using namespace boost::local_time;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::uuids;
using namespace std;

int Rent::rentDuration()
{
	if(*rentEnd!=*(make_shared<local_date_time>(not_a_date_time)))
	{
		local_time_period ltp{*rentStart, *rentEnd};
		time_duration td =ltp.length();
		if(td.hours()<0 or td.minutes() <0 or td.seconds()<0)
			return 0;
		int days = ceil(td.hours()/24.0);
		if(td.hours()%24==0)
		{
			if(td.minutes()!=0)
				days++;
			else if (td.seconds()!=0)
				days++;
		}
		return days;
	}
	else 
		return 0;
}

void Rent::returnRoom(spLDT ldt,double discount)
{
	rentEnd= ldt;
	rentCost=rentDuration()*room->getDailyCost() * discount;
}

string Rent::rentInfo()
{
	stringstream ss1,ss2,ss3;
	string s1 = to_string(id);
	string s2,s3;
	ss1 << *rentStart;
	if(rentEnd)
	{
		ss2<<*rentEnd;
		s2=ss2.str();
		ss3<<rentCost;
		s3=ss3.str();
	}
	else
	{
		s2="Wypozyczenie niezakonczone!";
		s3="Wypozyczenie niezakonczone!";
	}
	string result="Dane wypozyczenia:\nID wypozyczenia:\t"+s1+"\nData wypozyczenia:\t"+ss1.str()+"\nData zakonczenia wypozyczenia:\t"+s2+"\nKoszt calkowity wypozyczenia bez znizek:\t" + s3;
	result+="\n\nDane klienta:\n" + client->info() + "\nDane pracownika:\n"+worker->info()+"\nDane pokoju:"+room->roomInfo();
	return result;
}

////////gettery
spClient Rent::getClient()
{
	return client;
}

spWorker Rent::getWorker()
{
	return worker;
}

spRoom Rent::getRoom()
{
	return room;
}

spLDT Rent::getRentStart()
{
	return rentStart;
}

spLDT Rent::getRentEnd()
{
	return rentEnd;
}

uuid Rent::getUUID()
{
	return id;
}

double Rent::getRentCost()
{
	return rentCost;
}

//////settery
void Rent::setRentCost(double cost)
{
	rentCost=cost;
}

void Rent::setRentEnd(spLDT ldt)
{
	rentEnd=ldt;
}

void Rent::setUUID(uuid  ID)
{
	id=ID;
}
