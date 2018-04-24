#include "Manager.h"
#include <fstream>
#include <istream>

using namespace boost::local_time;
using namespace boost::posix_time;
using namespace boost::gregorian;
using namespace boost::uuids;
using namespace std;
using namespace Hotel;

bool ClientManager::checkPresence(spClient client)
{
	bool trigger=false;
	for(unsigned int i=0;i<getAll().size();i++)
	{
		if(*client==*getAll()[i])
		{
			trigger=true;
			break;
		}
	}
	return trigger;
}
vector <spEvent> ClientManager::getAllClientAdditionalCosts(spClient c)
{
	return c->getAdditionalCosts();
}

string ClientManager::getClientInfo(spClient c)
{
	return c->info();
}

void ClientManager::addClient(spClient c1)
{
	if(!checkPresence(c1))
		clientRepository->create(c1);
}
void ClientManager::removeClient(spClient c)
{
	clientRepository->remove(c);
}
vector<spClient> ClientManager::getAll()
{
	return clientRepository->getAll();
}

void ClientManager::writeToFile(string arg)
{
	ofstream file;
	file.open(arg);
	if(file.good())
	{
		for(unsigned int i=0;i<getAll().size();i++)
			file<<*(getAll()[i]);
	}
	file.close();
}

void ClientManager::readFromFile(string arg)
{
	fstream file;
	file.open( arg,ios::in);
	////////////////
	string line,cont0,cont1,cont2,cont3;
	int iterator=0;
	////////////////
	if(file.good())
	{
		while(getline(file,line))
		{
			int tmp=0;
			if(iterator%4==3)
			{
				istringstream ss(line);
				ss>>tmp;
			}
			switch(iterator%4)
			{
				case 0:
				{
					cont0=line;
					break;
				}
				case 1:
				{
					cont1=line;
					break;
				}
				case 2:
				{
					cont2=line;
					break;
				}
				case 3:
				{
					cont3=line;
					spClient ptr = make_shared<Client>(cont0,cont1,cont2,cont3);
					addClient(ptr);
					break;
				}
			}
			iterator++;
		}
	}
	file.close();
}


void ClientManager::writeClientEventsToFile(string arg,spClient client)
{
	if(checkPresence(client))
	{
		ofstream file;
		file.open(arg);
		if(file.good())
		{
			for(unsigned int i=0;i<getAllClientAdditionalCosts(client).size();i++)
				file<<*(getAllClientAdditionalCosts(client)[i]);
		}
		file.close();
	}
}

void ClientManager::readClientEventsFromFile(string arg,spClient client)
{
	if (checkPresence(client))
	{
		fstream file;
		file.open( arg,ios::in);
		////////////////
		double cont0;
		string line,cont1;
		int iterator=0;
		////////////////
		if(file.good())
		{
			while(getline(file,line))
			{
				int tmp=0;
				if(iterator%3==0)
				{
					istringstream ss(line);
					ss>>tmp;
				}
				switch(iterator%3)
				{
					case 0:
					{
						cont0=tmp;
						break;
					}
					case 1:
					{
						cont1=line;
						break;
					}
					case 2:
					{
						stringstream ss;
						local_time_input_facet *input_facet   = new local_time_input_facet("%Y-%b-%d %H:%M:%S %ZP");
						ss.imbue(std::locale(ss.getloc(), input_facet));
						spLDT cont2=make_shared<local_date_time>(not_a_date_time);
						ss.str(line);
						ss >> *cont2;
						spEvent ptr = make_shared<Event>(cont0,cont1,cont2);
						client->addEvent(ptr);
						break;
					}
				}
				iterator++;
			}
		}
		file.close();
	}
}
///////////////////////////////////////////////////////////////////////////
bool WorkerManager::checkPresence(spWorker worker)
{
	bool trigger=false;
	for(unsigned int i=0;i<getAll().size();i++)
	{
		if(*worker==*getAll()[i])
		{
			trigger=true;
			break;
		}
	}
	return trigger;
}
vector <spEvent> WorkerManager::getAllWorkerBonuses(spWorker w)
{
	return w->getBonuses();
}

