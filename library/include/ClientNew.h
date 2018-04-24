#ifndef  CLIENTNEW_H
#define  CLIENTNEW_H
#include "ClientType.h"
namespace Hotel
{
	class ClientNew : public ClientType
	{
		public:
		ClientNew():
		ClientType(2)
		{}
		
		double getDiscount(int);
		
	};
}
#endif
