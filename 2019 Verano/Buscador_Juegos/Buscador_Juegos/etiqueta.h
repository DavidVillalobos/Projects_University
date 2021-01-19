#ifndef ETIQUETA_H
#define ETIQUETA_H
#include <sstream>
using namespace std;

class etiqueta {
private:
	string info;
	etiqueta *sig;
public:
	etiqueta(string,etiqueta*);
	string getInfo();
	etiqueta *getSig();
	void setInfo(string);
	void setSig(etiqueta*);
	~etiqueta();
};
#endif 