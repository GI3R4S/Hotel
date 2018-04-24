#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "Manager.h"
#include "/usr/include/boost/date_time/local_time/local_date_time.hpp"
using namespace Hotel;
BOOST_AUTO_TEST_SUITE(HotelSuiteCorrect)

BOOST_AUTO_TEST_CASE(clientTest) 
{
	//utworzenie
    spClient osoba = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
    BOOST_REQUIRE(osoba->getFirstName() == "Jan" and osoba->getLastName() == "Kowalski" 
		and osoba->getAdress() == "Ogrodowa 24" and osoba->getPersonalID() =="64021400278");
    
    //przeciazenie operatora <<
    boost::test_tools::output_test_stream output;
    output << *osoba;
    BOOST_CHECK(output.is_equal("Jan\nKowalski\nOgrodowa 24\n64021400278\n"));  
   
    //operator rownosci
    spClient osoba2 = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	BOOST_REQUIRE(*osoba==*osoba2);
	
	//typy klienta i liczba maks. wypozyczen
	BOOST_REQUIRE(osoba->getClientTypeName() == "Nowy klient"); 
	BOOST_REQUIRE_EQUAL(osoba->getMaxCount(),2);
	osoba->changeClientType(4);
	BOOST_REQUIRE(osoba->getClientTypeName() == "Zaufany klient"); 
	BOOST_REQUIRE_EQUAL(osoba->getMaxCount(),4);
	osoba->changeClientType(6);
	BOOST_REQUIRE(osoba->getClientTypeName() == "Biznesowy klient"); 
	BOOST_REQUIRE_EQUAL(osoba->getMaxCount(),10);
}

BOOST_AUTO_TEST_CASE(workerTest) 
{
	//utworzenie
	spWorker pracownik = make_shared<Worker>("Jan","Kowalski","Ogrodowa 24","64021400278","Recepcjonista",100);
	BOOST_REQUIRE(pracownik->getFirstName() == "Jan" and pracownik->getLastName() == "Kowalski" and pracownik->getAdress() == "Ogrodowa 24" 
		and pracownik->getPersonalID() =="64021400278" and pracownik->getJobType() == "Recepcjonista" and pracownik->getPayPerDay() == 100);
	
	//przeciazenie operatora <<
	boost::test_tools::output_test_stream output;
    output << *pracownik;
    BOOST_CHECK(output.is_equal("Jan\nKowalski\nOgrodowa 24\n64021400278\nRecepcjonista\n100\n"));  
    
    //operator rownosci
    spWorker pracownik2 = make_shared<Worker>("Jan","Kowalski","Ogrodowa 24","64021400278","Recepcjonista",100);
	BOOST_REQUIRE(*pracownik==*pracownik2);
}

BOOST_AUTO_TEST_CASE(roomTest) 
{
	//utworzenie
	spRoom pokoj = make_shared<Room>(2,322,"Pokoj testowy nr 1",30);
    BOOST_REQUIRE(pokoj->getMaxCapacity() == 2 and pokoj->getID() == 322 and pokoj->getDescription() == "Pokoj testowy nr 1" and pokoj->getDailyCost() == 30);
		
    //przeciazenie operatora <<
    boost::test_tools::output_test_stream output;
    output << *pokoj;
    BOOST_CHECK(output.is_equal("2\n322\nPokoj testowy nr 1\n30\n"));  
    
	//operator rownosci
    spRoom pokoj2 = make_shared<Room>(2,322,"Pokoj testowy nr 1",30);
	BOOST_REQUIRE(*pokoj==*pokoj2);
}

