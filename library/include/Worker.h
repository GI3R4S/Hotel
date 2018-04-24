#ifndef  WORKER_H
#define  WORKER_H
#include "Person.h"
#include <vector>
#include "Event.h"
#include <iostream>
using namespace std;
namespace Hotel
{
typedef shared_ptr <Event> spEvent;
	class Worker : public Person
	{
		private:
		string jobType;
		double payPerDay;
		vector<spEvent> bonuses;
		
		public:
		class WorkerException:public logic_error{public: WorkerException(const char* text):logic_error::logic_error(text){}};
		Worker(string FirstName, string LastName,string Adress,string PESEL,string JobType,double PayPerDay):
		Person::Person(FirstName,LastName,Adress,PESEL),
		jobType(JobType),
		payPerDay(PayPerDay)
		{
			if(payPerDay<=0)
				throw WorkerException("Pracownik nie moze miec niedodatniego wynagrodzenia !");
		}
		vector<spEvent> getBonuses()
		{
			return bonuses;
		}
		string info();
		string getJobType();
		double getPayPerDay();
		void addEvent(spEvent);
		void removeEvent(spEvent);
		bool operator ==(  Worker & c ) 
		{
			string s1 = this->getPersonalID();
			string s2 = c.getPersonalID();
			if(s1 ==s2)
				return true;
			else
				return false;
		}
		
		friend std::ostream& operator<< (std::ostream& os,  Worker& client)
		{
			os<<client.Person::getFirstName()<<endl;
			os<<client.Person::getLastName()<<endl;
			os<<client.Person::getAdress()<<endl;
			os<<client.Person::getPersonalID()<<endl;
			os<<client.getJobType()<<endl;
			os<<client.getPayPerDay()<<endl;
			return os;
		}
	
	
		friend std::istream& operator>> (std::istream& is,  Worker& client)
		{
			string s=client.info();
			is>>s;
			return is;
		}
	};
}
#endif
