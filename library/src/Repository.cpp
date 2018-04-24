#include "Repository.h"
#include <algorithm> 
using namespace std;
using namespace Hotel;
void ClientRepository::create(spClient client)
{
	cr.push_back(client);
}

void ClientRepository::remove(spClient client)
{
	cr.erase(std::remove(cr.begin(), cr.end(), client ),cr.end());
}

vector <spClient> ClientRepository::getAll()
{
	return cr;
}

/////////////////////////////////////////////////////////////////////////////////
void WorkerRepository::create(spWorker worker)
{
	wr.push_back(worker);
}

void WorkerRepository::remove(spWorker worker)
{
	wr.erase(std::remove(wr.begin(), wr.end(), worker ),wr.end());
}

vector <spWorker> WorkerRepository::getAll()
{
	return wr;
}

/////////////////////////////////////////////////////////////////////////////////
void RoomRepository::create(spRoom room)
{
	rr.push_back(room);
}

void RoomRepository::remove(spRoom room)
{
	rr.erase(std::remove(rr.begin(), rr.end(), room ),rr.end());
}

vector <spRoom> RoomRepository::getAll()
{
	return rr;
}


/////////////////////////////////////////////////////////////////////////////////

void RentRepository::create(spRent rent)
{
	rer.push_back(rent);
}

void RentRepository::remove(spRent rent)
{
	rer.erase(std::remove(rer.begin(), rer.end(), rent ),rer.end());
}

vector <spRent> RentRepository::getAll()
{
	return rer;
}


