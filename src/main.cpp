#include <SDL/SDL.h>
#include <GL/gl.h>
#include <lua5.2/lua.hpp>
#include <iostream>

#include "render/render.h"
#include "scene/scene.h"
#include "wavefront/wavefront.h"
#include "keyboard/keyboard.h"
#include "placeable/placeable.h"
#include "camera/camera.h"

#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */


using namespace red;

int main(int argc, char** argv)
{

	/*Rrender* render = new Rrender();
	render->initWindow(500,500);	
	
	Rscene* cena = new Rscene();
	cena->addPrimitiveObject(1);
	render->setScene(cena);
	int i =0;
	for(i=0;i<20000;i++)
		render->render();
	*/

	lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    
	RegisterRrender(l);
    RegisterRkeyboard(l);
	RegisterRscene(l);
    RegisterRwavefront(l);
    RegisterRplaceable(l);
    RegisterRcamera(l);
    RegisterRlightLamp(l);
	
	if(argv[1] != NULL)
	{
		int erred = luaL_dofile(l, argv[1]);
		if(erred)
		    std::cout << "Lua error: " << luaL_checkstring(l, -1) << std::endl;
	}
	
	lua_close(l);


	return 0;

}
