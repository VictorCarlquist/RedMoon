#include "camera.h"
namespace red
{

    void Rcamera::setLocT(float x, float y, float z)
    {
        this->tx = x;
        this->ty = y;
        this->tz = z;
    }

    void Rcamera::setLocTX(float x)
    {
        this->tx = x;
    }
    void Rcamera::setLocTY(float y)
    {
        this->ty = y;
    }
    void Rcamera::setLocTZ(float z)
    {
        this->tz = z;
    }
    float Rcamera::getLocTX()
    {
        return this->tx;
    }
    float Rcamera::getLocTY()
    {
        return this->ty;
    }
    float Rcamera::getLocTZ()
    {
        return this->tz;
    }


    Rcamera * l_CheckRcamera(lua_State * l, int n)
    {
        return *(Rcamera **)luaL_checkudata(l, n, "luaL_Rcamera");
    }
    int l_Rcamera_constructor(lua_State * l)
    {
        Rcamera ** udata = (Rcamera **) lua_newuserdata(l, sizeof(Rcamera *));
        *udata = new Rcamera();

        luaL_getmetatable(l, "luaL_Rcamera");

        lua_setmetatable(l, -2);

        return 1;
    }

    int l_Rcamera_destructor(lua_State * l)
    {
        Rcamera * foo = l_CheckRcamera(l, 1);
        delete foo;

        return 0;
    }
    int l_Rcamera_setLoc(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setLoc(x,y,z);

        return 1;
    }
    int l_Rcamera_setLocX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocX(x);

        return 1;
    }
    int l_Rcamera_setLocY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setLocY(y);

        return 1;
    }
    int l_Rcamera_setLocZ(lua_State * l)
    {

        Rcamera * locate = l_CheckRcamera(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setLocZ(z);

        return 1;
    }

    int l_Rcamera_setRot(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setRot(x,y,z);

        return 1;
    }
    int l_Rcamera_setRotX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setRotX(x);

        return 1;
    }
    int l_Rcamera_setRotY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setRotY(y);

        return 1;
    }
    int l_Rcamera_setRotZ(lua_State * l)
    {

        Rcamera * locate = l_CheckRcamera(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setRotZ(z);

        return 1;
    }
    int l_Rcamera_getLocX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocX());

        return 1;
    }
    int l_Rcamera_getLocY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocY());

        return 1;
    }
    int l_Rcamera_getLocZ(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocZ());

        return 1;
    }
    int l_Rcamera_getRotX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getRotX());

        return 1;
    }
    int l_Rcamera_getRotY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getRotY());

        return 1;
    }
    int l_Rcamera_getRotZ(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getRotZ());

        return 1;
    }

    int l_Rcamera_setLocT(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setLocT(x,y,z);

        return 1;
    }
    int l_Rcamera_setLocTX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocTX(x);

        return 1;
    }
    int l_Rcamera_setLocTY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocTY(x);

        return 1;
    }
    int l_Rcamera_setLocTZ(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocTZ(x);

        return 1;
    }
    int l_Rcamera_getLocTX(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocTX());

        return 1;
    }
    int l_Rcamera_getLocTY(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocTY());

        return 1;
    }
    int l_Rcamera_getLocTZ(lua_State * l)
    {
        Rcamera * locate = l_CheckRcamera(l, 1);
        lua_pushnumber(l,locate->getLocTZ());

        return 1;
    }


    void RegisterRcamera(lua_State *l)
    {
        luaL_Reg sRcameraRegs[] =
        {
            { "new", l_Rcamera_constructor },
            { "__gc", l_Rcamera_destructor },

            { "setLoc", l_Rcamera_setLoc },
            { "setLocX", l_Rcamera_setLocX },
            { "setLocY", l_Rcamera_setLocY },
            { "setLocZ", l_Rcamera_setLocZ },
            { "getLocX", l_Rcamera_getLocX },
            { "getLocY", l_Rcamera_getLocY },
            { "getLocZ", l_Rcamera_getLocZ },

            { "setRot", l_Rcamera_setRot },
            { "setRotX", l_Rcamera_setRotX },
            { "setRotY", l_Rcamera_setRotY },
            { "setRotZ", l_Rcamera_setRotZ },
            { "getRotX", l_Rcamera_getRotX },
            { "getRotY", l_Rcamera_getRotY },
            { "getRotZ", l_Rcamera_getRotZ },

            { "setLocT", l_Rcamera_setLocT },
            { "setLocTX", l_Rcamera_setLocTX },
            { "setLocTY", l_Rcamera_setLocTY },
            { "setLocTZ", l_Rcamera_setLocTZ },
            { "getLocTX", l_Rcamera_getLocTX },
            { "getLocTY", l_Rcamera_getLocTY },
            { "getLocTZ", l_Rcamera_getLocTZ },


            { NULL, NULL }
        };

        // Create a luaL metatable. This metatable is not
        // exposed to Lua. The "luaL_Rcamera" label is used by luaL
        // internally to identity things.
        luaL_newmetatable(l, "luaL_Rcamera");

        // Register the C functions _into_ the metatable we just created.
        //luaL_register(l, NULL, sRcameraRegs); --> VERSION <= 5.1
        luaL_setfuncs(l,sRcameraRegs,0);

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rcamera"   |-1
        lua_pushvalue(l, -1);

        // The Lua stack at this point looks like this:
        //
        //     2| metatable "luaL_Rcamera"   |-1
        //     1| metatable "luaL_Rcamera"   |-2

        // Set the "__index" field of the metatable to point to itself
        // This pops the stack
        lua_setfield(l, -1, "__index");

        // The Lua stack at this point looks like this:
        //
        //     1| metatable "luaL_Rcamera"   |-1

        // The luaL_Rcamera metatable now has the following fields
        //     - __gc
        //     - __index
        //     - add
        //     - new

        // Now we use setglobal to officially expose the luaL_Rcamera metatable
        // to Lua. And we use the name "Rcamera".
        //
        // This allows Lua scripts to _override_ the metatable of Rcamera.
        // For high security code this may not be called for but
        // we'll do this to get greater flexibility.
        lua_setglobal(l, "Rcamera");
    }
}
