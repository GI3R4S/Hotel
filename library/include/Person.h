#ifndef  PERSON_H
#define  PERSON_H
#include <string>
#include <exception>
#include <iostream>
using namespace std;
namespace Hotel
{
	class Person
	{
		private:
		string firstName;
		string lastName;
		string adress;
		string personalID;
		public:
		class PersonException:public logic_error{public: PersonException(const char* text):logic_error::logic_error(text){}};
		Person(string FirstName,string LastName,string Adress, string PESEL):
		firstName(FirstName),
		lastName(LastName),
		adress(Adress),
		personalID(PESEL)
		{
			for(unsigned int i=0;i<firstName.size();i++)
				if(firstName[i]>='0' && firstName[i]<='9')
					throw PersonException("Imie zawiera cyfry !");
			for(unsigned int i=0;i<firstName.size();i++)
				if(lastName[i]>='0' && lastName[i]<='9')
					throw PersonException("Nazwisko zawiera cyfry !");
			for(unsigned int i=0;i<personalID.size();i++)
				if(personalID[i]<'0' || personalID[i]>'9')
					throw PersonException("PESEL zawiera litery !");
		
		}
		virtual ~Person(){};
		string info();
		string getFirstName();
		string getLastName();
		string getAdress();
		string getPersonalID();
		
		bool operator ==( const Person & c ) const
		{
			if(this->personalID==c.personalID)
				return true;
			else
				return false;
		}
		
		friend std::ostream& operator<< (std::ostream& os,  Person& person)
		{
			os<<person.firstName<<endl;
			os<<person.lastName<<endl;
			os<<person.adress<<endl;
			os<<person.personalID<<endl<<endl;
			return os;
		}
	
	
		friend std::istream& operator>> (std::istream& is,  Person& person)
		{
			string s=person.info();
			is>>s;
			return is;
		}
		
	};
}
#endif