string WorkerManager::getWorkerInfo(spWorker w)
{
	return w->info();
}

void WorkerManager::addWorker(spWorker w1)
{
	if(!checkPresence(w1))
		workerRepository->create(w1);
}
void WorkerManager::removeWorker(spWorker w)
{
	workerRepository->remove(w);
}
vector<spWorker> WorkerManager::getAll()
{
	return workerRepository->getAll();
}

void WorkerManager::writeToFile(string arg)
{
	ofstream file;
	file.open(arg);
	if(file.good())
	{
		for(unsigned int i=0;i<getAll().size();i++)
			file<<*(getAll()[i]);
	}
	file.close();
}

void WorkerManager::readFromFile(string arg)
{
	fstream file;
	file.open( arg,ios::in);
	////////////////
	string line,cont0,cont1,cont2,cont3,cont4;
	double cont5;
	int iterator=0;
	////////////////
	if(file.good())
	{
		while(getline(file,line))
		{
			int tmp=0;
			if(iterator%6==5)
			{
				istringstream ss(line);
				ss>>tmp;
			}
			switch(iterator%6)
			{
				case 0:
				{
					cont0=line;
					break;
				}
				case 1:
				{
					cont1=line;
					break;
				}
				case 2:
				{
					cont2=line;
					break;
				}
				case 3:
				{
					cont3=line;
					break;
				}
				case 4:
				{
					cont4=line;
					break;
				}
				case 5:
				{
					cont5=tmp;
					spWorker ptr = make_shared<Worker>(cont0,cont1,cont2,cont3,cont4,cont5);
					addWorker(ptr);
					break;
				}
			}
			iterator++;
		}
	}
	file.close();
}
void WorkerManager::writeWorkerEventsToFile(string arg,spWorker worker)
{
	if(checkPresence(worker))
	{
		ofstream file;
		file.open(arg);
		if(file.good())
		{
			for(unsigned int i=0;i<getAllWorkerBonuses(worker).size();i++)
				file<<*(getAllWorkerBonuses(worker)[i]);
		}
		file.close();
	}
}

void WorkerManager::readWorkerEventsFromFile(string arg,spWorker worker)
{
	if(checkPresence(worker))
	{
		fstream file;
		file.open( arg,ios::in);
		////////////////
		double cont0;
		string line,cont1;
		int iterator=0;
		////////////////
		if(file.good())
		{
			while(getline(file,line))
			{
				int tmp=0;
				if(iterator%3==0)
				{
					istringstream ss(line);
					ss>>tmp;
				}
				switch(iterator%3)
				{
					case 0:
					{
						cont0=tmp;
						break;
					}
					case 1:
					{
						cont1=line;
						break;
					}
					case 2:
					{
						stringstream ss;
						local_time_input_facet *input_facet   = new local_time_input_facet("%Y-%b-%d %H:%M:%S %ZP");
						ss.imbue(std::locale(ss.getloc(), input_facet));
						spLDT cont2=make_shared<local_date_time>(not_a_date_time);
						ss.str(line);
						ss >> *cont2;
						spEvent ptr = make_shared<Event>(cont0,cont1,cont2);
						worker->addEvent(ptr);
						break;
					}
				}
				iterator++;
			}
		}
		file.close();
	}
}
/////////////////////////////////////////////////////////////////////////
string RoomManager::getRoomInfo(spRoom r)
{
	return r->roomInfo();
}

void RoomManager::addRoom(spRoom r1)
{
	bool trigger=true;
	for(unsigned int i=0;i<getAll().size();i++)
	{
		if(r1->getID()==getAll()[i]->getID())
		{
			trigger=false;
			break;
		}
	}
	if(trigger)
		roomRepository->create(r1);
}
void RoomManager::removeRoom(spRoom r)
{
	roomRepository->remove(r);
}
vector<spRoom> RoomManager::getAll()
{
	return roomRepository->getAll();
}
void RoomManager::writeToFile(string arg)
{
	ofstream file;
	file.open(arg);
	if(file.good())
	{
		for(unsigned int i=0;i<getAll().size();i++)
			file<<*(getAll()[i]);
	}
	file.close();
}

