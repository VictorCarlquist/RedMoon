#include "light.h"
#include <cstdlib>

namespace red {

    RlightLamp::RlightLamp(const char *uid){

        ambient = (float*) malloc(sizeof(float) * 4);
        ambient[0] = 0.5;
        ambient[1] = 0.5;
        ambient[2] = 0.5;
        ambient[3] = 1;

        diffuse = (float*) malloc(sizeof(float) * 4);
        diffuse[0] = 0.5;
        diffuse[1] = 0.5;
        diffuse[2] = 0.5;
        diffuse[3] = 1;

        specular = (float*) malloc(sizeof(float) * 4);
        specular[0] = 0.5;
        specular[1] = 0.5;
        specular[2] = 0.5;
        specular[3] = 1;

        this->uid = uid;

         /**
          * typeLight:
          * 0 - lamp
          * 1 - spot
          **/
        typeLight = 0;
    }
    void RlightLamp::setAmbient(float amb[])
    {
        this->ambient = amb;
    }
    void RlightLamp::setDiffuse(float dif[])
    {
        this->diffuse = dif;
    }
    void RlightLamp::setSpecular(float spe[])
    {
        this->specular = spe;
    }
    float* RlightLamp::getAmbient()
    {
        return this->ambient;
    }
    float* RlightLamp::getDiffuse()
    {
        return this->diffuse;
    }
    float* RlightLamp::getSpecular()
    {
        return this->specular;
    }
    RlightLamp * l_CheckRlightLamp(lua_State * l, int n)
    {
        return *(RlightLamp **)luaL_checkudata(l, n, "luaL_RlightLamp");
    }
    int l_RlightLamp_constructor(lua_State * l)
    {
        const char*  uid= luaL_checkstring(l, 1);
        RlightLamp ** udata = (RlightLamp **) lua_newuserdata(l, sizeof(RlightLamp *));
        *udata = new RlightLamp(uid);

        luaL_getmetatable(l, "luaL_RlightLamp");

        lua_setmetatable(l, -2);


        return 1;
    }
    int l_RlightLamp_destructor(lua_State * l)
    {
        RlightLamp * foo = l_CheckRlightLamp(l, 1);
        delete foo;

        return 1;
    }
    int l_RlightLamp_setAmbient(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);

        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);
        float n[4];
        n[0] = x;
        n[1] = y;
        n[2] = z;
        n[3] = 1;
        li->setAmbient(n);

        return 1;
    }
    int l_RlightLamp_setSpecular(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);

        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);
        float n[4];
        n[0] = x;
        n[1] = y;
        n[2] = z;
        n[3] = 1;
        li->setSpecular(n);

        return 1;
    }
    int l_RlightLamp_setDiffuse(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);

        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);
        float n[4];
        n[0] = x;
        n[1] = y;
        n[2] = z;
        n[3] = 1;
        li->setDiffuse(n);

        return 1;
    }
    int l_RlightLamp_getAmbient(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);
        float *a = li->getAmbient();
        lua_pushnumber(l,a[0]);
        lua_pushnumber(l,a[1]);
        lua_pushnumber(l,a[2]);

        return 3;
    }
    int l_RlightLamp_getSpecular(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);
        float *a = li->getSpecular();
        lua_pushnumber(l,a[0]);
        lua_pushnumber(l,a[1]);
        lua_pushnumber(l,a[2]);

        return 3;
    }
    int l_RlightLamp_getDiffuse(lua_State * l)
    {
        RlightLamp * li = l_CheckRlightLamp(l, 1);
        float *a = li->getAmbient();
        lua_pushnumber(l,a[0]);
        lua_pushnumber(l,a[1]);
        lua_pushnumber(l,a[2]);

        return 3;
    }

    int l_RlightLamp_setLoc(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setLoc(x,y,z);

        return 1;
    }
    int l_RlightLamp_setLocX(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocX(x);

        return 1;
    }
    int l_RlightLamp_setLocY(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setLocY(y);

        return 1;
    }
    int l_RlightLamp_setLocZ(lua_State * l)
    {

        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setLocZ(z);

        return 1;
    }
    int l_RlightLamp_getLocX(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        lua_pushnumber(l,locate->getLocX());

        return 1;
    }
    int l_RlightLamp_getLocY(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        lua_pushnumber(l,locate->getLocY());

        return 1;
    }
    int l_RlightLamp_getLocZ(lua_State * l)
    {
        RlightLamp * locate = l_CheckRlightLamp(l, 1);
        lua_pushnumber(l,locate->getLocZ());

        return 1;
    }

    void RegisterRlightLamp(lua_State *l)
    {
        luaL_Reg sRlightLampRegs[] =
        {
            { "new", l_RlightLamp_constructor },
            { "__gc", l_RlightLamp_destructor },

            { "setLoc", l_RlightLamp_setLoc },
            { "setLocX", l_RlightLamp_setLocX },
            { "setLocY", l_RlightLamp_setLocY },
            { "setLocZ", l_RlightLamp_setLocZ },
            { "getLocX", l_RlightLamp_getLocX },
            { "getLocY", l_RlightLamp_getLocY },
            { "getLocZ", l_RlightLamp_getLocZ },

            { "getSpecular", l_RlightLamp_getSpecular },
            { "getDiffuse", l_RlightLamp_getDiffuse },
            { "getAmbient", l_RlightLamp_getAmbient },
            { "setSpecular", l_RlightLamp_setSpecular },
            { "setDiffuse", l_RlightLamp_setDiffuse },
            { "setAmbient", l_RlightLamp_setAmbient },

            { NULL, NULL }
        };

        // Create a luaL metatable. This metatable is not
        // exposed to Lua. The "luaL_Rscene" label is used by luaL
        // internally to identity things.
        luaL_newmetatable(l, "luaL_RlightLamp");

        // Register the C functions _into_ the metatable we just created.
        //luaL_register(l, NULL, sRsceneRegs); --> VERSION <= 5.1
        luaL_setfuncs(l,sRlightLampRegs,0);

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
        lua_setglobal(l, "RlightLamp");
    }
}
