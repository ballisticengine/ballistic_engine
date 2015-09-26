#ifndef PRELOADSTORE_HPP
#define	PRELOADSTORE_HPP

#include <map>
#include <string>

using namespace std;

#include "misc/singleton.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"

typedef map<string,Shape*> preload_map;
typedef map<string,Ballistic::Types::Texture *> tex_preload_map;

class PreloadStore : public Singleton<PreloadStore> {
    public:
        preload_map shape_preloads;
        tex_preload_map tex_preloads;
        preload_map getAllShapePreloads();
        
};

#endif	

