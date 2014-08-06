#ifndef TEXTUREFACTORY_H
#define TEXTUREFACTORY_H

#include "factory.hpp"
#include "texture.hpp"

class textureFactory :  public factory, public singleton<textureFactory> {
protected:
		virtual void * actualLoad(string fn);
		
};

#endif