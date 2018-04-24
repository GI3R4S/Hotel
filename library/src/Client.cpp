#include <sstream>
#include "Client.h"
using namespace Hotel;

string Client::info()
{
	string result=Person::info();
	result+="Typ klienta:\t"+ clientTypeName + "\n";
	double sum=0;
	stringstream ss2;
	if(additionalCosts.size() != 0)
	{
		result+="Naliczone zostaly nastepujace dodatkowe koszty:\n";
		for(int i=0;i<additionalCosts.size();i++)
		{
			ss2<<i+1;
			result+=ss2.str()+". \n";
			result+=additionalCosts[i]->eventInfo();
			sum+=additionalCosts[i]->getBalance();
		}
	}
	if(sum!=0)
	{
		stringstream ss;
		ss<<sum;
		return result + "Suma dodatkowych wydatkow:\t" + ss.str()+"\n";
	}
	else
		return result;
}

double Client::getDiscount(int i)
{
	clientType->getDiscount(i);
}

string Client::getClientTypeName()
{
	return clientTypeName;
}

void Client::changeClientType(int i)
{
	if(i<=2)
	{
		clientType=make_shared<ClientNew>();
		clientTypeName="Nowy klient";
	}
	else if(i>2 && i<=4)
	{
		clientType=make_shared<ClientTrusted>();
		clientTypeName="Zaufany klient";
	}
	else if(i>4)
	{
		clientType=make_shared<ClientBusiness>();
		clientTypeName="Biznesowy klient";
	}
}

vector<spEvent> Client::getAdditionalCosts()
{
	return additionalCosts;
}

unsigned int Client::getMaxCount()
{
	return clientType->getMaxCount();
}

void Client::addEvent(spEvent event)
{
	additionalCosts.push_back(event);
}

void Client::removeEvent(spEvent event)
{
	additionalCosts.erase(remove(additionalCosts.begin(), additionalCosts.end(), event ),additionalCosts.end());
}
