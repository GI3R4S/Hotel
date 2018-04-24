#ifndef  CLIENT_H
#define  CLIENT_H
#include "Event.h"
#include "Person.h"
#include "ClientType.h"
#include "ClientNew.h"
#include "ClientTrusted.h"
#include "ClientBusiness.h"
#include <vector>
#include <memory>
#include <string>
namespace Hotel
{
	typedef shared_ptr <ClientType> spClientType;
	typedef shared_ptr <Event> spEvent;
	class Rent;
	using namespace std;
	
	class Client : public Person
	{
		private:
		string clientTypeName;
		spClientType clientType;
		vector<spEvent> additionalCosts;
		vector<Rent*> rents;
		
		
		public:
		Client(string FirstName,string LastName, string Adress, string PESEL):
		Person::Person(FirstName,LastName,Adress,PESEL),
		clientTypeName("Nowy klient"),
		clientType(make_shared<ClientNew>())
		{}
		
		string info();
		vector<spEvent>  getAdditionalCosts();
		void addEvent(spEvent);
		void removeEvent(spEvent event);
		double getDiscount(int);
		string getClientTypeName();
		void changeClientType(int);
		unsigned int getMaxCount();
		
		bool operator ==(  Client & c ) 
		{
			string s1 = this->getPersonalID();
			c.getPersonalID();
			string s2 = c.getPersonalID();
			if(s1 ==s2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		friend std::ostream& operator<< (std::ostream& os,  Client& client)
		{
			os<<client.Person::getFirstName()<<endl;
			os<<client.Person::getLastName()<<endl;
			os<<client.Person::getAdress()<<endl;
			os<<client.Person::getPersonalID()<<endl;
			return os;
		}
	
	
		friend std::istream& operator>> (std::istream& is,  Client& client)
		{
			string s=client.info();
			is>>s;
			return is;
		}
	
	};
}
#endif
