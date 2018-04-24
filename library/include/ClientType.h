#ifndef  CLIENTTYPE_H
#define  CLIENTTYPE_H
namespace Hotel
{
	class ClientType
	{	private:
		int maxCount;
		public:
		ClientType(int i):
		maxCount(i)
		{}
		
		virtual double getDiscount(int)=0;
		int getMaxCount();
	};
}
#endif
