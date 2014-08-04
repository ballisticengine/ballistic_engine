#include <map>
#include <string>
using namespace std;
#include "singleton.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/
class loader : public singleton<loader>  {
protected:
	map <string,void *> items;
	virtual void * actualLoad(string fn) {
	 return 0;
	}
public:
	
	virtual void * get(string fn); //potem w dzieciach mo�na tu prze�adowa� na np. shape * get
};