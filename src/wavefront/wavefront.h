#include "../object/object.h"
#include "../locate/locate.h"
#include "../material/material.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <lua5.2/lua.hpp>


#ifndef __WAVEFRONT__
#define __WAVEFRONT__
namespace red
{

    class Rwavefront: public Robject
	{
		public:

            Rwavefront(const char* uid):Robject(uid)
            {
                this->smooth = false;
                this->isUv = false;
            }
			~Rwavefront();
            std::vector<std::vector<float> > vertices, normals, uvs;
            std::vector<std::vector<int> > faces;
            std::vector<Rwavefront *> listObjects;
            bool smooth;

            unsigned int vertexId;
            unsigned int normalId;
            unsigned int uvId;
            bool isUv;


            std::map<std::string, Rmaterial *> listMaterials;
            std::string textureName;


           // std::vector<Rmaterial*> materials;
            void loadFileChild(std::ifstream *file, Rwavefront *obj, std::string absol);
            void loadFile(const char *, bool isChild  = false);
            void loadMaterial(const char * );
            void createMesh(Rwavefront *obj);

	};
    void RegisterRwavefront(lua_State *l);
    Rwavefront * l_CheckRwavefront(lua_State * l, int n);
}
#endif
