#include "../locate/locate.h"
#include <iostream>
#include <GL/gl.h>
//#include "../util/lua_typed_enums.h"

#ifndef LIGHT_H
#define LIGHT_H

namespace red {

    class RlightLamp:public Rlocate{

        public:
            RlightLamp(const char*);
            ~RlightLamp(){}
            void setAmbient(float  amb[]);
            void setDiffuse(float  dif[]);
            void setSpecular(float spe[]);

            float* getAmbient();
            float* getDiffuse();
            float* getSpecular();

            unsigned char typeLight;
            const char* uid;
            private:
                float *ambient;
                float *diffuse;
                float *specular;



    };
    RlightLamp * l_CheckRlightLamp(lua_State * l, int n);
    void RegisterRlightLamp(lua_State *l);

}

#endif // LIGHT_H
