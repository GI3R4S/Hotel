#ifndef  MANAGER_H
#define  MANAGER_H
#include "Repository.h"
namespace Hotel
{
	class ClientManager
	{
		private:
		ClientRepository * clientRepository;
		public:
		ClientManager():
		clientRepository(new ClientRepository())
		{}
		~ClientManager(){delete clientRepository;};
		vector <spClient> getAll();
		vector <spEvent> getAllClientAdditionalCosts(spClient);
		string getClientInfo(spClient c);
		void addClient(spClient);
		void removeClient(spClient);
		void writeToFile(string);
		void readFromFile(string);
		void writeClientEventsToFile(string,spClient);
		void readClientEventsFromFile(string,spClient);
		bool checkPresence(spClient);
	};
	
	class WorkerManager
	{
		private:
		WorkerRepository * workerRepository;
		public:
		WorkerManager():
		workerRepository(new WorkerRepository())
		{}
		~WorkerManager(){delete workerRepository;};
		vector <spWorker> getAll();
		vector <spEvent> getAllWorkerBonuses(spWorker);
		string getWorkerInfo(spWorker);
		void addWorker(spWorker);
		void removeWorker(spWorker);
		void writeToFile(string);
		void readFromFile(string);
		void writeWorkerEventsToFile(string,spWorker);
		void readWorkerEventsFromFile(string,spWorker);
		bool checkPresence(spWorker);
	};
	
	class RoomManager
	{
		private:
		RoomRepository * roomRepository;
		public:
		RoomManager():
		roomRepository(new RoomRepository())
		{}
		~RoomManager(){delete roomRepository;};
		vector <spRoom> getAll();
		string getRoomInfo(spRoom);
		void addRoom(spRoom);
		void removeRoom(spRoom);
		void writeToFile(string);
		void readFromFile(string);
	};
	
	class RentManager
	{
		private:
		RentRepository * archiveRent;
		RentRepository * currentRent;
		public:
		RentManager():
		archiveRent(new RentRepository()),
		currentRent(new RentRepository())
		{}
		~RentManager(){
			delete archiveRent;
			delete currentRent;};
		void returnRoom(spRent,spLDT);
		vector <spRent> getArchive();
		vector <spRent> getCurrent();
		vector <spRent> getAllClientArchiveRents(spClient);
		vector <spRent> getAllClientCurrentRents(spClient);
		vector <spRent> getAll();
		void create(spRent);
		void saveAll(string,string);
		void loadAll(ClientManager *, WorkerManager *, RoomManager *, string,string);
		bool checkPresence(spRent);
	};
}

#endif
