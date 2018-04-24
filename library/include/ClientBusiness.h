#ifndef  CLIENTBUSINESS_H
#define  CLIENTBUSINESS_H
#include "ClientType.h"
namespace Hotel
{
	class ClientBusiness : public ClientType
	{
		public:
		ClientBusiness():
		ClientType(10)
		{}
		
		double getDiscount(int);
		
	};
}
#endif
