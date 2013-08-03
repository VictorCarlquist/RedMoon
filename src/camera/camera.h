#include "../placeable/placeable.h"
#include <lua5.2/lua.hpp>

#ifndef CAMERA_H
#define CAMERA_H
namespace red
{
    class Rcamera : public Rplaceable{

        public:
        Rcamera():Rplaceable()
        {
            this->tx = 0;
            this->ty = 0;
            this->tz = 0;
        }
        float tx,ty,tz; //target

        void setLocT(float x,float y,float z);

        void setLocTX(float);
        void setLocTY(float);
        void setLocTZ(float);

        float getLocTX();
        float getLocTY();
        float getLocTZ();
    };

    void RegisterRcamera(lua_State *l);
}
#endif // CAMERA_H
