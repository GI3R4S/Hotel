#include "ClientBusiness.h"
using namespace Hotel;
double ClientBusiness::getDiscount(int i)
{
	return 1 - i*0.02;
}
