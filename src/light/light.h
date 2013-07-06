#include "locate.h"
#include <iostream>
#include "../util/lua_typed_enums.h"

#ifndef LIGHT_H
#define LIGHT_H

namespace red {

    class Rlight:public Rlocate{

        public:
            Rlight(){


            };
            unsigned char typeLight;


            ~Rlight(){};

    };

}

#endif // LIGHT_H
