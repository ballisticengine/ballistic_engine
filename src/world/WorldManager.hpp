#ifndef WORLDMANAGER_HPP
#define	WORLDMANAGER_HPP

#include "world/World.hpp"
#include "misc/singleton.hpp"

class WorldManager : public Singleton<WorldManager> {
protected:
    World *world;
public:
    World *getCurrentWorld();
    void setWorld(World *w);
    WorldManager();
    ~WorldManager();
    bool saveInto(string file_name);
};


#endif	