void RoomManager::readFromFile(string arg)
{
	fstream file;
	file.open( arg,ios::in);
	////////////////
	string line,cont2;
	double cont0,cont1,cont3;
	int iterator=0;
	////////////////
	if(file.good())
	{
		while(getline(file,line))
		{
			int tmp=0;
			if(iterator%4!=2)
			{
				istringstream ss(line);
				ss>>tmp;
			}
			switch(iterator%4)
			{
				case 0:
				{
					cont0=tmp;
					break;
				}
				case 1:
				{
					cont1=tmp;
					break;
				}
				case 2:
				{
					cont2=line;
					break;
				}
				case 3:
				{
					cont3=tmp;
					spRoom ptr = make_shared<Room>(cont0,cont1,cont2,cont3);
					addRoom(ptr);
					break;
				}
			}
			iterator++;
		}
	}
	file.close();
}
/////////////////////////////////////////////////////////////////////////

 vector <spRent> RentManager::getArchive()
{
	return archiveRent->getAll();
}

vector <spRent> RentManager::getCurrent()
{
	return currentRent->getAll();
}

vector <spRent> RentManager::getAllClientArchiveRents(spClient c)
{
	vector <spRent> result;
	for(unsigned int i=0;i<getArchive().size();i++)
		if(*(getArchive()[i]->getClient())==*c)
			result.push_back(getArchive()[i]);
	return result;
}
vector <spRent> RentManager::getAllClientCurrentRents(spClient c)
{
	vector <spRent> result;
	for(unsigned int i =0;i<getCurrent().size();i++)
		if(*(getCurrent()[i]->getClient())==*c)
			result.push_back(getCurrent()[i]);
	return result;
}


void RentManager::returnRoom(spRent r1,spLDT ldt)
{
	for(unsigned int i=0;i<getCurrent().size();i++)
	{
		if(*r1==*(getCurrent()[i]))
		{
			//1->returnRoom(ldt,getAllClientArchiveRents(r1->getClient()).size());
			r1->returnRoom(ldt,r1->getClient()->getDiscount((getAllClientArchiveRents(r1->getClient()).size())));
			archiveRent->create(r1);
			currentRent->remove(r1);
			r1->getClient()->changeClientType(getAllClientArchiveRents(r1->getClient()).size());
			break;
		}
	}
}

vector<spRent> RentManager::getAll()
{
	vector <spRent> result;
	auto archive_first=getArchive().begin();
	auto archive_last=getArchive().end();
	auto current_first=getCurrent().begin();
	auto current_last=getCurrent().end();
	
	result.reserve(getArchive().size()+getCurrent().size());
	result.insert(result.end(),archive_first,archive_last);
	result.insert(result.end(),current_first,current_last);
	return result;
}

void RentManager::create(spRent rent)
{
	 if ( !checkPresence(rent)
	 &&   (getAllClientCurrentRents(rent->getClient()).size() < rent->getClient()->getMaxCount()))
		currentRent->create(rent);
}

void RentManager::saveAll(string name1, string name2)
{
	fstream file1;
	file1.open(name1,ios::out);
	if(getArchive().size())
	for(unsigned int i=0;i<getArchive().size();i++)
		file1<<*(getArchive()[i]);	
	file1.close();
	////////////////////////////////////////////////////
	fstream file2;
	file2.open(name2,ios::out);
	if(getCurrent().size())
	for(unsigned int i=0;i<getCurrent().size();i++)
		file2<<*(getCurrent()[i]);
	file2.close();
}

