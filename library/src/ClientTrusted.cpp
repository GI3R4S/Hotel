#include "ClientTrusted.h"
using namespace Hotel;
double ClientTrusted::getDiscount(int i)
{
	if (i<=3)
		return 0.95;
	else
		return 0.92;
}
