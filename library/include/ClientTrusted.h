#ifndef  CLIENTTRUSTED_H
#define  CLIENTTRUSTED_H
#include "ClientType.h"
namespace Hotel
{
	class ClientTrusted : public ClientType
	{
		public:
		ClientTrusted():
		ClientType(4)
		{}
		
		double getDiscount(int);
		
	};
}
#endif
//f
