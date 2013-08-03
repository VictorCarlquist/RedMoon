#include "placeable.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

namespace red
{
	void Rplaceable::setLoc(float x,float y,float z)
	{
		this->lx = x;
		this->ly = y;
        this->lz = z;
	}
	void Rplaceable::setLocX(float a)
	{
        this->lx = a;
	}
	void Rplaceable::setLocY(float a)
	{
        this->ly = a;
	}
	void Rplaceable::setLocZ(float a)
	{
        this->lz = a;
	}

	void Rplaceable::setRot(float x,float y,float z)
	{
        this->rx = fmod(x,360);
        this->ry = fmod(y,360);
        this->rz = fmod(z,360);
	}
	void Rplaceable::setRotX(float a)
	{
        this->rx = fmod(a,360);
	}
	void Rplaceable::setRotY(float a)
	{
        this->ry = fmod(a,360);
	}
	void Rplaceable::setRotZ(float a)
	{
        this->rz = fmod(a,360);
	}

    float* Rplaceable::getLoc()
    {
        float* pos = (float*) malloc(sizeof(float) * 4);
        pos[0] = this->lx;
        pos[1] = this->ly;
        pos[2] = this->lz;
        pos[3] = 1;

        return pos;
    }
	float Rplaceable::getLocX()
	{
		return this->lx;
	}
	float Rplaceable::getLocY()
	{
		return this->ly;
	}
	float Rplaceable::getLocZ()
	{
		return this->lz;
	}

	float Rplaceable::getRotX()
	{
		return this->rx;
	}
	float Rplaceable::getRotY()
	{
		return this->ry;
	}
	float Rplaceable::getRotZ()
	{
		return this->rz;
    }

    int l_Rplaceable_constructor(lua_State * l)
    {
        //const char * name = luaL_checkstring(l, 1);

        Rplaceable ** udata = (Rplaceable **) lua_newuserdata(l, sizeof(Rplaceable *));
        *udata = new Rplaceable();

        luaL_getmetatable(l, "luaL_Rplaceable");

        lua_setmetatable(l, -2);

        return 1;
    }

    Rplaceable * l_CheckRplaceable(lua_State * l, int n)
    {
        return *(Rplaceable **)luaL_checkudata(l, n, "luaL_Rplaceable");
    }

    int l_Rplaceable_setLoc(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        placeable->setLoc(x,y,z);

        return 1;
    }
    int l_Rplaceable_setLocX(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float x = luaL_checknumber(l, 2);

        placeable->setLocX(x);

        return 1;
    }
    int l_Rplaceable_setLocY(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float y = luaL_checknumber(l, 2);

        placeable->setLocY(y);

        return 1;
    }
    int l_Rplaceable_setLocZ(lua_State * l)
    {

        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float z = luaL_checknumber(l,2);

        placeable->setLocZ(z);

        return 1;
    }

    int l_Rplaceable_setRot(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        placeable->setRot(x,y,z);

        return 1;
    }
    int l_Rplaceable_setRotX(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float x = luaL_checknumber(l, 2);

        placeable->setRotX(x);

        return 1;
    }
    int l_Rplaceable_setRotY(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float y = luaL_checknumber(l, 2);

        placeable->setRotY(y);

        return 1;
    }
    int l_Rplaceable_setRotZ(lua_State * l)
    {

        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        float z = luaL_checknumber(l,2);

        placeable->setRotZ(z);

        return 1;
    }
    int l_Rplaceable_getLocX(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getLocX());

        return 1;
    }
    int l_Rplaceable_getLocY(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getLocY());

        return 1;
    }
    int l_Rplaceable_getLocZ(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getLocZ());

        return 1;
    }
    int l_Rplaceable_getRotX(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getRotX());

        return 1;
    }
    int l_Rplaceable_getRotY(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getRotY());

        return 1;
    }
    int l_Rplaceable_getRotZ(lua_State * l)
    {
        Rplaceable * placeable = l_CheckRplaceable(l, 1);
        lua_pushnumber(l,placeable->getRotZ());

        return 1;
    }
    int l_Rplaceable_destructor(lua_State * l)
    {
        Rplaceable * foo = l_CheckRplaceable(l, 1);
        delete foo;

        return 0;
    }

    void RegisterRplaceable(lua_State *l)
    {
        luaL_Reg sRplaceableRegs[] =
        {
            { "new", l_Rplaceable_constructor },

            { "setLoc", l_Rplaceable_setLoc },
            { "setLocX", l_Rplaceable_setLocX },
            { "setLocY", l_Rplaceable_setLocY },
            { "setLocZ", l_Rplaceable_setLocZ },

            { "getLocX", l_Rplaceable_getLocX },
            { "getLocY", l_Rplaceable_getLocY },
            { "getLocZ", l_Rplaceable_getLocZ },

            { "setRotX", l_Rplaceable_setRotX },
            { "setRotY", l_Rplaceable_setRotY },
            { "setRotZ", l_Rplaceable_setRotZ },
            { "getRotX", l_Rplaceable_getRotX },
            { "getRotY", l_Rplaceable_getRotY },
            { "getRotZ", l_Rplaceable_getRotZ },

            { "__gc", l_Rplaceable_destructor },
            { NULL, NULL }
        };

        // Create a luaL metatable. This metatable is not
        // exposed to Lua. The "luaL_Rplaceable" label is used by luaL
        // internally to identity things.
        luaL_newmetatable(l, "luaL_Rplaceable");

        // Register the C functions _into_ the metatable we just created.
        //luaL_register(l, NULL, sRplaceableRegs); --> VERSION <= 5.1
        luaL_setfuncs(l,sRplaceableRegs,0);

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rplaceable"   |-1
        lua_pushvalue(l, -1);

        // The Lua stack at this point looks like this:
        //
        //     2| metatable "luaL_Rplaceable"   |-1
        //     1| metatable "luaL_Rplaceable"   |-2

        // Set the "__index" field of the metatable to point to itself
        // This pops the stack
        lua_setfield(l, -1, "__index");

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rplaceable"   |-1

        // The luaL_Rplaceable metatable now has the following fields
        //     - __gc
        //     - __index
        //     - add
        //     - new

        // Now we use setglobal to officially expose the luaL_Rplaceable metatable
        // to Lua. And we use the name "Rplaceable".
        //
        // This allows Lua scripts to _override_ the metatable of Rplaceable.
        // For high security code this may not be called for but
        // we'll do this to get greater flexibility.
        lua_setglobal(l, "Rplaceable");
    }
}



