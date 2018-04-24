#ifndef  RENT_H
#define  RENT_H
#include </usr/include/boost/uuid/random_generator.hpp>
#include </usr/include/boost/date_time/local_time/local_time.hpp>
#include <boost/enable_shared_from_this.hpp>
#include </usr/include/boost/uuid/uuid_io.hpp>
#include "Client.h"
#include "Worker.h"
#include "Room.h"
#include <string>
#include <sstream>
#include <memory>
namespace Hotel
{
	using namespace boost::local_time;
	using namespace boost::posix_time;
	using namespace boost::gregorian;
	using namespace boost::uuids;
	using namespace std;
	typedef shared_ptr <Room> spRoom;
	typedef shared_ptr <Client> spClient;
	typedef shared_ptr <Worker> spWorker;
	typedef shared_ptr <Rent> spRent;
	typedef shared_ptr <local_date_time> spLDT;
	class Rent
	{
		private:
		spClient client;
		spRoom room;
		spWorker worker;
		double rentCost;
		spLDT rentStart;
		spLDT rentEnd;
		uuid id;
		public:
		class RentException:public logic_error{public: RentException(const char* text):logic_error::logic_error(text){}};
		
		Rent(spClient c, spRoom r, spWorker w, spLDT ldt):
		client(c),
		room(r),
		worker(w),
		rentCost(0),
		rentStart(ldt)
		{
			rentEnd=make_shared<local_date_time>(not_a_date_time);
			random_generator gen;
			id=gen();
			if(c == nullptr || w == nullptr || r==nullptr || ldt==nullptr)
				throw RentException("Wprowadzono nullptr jako argument !!!");
		}
		
		void returnRoom(spLDT,double);
		int rentDuration();
		string rentInfo();
		////////gettery
		spClient getClient();
		spWorker getWorker();
		spRoom getRoom();
		spLDT getRentStart();
		spLDT getRentEnd();
		uuid getUUID();
		double getRentCost();
		///////settery
		void setRentCost(double);
		void setRentEnd(spLDT);
		void setUUID(uuid);
		
		bool operator ==(Rent & r )
		{
			string s1 = to_string(r.getUUID());
			string s2 = to_string(this->getUUID());	
			if(s1==s2)
				return true;
			else
				return false;
		}
		friend ostream& operator<< (std::ostream& os,  Rent & rent)
		{
			os<<*(rent.getClient());
			os<<*(rent.getRoom());
			os<<*(rent.getWorker());
			os<<rent.getRentCost()<<endl;
			os<<*(rent.getRentStart())<<endl;
			os<<*(rent.getRentEnd())<<endl;
			os<<(rent.getUUID())<<endl;
			return os;
		}
	
	
		friend std::istream& operator>> (std::istream& is,  Rent& rent)
		{
			string s=rent.rentInfo();
			is>>s;
			return is;
		}
	};
}

#endif
