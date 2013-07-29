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

            void    enableFog();
            void    disableFog();
            void    setFogColor(float r, float g, float b);
            void    setFogDensity(float d);
            void    setFogNearFar(float near, float far);
            void    setFogType(int t);


            //void	setObject(Robject *); //array de objetos
            std::vector<Rwavefront*> WavefrontObjects;
            std::vector<RlightLamp*> LightLamps;
            bool    fog_enable;
        private:

            float   fog_near,fog_far;
            float   fog_density;
            float   fog_type;           //GL_LINEAR
            float   fog_color[4];

    };
void RegisterRscene(lua_State *l);
}
#endif
