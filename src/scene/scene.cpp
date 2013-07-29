

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <SOIL/SOIL.h>
#include "../render/render.h"
#include "scene.h"
#include "../util/lua_typed_enums.h"


namespace red
{
    Rscene::Rscene(){
        this->fog_enable = false;
        this->fog_color[0] = 1;
        this->fog_color[1] = 1;
        this->fog_color[2] = 1;
        this->fog_color[3] = 1.0;
        this->fog_density = 1;
        this->fog_far = 100.0;
        this->fog_near = 5.0;
        this->fog_enable = false;
        this->fog_type = GL_LINEAR;

    }
	Rscene::~Rscene(){}

    std::vector<Rwavefront *> Rscene::getWavefrontObjects()
	{
		return this->WavefrontObjects;
	}
	void Rscene::addWavefront(Rwavefront* obj)
	{	
        this->WavefrontObjects.push_back(obj);
	}
    void Rscene::addLightLamp(RlightLamp* obj)
    {
        this->LightLamps.push_back(obj);
    }

	void Rscene::removeWavefront(Rwavefront *obj)
	{
        /*int l = sizeof(this->objects)/sizeof(Rwavefront);
		int i,j;
	
		for(i=0;i<l;i++)
			if(this->objects[i].getUID() == obj->getUID())
			{
				for(j=i;j<l-1;j++)
					this->objects[j] = this->objects[j+1];
				obj->~Rwavefront();
			}	
    */
	}
    /*void Rscene::addPrimitiveObject(int type)
	{
        //this->primitive = type;
    }*/

    /*
     * FOG Settings
     */
    void Rscene::enableFog()
    {
        glFogi(GL_FOG_MODE, this->fog_type);    // Fog Mode
        glFogfv(GL_FOG_COLOR, this->fog_color);            // Set Fog Color
        glFogf(GL_FOG_DENSITY, this->fog_density);              // How Dense Will The Fog Be
        glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
        glFogf(GL_FOG_START, this->fog_near);             // Fog Start Depth
        glFogf(GL_FOG_END, this->fog_far);               // Fog End Depth
        glEnable(GL_FOG);
    }
    void Rscene::disableFog()
    {
        glDisable(GL_FOG);
    }
    void Rscene::setFogColor(float r,float g, float b)
    {
        this->fog_color[0] = r;
        this->fog_color[1] = g;
        this->fog_color[2] = b;
        this->fog_color[3] = 1;
    }
    void Rscene::setFogDensity(float d)
    {
        this->fog_density = d;
    }
    void Rscene::setFogNearFar(float near, float far)
    {
        this->fog_near = near;
        this->fog_far = far;
    }
    void Rscene::setFogType(int t)
    {
        this->fog_type = t;
    }
    /*
     * END FOG Settings
     */
	
	int l_Rscene_constructor(lua_State * l)
	{
		//const char * name = luaL_checkstring(l, 1);

		
		Rscene ** udata = (Rscene **) lua_newuserdata(l, sizeof(Rscene *));
		*udata = new Rscene();

		luaL_getmetatable(l, "luaL_Rscene");

		lua_setmetatable(l, -2);

				
		return 1;
	}

	Rscene * l_CheckRscene(lua_State * l, int n)
	{
		return *(Rscene **)luaL_checkudata(l, n, "luaL_Rscene");
	}


    int l_Rscene_addWavefront(lua_State * l)
	{
		//initWindow(argc,argv,400,400);
        Rscene * foo = l_CheckRscene(l, 1);
        Rwavefront *w = l_CheckRwavefront(l, 2);
		
        foo->addWavefront(w);
		return 0;
    }
    int l_Rscene_addLightLamp(lua_State * l)
    {
        //initWindow(argc,argv,400,400);
        Rscene * s = l_CheckRscene(l, 1);
        RlightLamp *w = l_CheckRlightLamp(l, 2);


        s->addLightLamp(w);
        return 0;
    }

	int l_Rscene_destructor(lua_State * l)
	{
		Rscene * foo = l_CheckRscene(l, 1);
		delete foo;

		return 0;
	}
    int l_Rscene_fogEnable(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        foo->fog_enable = true;
        return 0;
    }
    int l_Rscene_fogDisable(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        foo->fog_enable = false;
        return 0;
    }
    int l_Rscene_setFogColor(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        float r,g,b;
        r = luaL_checknumber(l, 2);
        g = luaL_checknumber(l, 3);
        b = luaL_checknumber(l, 4);
        foo->setFogColor(r,g,b);
        return 0;
    }
    int l_Rscene_setFogNearFar(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        float n,f;
        n = luaL_checknumber(l, 2);
        f = luaL_checknumber(l, 3);
        foo->setFogNearFar(n,f);
        return 0;
    }
    int l_Rscene_setFogDensity(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        float d;
        d = luaL_checknumber(l, 2);
        foo->setFogDensity(d);
        return 0;
    }
    int l_Rscene_setFogType(lua_State * l)
    {
        Rscene * foo = l_CheckRscene(l, 1);
        int t;
        t = luaL_checknumber(l, 2);
        foo->setFogType(t);
        return 0;
    }

	void RegisterRscene(lua_State *l)
	{
		luaL_Reg sRsceneRegs[] =
		{
		    { "new", l_Rscene_constructor },
		    { "__gc", l_Rscene_destructor },
			{"name",},
            {"addWavefront",l_Rscene_addWavefront},
            {"addLightLamp",l_Rscene_addLightLamp},
            {"fogEnable",l_Rscene_fogEnable},
            {"fogDisable",l_Rscene_fogDisable},
            {"setFogColor",l_Rscene_setFogColor},
            {"setFogNearFar",l_Rscene_setFogNearFar},
            {"setFogDensity",l_Rscene_setFogDensity},
            {"setFogType",l_Rscene_setFogType},
            { NULL, NULL }
		};

		luaL_newmetatable(l, "luaL_Rscene");

		//luaL_register(l, NULL, sRsceneRegs); --> VERSION <= 5.1
		luaL_setfuncs(l,sRsceneRegs,0);

		lua_pushvalue(l, -1);

		lua_setfield(l, -1, "__index");

		lua_setglobal(l, "Rscene");

        add_enum_to_lua( l, "Rfog"
        ,"FOG_LINEAR",GL_LINEAR
        ,"FOG_EXP", GL_EXP
        ,"FOG_EXP2",GL_EXP2,0);

	}

}
