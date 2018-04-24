#include "Worker.h"
using namespace Hotel;
string Worker::info()
{
	string result=Person::info();
	double sum=0;
	stringstream ss,ss2;
	if(bonuses.size() != 0)
	{
		result+="Otrzymano nastepujace dodatki:\n";
		for(unsigned int i=0;i<bonuses.size();i++)
		{
			ss2<<i+1;
			result+=ss2.str()+". \n";
			result+=bonuses[i]->eventInfo();
			sum+=bonuses[i]->getBalance();
		}
	}
	if(sum !=0)
	{
		ss<<sum;
		return result + "\nSuma dodatkow:\t" + ss.str();
	}
	else
		return result;
}

string Worker::getJobType()
{
	return jobType;
}

double Worker::getPayPerDay()
{
	return payPerDay;
}

void Worker::addEvent(spEvent event)
{
	bonuses.push_back(event);
}

void Worker::removeEvent(spEvent event)
{
	bonuses.erase(remove(bonuses.begin(), bonuses.end(), event ),bonuses.end());
}
