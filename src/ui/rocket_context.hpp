#ifndef ROCKET_CONTEXT_HPP
#define	ROCKET_CONTEXT_HPP

#include <Rocket/Core.h>

namespace RC = Rocket::Core;

class RocketContext : public RC::Context {
public:
    RC::ElementDocument * LoadStrDocument(char *document) {
        return this->LoadDocument(document);
    }
};

#endif	