BOOST_AUTO_TEST_CASE(rentTest) 
{
	//utworzenie
	spClient klient = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	spWorker pracownik = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	spRoom pokoj = make_shared<Room>(2,322,"Pokoj testowy nr 1",30);
	spLDT start = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spRent rent = make_shared<Rent>(klient,pokoj,pracownik,start);
	BOOST_REQUIRE(rent->getClient() == klient and rent->getWorker() == pracownik and rent->getRoom() == pokoj and *(rent->getRentStart()) == *start);
	
	//zmiana UUID
	random_generator gen;
	uuid ID;
	ID=gen();
	BOOST_REQUIRE(rent->getUUID() != ID);
	rent->setUUID(ID);
	BOOST_REQUIRE(rent->getUUID() == ID);
	
	//koszt
	rent->setRentCost(14.5);
	BOOST_REQUIRE(rent->getRentCost() == 14.5);
	
	//zakonczenie
	spLDT koniec = make_shared<local_date_time>(ptime{date{2018, 01, 10}, time_duration{7, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	BOOST_REQUIRE(rent->rentDuration() == 0);
	rent->setRentEnd(koniec);
	BOOST_REQUIRE(rent->rentDuration() == 6);
	BOOST_REQUIRE(*(rent->getRentEnd()) == *koniec); 
}

BOOST_AUTO_TEST_CASE(eventTest)
{
	spClient klient = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	spWorker pracownik = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	spLDT ldt = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spLDT ldt2 = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spEvent event = make_shared<Event>(-20,"Stolowka - obiad dwudaniowy",ldt);
	BOOST_REQUIRE(event->getBalance() == -20 and event->getDescription() == "Stolowka - obiad dwudaniowy" and *(event->getLdt()) == *ldt);
	spEvent event2 = make_shared<Event>(30,"Pochwala od kilku klientow",ldt2);
	BOOST_REQUIRE(event2->getBalance() == 30 and event2->getDescription() == "Pochwala od kilku klientow" and *(event2->getLdt()) == *ldt);
	boost::test_tools::output_test_stream output;
    output << *event2;
    BOOST_CHECK(output.is_equal("30\nPochwala od kilku klientow\n2018-Jan-04 08:00:00 CET\n"));  
	spEvent event3 = make_shared<Event>(-15,"Stolowka - kolacja",ldt);
	
	klient->addEvent(event);
	klient->addEvent(event3);
	vector<spEvent> kli;
	kli=klient->getAdditionalCosts();
	double sum = 0;
	for(unsigned int i=0;i<kli.size();i++)
		{
			sum+=kli[i]->getBalance();
		}
	BOOST_REQUIRE(sum == -35);
	
	pracownik->addEvent(event2);
	vector<spEvent> prac;
	prac=pracownik->getBonuses();
	double sum2 = 0;
	for(unsigned int i=0;i<prac.size();i++)
		{
			sum2+=prac[i]->getBalance();
		}
	BOOST_REQUIRE(sum2 == 30);
}
BOOST_AUTO_TEST_CASE(repozytoria)
{
	//create, remove
	spClient klient = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	ClientRepository * cr = new ClientRepository();
	BOOST_REQUIRE(cr->getAll().size() == 0);
	cr->create(klient);
	BOOST_REQUIRE(cr->getAll().size() == 1);
	cr->remove(klient);
	BOOST_REQUIRE(cr->getAll().size() == 0);
	
	spWorker pracownik = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	WorkerRepository * wr = new WorkerRepository();
	BOOST_REQUIRE(wr->getAll().size() == 0);
	wr->create(pracownik);
	BOOST_REQUIRE(wr->getAll().size() == 1);
	wr->remove(pracownik);
	BOOST_REQUIRE(wr->getAll().size() == 0);
	
	spRoom pokoj = make_shared<Room>(2,322,"Pokoj testowy nr 1",30);
	RoomRepository * rr = new RoomRepository();
	BOOST_REQUIRE(rr->getAll().size() == 0);
	rr->create(pokoj);
	BOOST_REQUIRE(rr->getAll().size() == 1);
	rr->remove(pokoj);
	BOOST_REQUIRE(rr->getAll().size() == 0);
	
	spLDT start = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spRent rent = make_shared<Rent>(klient,pokoj,pracownik,start);
	RentRepository * rer = new RentRepository();
	BOOST_REQUIRE(rer->getAll().size() == 0);
	rer->create(rent);
	BOOST_REQUIRE(rer->getAll().size() == 1);
	rer->remove(rent);
	BOOST_REQUIRE(rer->getAll().size() == 0);
	
	delete rer;
	delete rr;
	delete wr;
	delete cr;
}

BOOST_AUTO_TEST_CASE(managery)
{
	//add, remove
	spClient klient = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	ClientManager * cm = new ClientManager();
	BOOST_REQUIRE(cm->getAll().size() == 0);
	cm->addClient(klient);
	BOOST_REQUIRE(cm->getAll().size() == 1);
	cm->removeClient(klient);
	BOOST_REQUIRE(cm->getAll().size() == 0);
	
	//getAllClientAdditionalCosts
	spLDT ldt = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spEvent event = make_shared<Event>(-20,"Stolowka - obiad dwudaniowy",ldt);
	klient->addEvent(event);
	vector<spEvent> kli;
	kli=cm->getAllClientAdditionalCosts(klient);
	double suma = 0;
	for(unsigned int i=0;i<kli.size();i++)
		{
			suma+=kli[i]->getBalance();
		}
	BOOST_REQUIRE(suma == -20);
	
	
	spWorker pracownik = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	WorkerManager * wm = new WorkerManager();
	BOOST_REQUIRE(wm->getAll().size() == 0);
	wm->addWorker(pracownik);
	BOOST_REQUIRE(wm->getAll().size() == 1);
	wm->removeWorker(pracownik);
	BOOST_REQUIRE(wm->getAll().size() == 0);
	
	//getAllWorkerBonuses
	spEvent event2 = make_shared<Event>(30,"Pochwala od kilku klientow",ldt);
	pracownik->addEvent(event2);
	kli=wm->getAllWorkerBonuses(pracownik);
	suma = 0;
	for(unsigned int i=0;i<kli.size();i++)
		{
			suma+=kli[i]->getBalance();
		}
	BOOST_REQUIRE(suma == 30);
	

	spRoom pokoj = make_shared<Room>(2,322,"Pokoj testowy nr 1",30);
	RoomManager * rm = new RoomManager();
	BOOST_REQUIRE(rm->getAll().size() == 0);
	rm->addRoom(pokoj);
	BOOST_REQUIRE(rm->getAll().size() == 1);
	rm->removeRoom(pokoj);
	BOOST_REQUIRE(rm->getAll().size() == 0);
	
	
	spRent rent = make_shared<Rent>(klient,pokoj,pracownik,ldt);
	RentManager * rem = new RentManager();
	BOOST_REQUIRE(rem->getAll().size() == 0);
	rem->create(rent);
	BOOST_REQUIRE(rem->getCurrent().size() == 1);
	BOOST_REQUIRE(rem->getArchive().size() == 0);
	rem->returnRoom(rent, ldt);
	BOOST_REQUIRE(rem->getCurrent().size() == 0);
	BOOST_REQUIRE(rem->getArchive().size() == 1);
	
	delete rem; 
	delete rm;
	delete wm;
	delete cm;	
}

BOOST_AUTO_TEST_CASE(odczyt_zapis)
{
	spRoom r1 = make_shared<Room>(2,322,"Pokoj testowy nr 1",13);
	spRoom r2 = make_shared<Room>(2,323,"Pokoj testowy nr 2",13);
	spRoom r3 = make_shared<Room>(2,324,"Pokoj testowy nr 3",13);
	RoomManager * rm = new RoomManager();
	BOOST_REQUIRE(rm->getAll().size() == 0);
	rm->addRoom(r1);
	rm->addRoom(r2);
	rm->addRoom(r3);
	BOOST_REQUIRE(rm->getAll().size() == 3);
	rm->writeToFile("pokoje.txt");
	rm->removeRoom(r1);
	rm->removeRoom(r2);
	rm->removeRoom(r3);
	BOOST_REQUIRE(rm->getAll().size() == 0);
	rm->readFromFile("pokoje.txt");
	BOOST_REQUIRE(rm->getAll().size() == 3);
	BOOST_REQUIRE(rm->getAll()[2]->getMaxCapacity() == 2 and rm->getAll()[2]->getID() == 324 
		and rm->getAll()[2]->getDescription() == "Pokoj testowy nr 3" and rm->getAll()[2]->getDailyCost() == 13);
		
		
	spClient klient = make_shared<Client>("Jan","Kowalski","Zawodowa 24","64021400278");
	spClient klient2 = make_shared<Client>("Jane","Howalski","Ogrodowa 24","65021400278");
	spClient klient3 = make_shared<Client>("Janek","Powalski","Porodowa 24","66021400278");
	ClientManager * cm = new ClientManager();
	BOOST_REQUIRE(cm->getAll().size() == 0);
	cm->addClient(klient);
	cm->addClient(klient2);
	cm->addClient(klient3);
	BOOST_REQUIRE(cm->getAll().size() == 3);
	cm->writeToFile("klienci.txt");
	cm->removeClient(klient);
	cm->removeClient(klient2);
	cm->removeClient(klient3);
	BOOST_REQUIRE(cm->getAll().size() == 0);
	cm->readFromFile("klienci.txt");
	BOOST_REQUIRE(cm->getAll().size() == 3);
	BOOST_REQUIRE(cm->getAll()[1]->getFirstName() == "Jane" and cm->getAll()[1]->getLastName() == "Howalski" 
		and cm->getAll()[1]->getAdress() == "Ogrodowa 24" and cm->getAll()[1]->getPersonalID() =="65021400278");
	
	spLDT ldt = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spClient klient4 = make_shared<Client>("Jan","Kowalski","Zawodowa 24","64021400278");
	spEvent event = make_shared<Event>(-20,"Stolowka - obiad dwudaniowy",ldt);
	spEvent event2 = make_shared<Event>(-15,"Stolowka - kolacja",ldt);
	ClientManager * em = new ClientManager();
	em->addClient(klient4);
	BOOST_REQUIRE(em->getAllClientAdditionalCosts(klient4).size() == 0);
	klient4->addEvent(event);
	klient4->addEvent(event2);
	BOOST_REQUIRE(int(em->getAllClientAdditionalCosts(klient4).size()) == 2);
	em->writeClientEventsToFile("eventy.txt",klient4);
	klient4->removeEvent(event2);
	klient4->removeEvent(event);
	BOOST_REQUIRE(em->getAllClientAdditionalCosts(klient4).size() == 0);
	em->readClientEventsFromFile("eventy.txt",klient4);
	BOOST_REQUIRE(int(em->getAllClientAdditionalCosts(klient4).size()) == 2);
	BOOST_REQUIRE(em->getAllClientAdditionalCosts(klient4)[0]->getBalance() == -20 
		and em->getAllClientAdditionalCosts(klient4)[0]->getDescription() == "Stolowka - obiad dwudaniowy" 
		and *(em->getAllClientAdditionalCosts(klient4)[0]->getLdt()) == *ldt); 
		
	spEvent event3 = make_shared<Event>(30,"Pochwala od kilku klientow",ldt);
	spEvent event4 = make_shared<Event>(60,"Nadgodziny",ldt);
	spWorker pracownik = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	WorkerManager * wm = new WorkerManager();
	wm->addWorker(pracownik);
	BOOST_REQUIRE(wm->getAllWorkerBonuses(pracownik).size() == 0);
	pracownik->addEvent(event3);
	pracownik->addEvent(event4);
	BOOST_REQUIRE(wm->getAllWorkerBonuses(pracownik).size() == 2);
	wm->writeWorkerEventsToFile("eventyPrac.txt",pracownik);
	pracownik->removeEvent(event3);
	pracownik->removeEvent(event4);
	BOOST_REQUIRE(wm->getAllWorkerBonuses(pracownik).size() == 0);
	wm->readWorkerEventsFromFile("eventyPrac.txt",pracownik);
	BOOST_REQUIRE_EQUAL(wm->getAllWorkerBonuses(pracownik).size(), 2);
	BOOST_REQUIRE(wm->getAllWorkerBonuses(pracownik)[0]->getBalance() == 30 
		and wm->getAllWorkerBonuses(pracownik)[0]->getDescription() == "Pochwala od kilku klientow" 
		and *(wm->getAllWorkerBonuses(pracownik)[0]->getLdt()) == *ldt);
	
	spLDT ldt2 = make_shared<local_date_time>(ptime{date{2018, 01, 07}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spRent rent = make_shared<Rent>(klient,r1,pracownik,ldt);
	spRent rent2 = make_shared<Rent>(klient2,r2,pracownik,ldt);
	spRent rent3 = make_shared<Rent>(klient4,r3,pracownik,ldt);
	RentManager * rem = new RentManager();
	rem->create(rent);
	rem->create(rent2);
	rem->create(rent3);
	BOOST_REQUIRE(rem->getCurrent().size() == 3);
	BOOST_REQUIRE(rem->getArchive().size() == 0);
	rem->returnRoom(rent, ldt2);
	rem->returnRoom(rent3, ldt2);
	BOOST_REQUIRE(rem->getCurrent().size() == 1);
	BOOST_REQUIRE(rem->getArchive().size() == 2);
	rem->saveAll("archive","current");
	
	RentManager * rem2 = new RentManager();
	BOOST_REQUIRE(rem2->getCurrent().size() == 0);
	BOOST_REQUIRE(rem2->getArchive().size() == 0);
	rem2->loadAll(cm,wm,rm,"archive","current");
	BOOST_REQUIRE(rem2->getCurrent().size() == 1);
	BOOST_REQUIRE(rem2->getArchive().size() == 2);
	
	delete rem2;
	delete rem; 
	delete wm;
	delete em;
	delete cm;
	delete rm;
}

BOOST_AUTO_TEST_CASE(ChangeClientTypeAndDiscount)
{
	RentManager * rem2 = new RentManager();
	spClient klient2 = make_shared<Client>("Jan","Kowalski","Ogrodowa 24","64021400278");
	ClientManager * cm = new ClientManager();
	cm->addClient(klient2);
	spWorker pracownik2 = make_shared<Worker>("Kamil","Nowacki","Zielona 62","87051600278","Recepcjonista",100);
	spRoom pokoj1 = make_shared<Room>(2,321,"Pokoj testowy nr 1",20);
	spRoom pokoj2 = make_shared<Room>(2,322,"Pokoj testowy nr 2",30);
	spRoom pokoj3 = make_shared<Room>(2,323,"Pokoj testowy nr 3",40);
	spRoom pokoj4 = make_shared<Room>(2,324,"Pokoj testowy nr 4",50);
	spRoom pokoj5 = make_shared<Room>(2,325,"Pokoj testowy nr 5",100);
	spRoom pokoj6 = make_shared<Room>(2,326,"Pokoj testowy nr 6",200);
	spLDT start = make_shared<local_date_time>(ptime{date{2018, 01, 04}, time_duration{8, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spLDT koniec = make_shared<local_date_time>(ptime{date{2018, 01, 05}, time_duration{7, 0, 0}},time_zone_ptr{new posix_time_zone{"CET"}});
	spRent rent1 = make_shared<Rent>(klient2,pokoj1,pracownik2,start);
	spRent rent2 = make_shared<Rent>(klient2,pokoj2,pracownik2,start);
	spRent rent3 = make_shared<Rent>(klient2,pokoj3,pracownik2,start);
	spRent rent4 = make_shared<Rent>(klient2,pokoj4,pracownik2,start);
	spRent rent5 = make_shared<Rent>(klient2,pokoj5,pracownik2,start);
	spRent rent6 = make_shared<Rent>(klient2,pokoj6,pracownik2,start);
	rem2->create(rent1);
	rem2->create(rent2);
	BOOST_REQUIRE(klient2->getClientTypeName() == "Nowy klient"); 
	rem2->returnRoom(rent1, koniec);
	BOOST_REQUIRE(rent1->getRentCost() == 20*1);
	rem2->returnRoom(rent2, koniec);
	BOOST_REQUIRE(rent2->getRentCost() == 30*1);
	rem2->create(rent3);
	rem2->create(rent4);
	rem2->returnRoom(rent3, koniec);
	BOOST_REQUIRE(rent3->getRentCost() == 40*1);
	BOOST_REQUIRE(klient2->getClientTypeName() == "Zaufany klient"); 
	rem2->returnRoom(rent4, koniec);
	BOOST_REQUIRE(rent4->getRentCost() == 50*0.95);
	rem2->create(rent5);
	rem2->create(rent6);
	rem2->returnRoom(rent5, koniec); 
	BOOST_REQUIRE(rent5->getRentCost() == 100*0.92);
	BOOST_REQUIRE(klient2->getClientTypeName() == "Biznesowy klient"); 
	rem2->returnRoom(rent6, koniec);
	BOOST_REQUIRE(rent6->getRentCost() == 200*0.9);
	delete cm;
	delete rem2;
}
BOOST_AUTO_TEST_SUITE_END()
