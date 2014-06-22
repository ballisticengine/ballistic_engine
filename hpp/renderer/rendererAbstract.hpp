#ifndef RENDERERABSTRACT_HPP
#define	RENDERERABSTRACT_HPP

#include "helpers/singleton.hpp"


class renderer : public(singleton) {
    renderer();
    virtual ~renderer();
};


#endif	/* RENDERERABSTRACT_HPP */

