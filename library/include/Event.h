#ifndef  EVENT_H
#define  EVENT_H
#include <string>
#include <sstream>
#include </usr/include/boost/date_time/local_time/local_time.hpp>

using namespace boost::local_time;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace std;
namespace Hotel
{
typedef shared_ptr <local_date_time> spLDT;

	class Event
	{
		private:
		double balance;
		string description;
		spLDT ldt;
		
		public:
		
		Event(double Balance,string Description,spLDT LDT):
		balance(Balance),
		description(Description),
		ldt(LDT)
		{}
		double getBalance();
		string getDescription();
		spLDT getLdt();
		string eventInfo();
		
		friend ostream& operator<< (std::ostream& os, Event& event)
		{
			os<<event.getBalance()<<endl;
			os<<event.getDescription()<<endl;
			os<<*(event.getLdt())<<endl;
			return os;
		}
	};
}
#endif
