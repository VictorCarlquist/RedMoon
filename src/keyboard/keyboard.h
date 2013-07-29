#include <SDL/SDL.h>
#include <lua5.2/lua.hpp>
#include <iostream>
#include <map>


#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

namespace red
{

	class Rkeyboard
	{
		public:
			Rkeyboard();
			~Rkeyboard(){};
			bool isKeyPressed(int);
			void refresh();
		private:
			Uint8 *keys;
            std::map<int, bool> keyboard;
			void keyCapture();
			int bufferKey;


	};
	void RegisterRkeyboard(lua_State *);
}
#endif
