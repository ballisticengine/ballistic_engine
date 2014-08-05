#include <map>
#include <string>
using namespace std;
#include "singleton.hpp"

/*
Fabryka abstrakcyjna - zwraca pliki, je�li nie istniej� - �aduje
*/

template <typename T, typename S>
class factory : public singleton<S>  {
protected:
	map <string,T *> items;
	virtual T * actualLoad(string fn) {
	 return 0;
	}
public:
	
	 T * get(string fn); //potem w dzieciach mo�na tu prze�adowa� na np. shape * get
};