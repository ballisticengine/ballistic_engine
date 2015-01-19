#ifndef PRELOADSTORE_HPP
#define	PRELOADSTORE_HPP

#include <map>
#include <string>

using namespace std;

#include "misc/singleton.hpp"
#include "types/shape.hpp"
#include "types/texture.hpp"

typedef map<string,shape*> preload_map;
typedef map<string,texture *> tex_preload_map;

class PreloadStore : public singleton<PreloadStore> {
    public:
        preload_map shape_preloads;
        tex_preload_map tex_preloads;
        preload_map getAllShapePreloads();
        
};

#endif	

