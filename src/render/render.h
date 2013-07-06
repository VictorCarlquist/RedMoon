#include "../scene/scene.h"
#include "../camera/camera.h"
#include <iostream>
#include <lua5.2/lua.hpp>

using namespace std;


#ifndef __RENDER_H__
#define __RENDER_H__

namespace red
{
	
	class Rrender
	{
		public:
			Rrender(void);
			Rrender(Rscene *);
            void initWindow(int , int, float near, float far);
			Rscene* getScene(void);
			void setScene(Rscene *);
            void setCamera(Rcamera *);
			void draw(void *);
			void render(void);
			Rscene *scene;
            Rcamera *camera;
		private:
			string typeObj;
			
	};
	void RegisterRrender(lua_State *l);
    Rscene * l_CheckRscene(lua_State * l, int n);
    Rcamera * l_CheckRcamera(lua_State * l, int n);
}
#endif
