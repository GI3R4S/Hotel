#ifndef  ROOM_H
#define  ROOM_H
#include <string>
#include <sstream>
#include <exception>

using namespace std;
namespace Hotel
{
	class Room
	{
		private:
		int maxCapacity;
		int id;
		string description;
		double dailyCost;
		public:
		class RoomException:public logic_error{public: RoomException(const char* text):logic_error::logic_error(text){}};
		Room(int MaxCapacity,int ID, string Description,double DailyCost):
		maxCapacity(MaxCapacity),
		id(ID),
		description(Description),
		dailyCost(DailyCost)
		{
			if(dailyCost<=0)
				throw RoomException("Dzienny koszt wynajmu pokoju nie moze byc wartoscia niedodatnia !!!");
			if(id<0)
				throw RoomException("Pokoj powinien miec nr nieujemny!!!");
			if(maxCapacity<=0)
				throw RoomException("Pojemnosc pokoju powinna byc wartoscia dodatnia !!!");
		}
		
		Room(int MaxCapacity,int ID,double DailyCost):
		maxCapacity(MaxCapacity),
		id(ID),
		description(" "),
		dailyCost(DailyCost)
		{
			if(dailyCost<=0)
				throw RoomException("Dzienny koszt wynajmu pokoju nie moze byc wartoscia niedodatnia !!!");
			if(id<0)
				throw RoomException("Pokoj powinien miec nr nieujemny!!!");
			if(maxCapacity<=0)
				throw RoomException("Pojemnosc pokoju powinna byc wartoscia dodatnia !!!");
	
		}
		string roomInfo();
		
		int getMaxCapacity();
		int getID();
		string getDescription();
		double getDailyCost();
		
		bool operator ==( const Room & c ) const
		{
			if(this->id==c.id)
				return true;
			else
				return false;
		}
		
		friend std::ostream& operator<< (std::ostream& os, Room& room)
		{
			os<<room.getMaxCapacity()<<endl;
			os<<room.getID()<<endl;
			os<<room.getDescription()<<endl;
			os<<room.getDailyCost()<<endl;
			return os;
		}
	
	
		friend std::istream& operator>> (std::istream& is,  Room& room)
		{
			string s=room.roomInfo();
			is>>s;
			return is;
		}
	};
}
#endif
