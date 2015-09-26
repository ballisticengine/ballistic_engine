#include "misc/utils.hpp"

namespace Utils {

char *loadText(string fn) {
	char *ft;
	FILE *f=fopen(fn.c_str(),"rb");
	if(!f) {
            return 0;
        }
        fseek(f,0,SEEK_END);
	size_t size=ftell(f);
	fseek(f,0,SEEK_SET);
	ft=new char[size+2];
	
	fread(ft,1,size,f);
	ft[size]=0;
	fclose(f);
	return ft;
}

string getExt(string fn) {
    size_t dotpos = fn.find_last_of(".");
    string ext = fn.substr(dotpos + 1, fn.size());
    return ext;
}


}