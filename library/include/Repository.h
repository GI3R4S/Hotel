#ifndef  REPOSITORY_H
#define  REPOSITORY_H
#include <vector>
#include "Rent.h"
#include <algorithm>
#include <memory>
using namespace std;
namespace Hotel
{
typedef shared_ptr<Room> spRoom;
	template <typename T> class Repository
	{
		public:
		virtual void create(){};
		virtual void remove(){};
		virtual vector<T> getAll()=0;	
		virtual ~Repository(){};
		Repository(){};
	};
	
	class RoomRepository : public Repository <spRoom>
	{
		private:
		vector <spRoom> rr;
		public:
		void create(spRoom);
		void remove(spRoom);
		vector<spRoom> getAll();
	};
	
	class ClientRepository : public Repository <spClient>
	{
		private:
		vector <spClient> cr;
		public:
		void create(spClient);
		void remove(spClient);
		vector<spClient> getAll();	
		virtual ~ClientRepository(){};
		ClientRepository(){};
	};
	class WorkerRepository : public Repository <spWorker>
	{
		private:
		vector <spWorker> wr;
		public:	
		void create(spWorker);
		void remove(spWorker);
		vector<spWorker> getAll();	
		virtual ~WorkerRepository(){};
		WorkerRepository(){};
	};
	
	class RentRepository : public Repository <spRent>
	{
		private:
		vector <spRent> rer;
		public:	
		void create(spRent);
		void remove(spRent);
		vector<spRent> getAll();	
		~RentRepository(){};
		RentRepository(){};
	};
	
	#endif
}
