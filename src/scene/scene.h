#include "../object/object.h"
#include "../wavefront/wavefront.h"
#include "../light/light.h"

#include <vector>
#include <iostream>


#include <lua5.2/lua.hpp>

#ifndef __SCENE_H__
#define __SCENE_H__

namespace red
{
    class Rscene
    {
        public:
            Rscene();
            ~Rscene();
            std::vector<Rwavefront*> getWavefrontObjects();
            void	addWavefront(Rwavefront *);
            void	removeWavefront(Rwavefront *);
            void    addLightLamp(RlightLamp* obj);
            //void	setObject(Robject *); //array de objetos
            std::vector<Rwavefront*> WavefrontObjects;
            std::vector<RlightLamp*> LightLamps;

    };
void RegisterRscene(lua_State *l);
}
#endif
