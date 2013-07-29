#include "locate.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace red
{
	void Rlocate::setLoc(float x,float y,float z)
	{
		this->lx = x;
		this->ly = y;
        this->lz = z;
	}
	void Rlocate::setLocX(float a)
	{
        this->lx = a;
	}
	void Rlocate::setLocY(float a)
	{
        this->ly = a;
	}
	void Rlocate::setLocZ(float a)
	{
        this->lz = a;
	}

	void Rlocate::setRot(float x,float y,float z)
	{
        this->rx = fmod(x,360);
        this->ry = fmod(y,360);
        this->rz = fmod(z,360);
	}
	void Rlocate::setRotX(float a)
	{
        this->rx = fmod(a,360);
	}
	void Rlocate::setRotY(float a)
	{
        this->ry = fmod(a,360);
	}
	void Rlocate::setRotZ(float a)
	{
        this->rz = fmod(a,360);
	}

    float* Rlocate::getLoc()
    {
        float* pos = (float*) malloc(sizeof(float) * 4);
        pos[0] = this->lx;
        pos[1] = this->ly;
        pos[2] = this->lz;
        pos[3] = 1;

        return pos;
    }
	float Rlocate::getLocX()
	{
		return this->lx;
	}
	float Rlocate::getLocY()
	{
		return this->ly;
	}
	float Rlocate::getLocZ()
	{
		return this->lz;
	}

	float Rlocate::getRotX()
	{
		return this->rx;
	}
	float Rlocate::getRotY()
	{
		return this->ry;
	}
	float Rlocate::getRotZ()
	{
		return this->rz;
    }

    int l_Rlocate_constructor(lua_State * l)
    {
        //const char * name = luaL_checkstring(l, 1);

        Rlocate ** udata = (Rlocate **) lua_newuserdata(l, sizeof(Rlocate *));
        *udata = new Rlocate();

        luaL_getmetatable(l, "luaL_Rlocate");

        lua_setmetatable(l, -2);

        return 1;
    }

    Rlocate * l_CheckRlocate(lua_State * l, int n)
    {
        return *(Rlocate **)luaL_checkudata(l, n, "luaL_Rlocate");
    }

    int l_Rlocate_setLoc(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setLoc(x,y,z);

        return 1;
    }
    int l_Rlocate_setLocX(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocX(x);

        return 1;
    }
    int l_Rlocate_setLocY(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setLocY(y);

        return 1;
    }
    int l_Rlocate_setLocZ(lua_State * l)
    {

        Rlocate * locate = l_CheckRlocate(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setLocZ(z);

        return 1;
    }

    int l_Rlocate_setRot(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setRot(x,y,z);

        return 1;
    }
    int l_Rlocate_setRotX(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setRotX(x);

        return 1;
    }
    int l_Rlocate_setRotY(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setRotY(y);

        return 1;
    }
    int l_Rlocate_setRotZ(lua_State * l)
    {

        Rlocate * locate = l_CheckRlocate(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setRotZ(z);

        return 1;
    }
    int l_Rlocate_getLocX(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getLocX());

        return 1;
    }
    int l_Rlocate_getLocY(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getLocY());

        return 1;
    }
    int l_Rlocate_getLocZ(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getLocZ());

        return 1;
    }
    int l_Rlocate_getRotX(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getRotX());

        return 1;
    }
    int l_Rlocate_getRotY(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getRotY());

        return 1;
    }
    int l_Rlocate_getRotZ(lua_State * l)
    {
        Rlocate * locate = l_CheckRlocate(l, 1);
        lua_pushnumber(l,locate->getRotZ());

        return 1;
    }
    int l_Rlocate_destructor(lua_State * l)
    {
        Rlocate * foo = l_CheckRlocate(l, 1);
        delete foo;

        return 0;
    }

    void RegisterRlocate(lua_State *l)
    {
        luaL_Reg sRlocateRegs[] =
        {
            { "new", l_Rlocate_constructor },

            { "setLoc", l_Rlocate_setLoc },
            { "setLocX", l_Rlocate_setLocX },
            { "setLocY", l_Rlocate_setLocY },
            { "setLocZ", l_Rlocate_setLocZ },

            { "getLocX", l_Rlocate_getLocX },
            { "getLocY", l_Rlocate_getLocY },
            { "getLocZ", l_Rlocate_getLocZ },

            { "setRotX", l_Rlocate_setRotX },
            { "setRotY", l_Rlocate_setRotY },
            { "setRotZ", l_Rlocate_setRotZ },
            { "getRotX", l_Rlocate_getRotX },
            { "getRotY", l_Rlocate_getRotY },
            { "getRotZ", l_Rlocate_getRotZ },

            { "__gc", l_Rlocate_destructor },
            { NULL, NULL }
        };

        // Create a luaL metatable. This metatable is not
        // exposed to Lua. The "luaL_Rlocate" label is used by luaL
        // internally to identity things.
        luaL_newmetatable(l, "luaL_Rlocate");

        // Register the C functions _into_ the metatable we just created.
        //luaL_register(l, NULL, sRlocateRegs); --> VERSION <= 5.1
        luaL_setfuncs(l,sRlocateRegs,0);

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rlocate"   |-1
        lua_pushvalue(l, -1);

        // The Lua stack at this point looks like this:
        //
        //     2| metatable "luaL_Rlocate"   |-1
        //     1| metatable "luaL_Rlocate"   |-2

        // Set the "__index" field of the metatable to point to itself
        // This pops the stack
        lua_setfield(l, -1, "__index");

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rlocate"   |-1

        // The luaL_Rlocate metatable now has the following fields
        //     - __gc
        //     - __index
        //     - add
        //     - new

        // Now we use setglobal to officially expose the luaL_Rlocate metatable
        // to Lua. And we use the name "Rlocate".
        //
        // This allows Lua scripts to _override_ the metatable of Rlocate.
        // For high security code this may not be called for but
        // we'll do this to get greater flexibility.
        lua_setglobal(l, "Rlocate");
    }
}



