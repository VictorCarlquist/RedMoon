#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <SOIL/SOIL.h>

#include "scene.h"
#include "../render/render.h"

namespace red
{
    Rscene::Rscene(){

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

	int l_Rscene_destructor(lua_State * l)
	{
		Rscene * foo = l_CheckRscene(l, 1);
		delete foo;

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
		    { NULL, NULL }
		};

		// Create a luaL metatable. This metatable is not 
		// exposed to Lua. The "luaL_Rscene" label is used by luaL
		// internally to identity things.
		luaL_newmetatable(l, "luaL_Rscene");

		// Register the C functions _into_ the metatable we just created.
		//luaL_register(l, NULL, sRsceneRegs); --> VERSION <= 5.1
		luaL_setfuncs(l,sRsceneRegs,0);

		// The Lua stack at this point looks like this:
		//     
		//     1| metatable "luaL_Rscene"   |-1
		lua_pushvalue(l, -1);

		// The Lua stack at this point looks like this:
		//     
		//     2| metatable "luaL_Rscene"   |-1
		//     1| metatable "luaL_Rscene"   |-2

		// Set the "__index" field of the metatable to point to itself
		// This pops the stack
		lua_setfield(l, -1, "__index");

		// The Lua stack at this point looks like this:
		//     
		//     1| metatable "luaL_Rscene"   |-1

		// The luaL_Rscene metatable now has the following fields
		//     - __gc
		//     - __index
		//     - add
		//     - new

		// Now we use setglobal to officially expose the luaL_Rscene metatable 
		// to Lua. And we use the name "Rscene".
		//
		// This allows Lua scripts to _override_ the metatable of Rscene.
		// For high security code this may not be called for but 
		// we'll do this to get greater flexibility.
		lua_setglobal(l, "Rscene");
	}
	
}
