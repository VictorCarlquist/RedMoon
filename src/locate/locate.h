#include <lua5.2/lua.hpp>
#ifndef __LOCATE_H__
#define __LOCATE_H__
namespace red
{
	class Rlocate 
	{
		public: 

            Rlocate(){
                this->lx = this->ly = this->lz = 0;
                this->rx = this->ry = this->rz = 0;
            }
	
			void setLoc(float x,float y,float z);
			void setLocX(float x);
			void setLocY(float y);
			void setLocZ(float z);
		
			float getLocX();
			float getLocY();
			float getLocZ();
		
		
			void setRot(float x,float y,float z);
			void setRotX(float x);
			void setRotY(float y);
			void setRotZ(float z);
		
			float getRotX();
			float getRotY();
			float getRotZ();
			
			 
		private:
			float lx,ly,lz;
			float rx,ry,rz;
	};
     void RegisterRlocate(lua_State *l);
}
#endif