void RentManager::loadAll(ClientManager * cm,WorkerManager * wm,RoomManager * rm,string name1,string name2)
{
	int count = 2;
	while(count--)
	{
		fstream file;
		if(count==1)
			file.open(name1,ios::in);
		if(count==0)
			file.open(name2,ios::in);
		string line,cont0,cont1,cont2,cont3,cont6,cont8,cont9,cont10,cont11,cont12;
		double cont4,cont5,cont7,cont13,cont14;
		spLDT cont15=nullptr;
		spLDT cont16=nullptr;
		spClient ptr1;
		spRoom ptr2;
		spWorker ptr3;
		if(file.good())
		{
			int iterator=0;
			while(getline(file,line))
			{
			try
				{
					
					int tmp=0;
					if((iterator%18==4)
					|  (iterator%18==5)
					|  (iterator%18==7)
					|  (iterator%18==13)
					|  (iterator%18==14)
					)
					{
						istringstream ss(line);
						ss>>tmp;
					}
					
					switch(iterator%18)
					{
					/////////////////client
						case 0:
						{
							cont0=line;
							break;
						}
						case 1:
						{
							
							cont1=line;
							break;
						}
						case 2:
						{
							cont2=line;
							break;
						}
						case 3:
						{
							cont3=line;
							ptr1 = make_shared<Client>(cont0,cont1,cont2,cont3);
							cm->addClient(ptr1);
							break;
						}
						/////////////////room
						case 4:
						{
							cont4=tmp;
							break;
						}
						case 5:
						{
							cont5=tmp;
							break;
						}
						case 6:
						{
							cont6=line;
							break;
						}
						case 7:
						{
							cont7=tmp;
							ptr2 = make_shared<Room>(cont4,cont5,cont6,cont7);
							rm->addRoom(ptr2);
							break;
						}
						////////////worker
						case 8:
						{
							cont8=line;
							break;
						}
						case 9:
						{
							cont9=line;
							break;
						}
						case 10:
						{
							cont10=line;
							break;
						}
						case 11:
						{
							cont11=line;
							break;
						}
						case 12:
						{
							cont12=line;
							break;
						}
						case 13:
						{
							cont13=tmp;
							ptr3 = make_shared<Worker>(cont8,cont9,cont10,cont11,cont12,cont13);
							wm->addWorker(ptr3);
							break;
						}
						/////////////rent
						case 14:
						{
							cont14=tmp;
							break;
						}		
						case 15:
						{
							stringstream ss;
							local_time_input_facet *input_facet   = new local_time_input_facet("%Y-%b-%d %H:%M:%S %ZP");
							ss.imbue(std::locale(ss.getloc(), input_facet));
							cont15=make_shared<local_date_time>(not_a_date_time);
							ss.str(line);
							ss >> *cont15;
							break;
						}
						case 16:
						{
							
							stringstream ss;
							local_time_input_facet *input_facet   = new local_time_input_facet("%Y-%b-%d %H:%M:%S %ZP");
							ss.imbue(std::locale(ss.getloc(), input_facet));
							cont16=make_shared<local_date_time>(not_a_date_time);
							ss.str(line);
							ss >> *cont16;
							break;
						}
						case 17:
						{
							uuid cont17 =boost::lexical_cast<uuid>(line);
							spRent  r = make_shared<Rent>(ptr1,ptr2,ptr3,cont15);
							r->setRentCost(cont14);
							r->setUUID(cont17);
							create(r);
							if(count==1)
								returnRoom(r,cont16);
							break;
	
						}
						
					}
					iterator++;
				}
				catch(logic_error o)
				{
					cout<<o.what()<<endl;
				}
				}
		}
		file.close();
	}
}
bool RentManager::checkPresence(spRent rent)
{
	bool trigger=false;
	for(unsigned int i=0;i<getArchive().size();i++)
	{
		if(*rent==*getArchive()[i])
		{
			trigger=true;
			break;
		}
	}
	for(unsigned int i=0;i<getCurrent().size();i++)
	{
		if(*rent==*getCurrent()[i])
		{
			trigger=true;
			break;
		}
	}
	return trigger;
}
