#include "utils.hpp"

namespace Utils {

char *loadText(string fn) {
	char *ft;
	FILE *f=fopen(fn.c_str(),"rb");
	fseek(f,0,SEEK_END);
	size_t size=ftell(f);
	fseek(f,0,SEEK_SET);
	ft=new char[size+2];
	
	fread(ft,1,size,f);
	ft[size]=0;
	fclose(f);
	return ft;
}
}