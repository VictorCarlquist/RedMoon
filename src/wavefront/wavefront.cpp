#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

#include <vector>


#include <GL/glew.h>
#include <GL/glut.h>
#include <SOIL/SOIL.h>

#include "../util/util.h"
#include "../wavefront/wavefront.h"

using namespace std;
namespace red
{
    /*Rwavefront::Rwavefront(int uid)
	{
		this->type = 'w'; //default wavefront (.obj)
		this->uid = uid;
    }*/
	Rwavefront::~Rwavefront(){}

	//# List of Vertices, with (x,y,z[,w]) coordinates, w is optional and defaults to 1.0.
    void Rwavefront::loadFile(const char *path , bool isChild)
	{
		string line;
        ifstream file(path);
        int i,j;
        std::vector<string> vtmp;

        string absol(path);

        absol = absol.substr(0,absol.find_last_of("/\\")+1);
        bool isListObjects = false;
        if(file.is_open())
        {
			while(file.good())
			{
                getline(file,line);
                if(line.substr(0,6) == "mtllib")
                {
                    string newpath = absol +line.substr(7);
                    this->loadMaterial(newpath.c_str());
                }
                if(line.substr(0,6) == "usemtl")
                {
                    this->textureName = line.substr(7);

                }

                if(line[0] == 'o' && isListObjects)
                {
                    this->listObjects.push_back(this);
                    if(!isChild)
                    {
                        Rwavefront *obj = new Rwavefront(line.substr(2).c_str());
                        this->loadFileChild(&file,obj,absol);
                        this->createMesh(obj);
                        this->listObjects.push_back(obj);



                    }
                }
                if(line[0] == 'o')
                {
                    isListObjects = true;

                }

                switch(line[0])
				{
					case 'v':
						if(line[1] != 't' && line[1] != 'n') //  'v'
						{
                            std::vector<float> tmp;
							vtmp = split(line.substr(2)," ");
							for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
							this->vertices.push_back(tmp);
                            tmp.clear();
						}else if(line[1] == 't') { //  'vt'
                            std::vector<float> tmp;
                            vtmp = split(line.substr(3)," ");

                            for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
                            this->uvs.push_back(tmp);

                            tmp.clear();
							
						}else if(line[1] == 'n') { //  'vn'
                            std::vector<float> tmp;
                            vtmp = split(line.substr(3)," ");
							for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
							this->normals.push_back(tmp);
                            tmp.clear();
							
						}
						
					break;
                    case 's':
                        this->smooth = ((line.substr(2) == "off") ? false : true);
                    break;
                    case 'f':
                        vector<int> ftmp;
                        std::vector<int> tmp;
                        std::vector<string> stmp;
                        vtmp = split(line.substr(2)," ");

                        for(i=0;i<vtmp.size();++i)
                        {

                            stmp = split(vtmp[i],"/");

                            for(j = 0; j < stmp.size(); ++j)
                            {
                                tmp.push_back(atoi(stmp[j].c_str()));
                            }
                            this->faces.push_back(tmp);
                            tmp.clear();
                        }

					break;


                }
            }
                vtmp.clear();


			file.close();
            this->createMesh(this);
        }


	}
    void Rwavefront::loadMaterial(const char *path)
    {
        string line;
        ifstream file(path);
        int i;
        std::vector<string> vtmp;

        Rmaterial *mat;
        if(file.is_open())
        {
            while(file.good())
            {
                getline(file,line);
                if(line.substr(0,6) == "newmtl")
                {
                    mat = new Rmaterial();
                    this->listMaterials[line.substr(7)] = mat;
                }
                if(line.substr(0,2) == "Ka")
                {
                    std::vector<float> tmp;
                    vtmp = split(line.substr(3)," ");
                    for(i=0;i<vtmp.size();++i)
                        tmp.push_back(atof(vtmp[i].c_str()));
                    mat->ambient.push_back(tmp);
                    vtmp.clear();
                }
                if(line.substr(0,2) == "Kd")
                {
                    std::vector<float> tmp;
                    vtmp = split(line.substr(3)," ");
                    for(i=0;i<vtmp.size();++i)
                        tmp.push_back(atof(vtmp[i].c_str()));
                    mat->diffuse.push_back(tmp);
                    vtmp.clear();
                }
                if(line.substr(0,2) == "Ks")
                {
                    std::vector<float> tmp;
                    vtmp = split(line.substr(3)," ");
                    for(i=0;i<vtmp.size();++i)
                        tmp.push_back(atof(vtmp[i].c_str()));
                    mat->specular.push_back(tmp);
                    vtmp.clear();
                }
                if(line.substr(0,2) == "Ns")
                {
                    mat->specularCof = atof(line.substr(3).c_str());
                }
                if(line.substr(0,1) == "d")
                    mat->transparent = atof(line.substr(3).c_str());
                if(line.substr(0,2) == "Tr")
                    mat->transparent = atof(line.substr(3).c_str());
                if(line.substr(0,6) == "map_Kd")
                {

                    int width,height;
                    string absol(path);
                    absol = absol.substr(0,absol.find_last_of("/\\")+1);
                    string newpath = absol +line.substr(7);
                    unsigned char* image = SOIL_load_image( newpath.c_str() , &width, &height, 0, SOIL_LOAD_RGB );

                    if( 0 == image )
                    {
                        cout << "SOIL loading error:" << SOIL_last_result() << endl;
                    }



                    glGenTextures(1,&mat->textureId);
                    glBindTexture(GL_TEXTURE_2D, mat->textureId);
                    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
                    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
                    glTexImage2D( GL_TEXTURE_2D, 0, 3, width, height, 0, GL_RGB,
                                  GL_UNSIGNED_BYTE, image );
                   // SOIL_free_image(image);

                }
            }
        }

    }
    void Rwavefront::loadFileChild(ifstream *file, Rwavefront *obj, string absol)
    {
        // Param file : continue line, keep old state
        string line;
        int i,j;
        std::vector<string> vtmp;

        if(file->is_open())
        {
            while(file->good())
            {

                getline(*file,line);

                if(line.substr(0,6) == "usemtl")
                {
                    obj->textureName = line.substr(7);

                }
                if(line[0] == 'o')
                {
                    return;
                }

                switch(line[0])
                {
                    case 'v':
                        if(line[1] != 't' && line[1] != 'n') //  'v'
                        {
                            std::vector<float> tmp;
                            vtmp = split(line.substr(2)," ");
                            for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
                            this->vertices.push_back(tmp);
                            tmp.clear();
                        }else if(line[1] == 't') { //  'vt'
                            std::vector<float> tmp;
                            vtmp = split(line.substr(3)," ");

                            for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
                            this->uvs.push_back(tmp);

                            tmp.clear();

                        }else if(line[1] == 'n') { //  'vn'
                            std::vector<float> tmp;
                            vtmp = split(line.substr(3)," ");
                            for(i=0;i<vtmp.size();++i)
                                tmp.push_back(atof(vtmp[i].c_str()));
                            this->normals.push_back(tmp);
                            tmp.clear();

                        }

                    break;
                    case 'f':
                        vector<int> ftmp;
                        std::vector<int> tmp;
                        std::vector<string> stmp;
                        vtmp = split(line.substr(2)," ");

                        for(i=0;i<vtmp.size();++i)
                        {

                            stmp = split(vtmp[i],"/");

                            for(j = 0; j < stmp.size(); ++j)
                            {
                                tmp.push_back(atoi(stmp[j].c_str()));
                            }
                            obj->faces.push_back(tmp);
                            tmp.clear();
                        }

                    break;

                }
            }
            vtmp.clear();


            file->close();
        }
    }

    void Rwavefront::createMesh(Rwavefront *obj)
    {
        int j;
        for(j=0;j<obj->faces.size();++j)
        {
           /*glColor4f(j*0.1, 0.5f, 0.0f, 1.0f);
            if(!obj->uvs.empty())
                if(lObj->faces[j][1]-1 < obj->uvs.size())
                    glTexCoord2f(obj->uvs[lObj->faces[j][1]-1][0],obj->uvs[lObj->faces[j][1]-1][1]);
           // cout << obj->uvs[obj->faces[j][1]-1][0] << endl;

            if(!obj->normals.empty())
                if(lObj->faces[j][2]-1 < obj->faces.size())
                    glNormal3f(obj->normals[lObj->faces[j][2]-1][0],obj->normals[lObj->faces[j][2]-1][1],obj->normals[lObj->faces[j][2]-1][2]);
            */

            //Vertex
            obj->mesh.push_back(this->vertices[obj->faces[j][0]-1][0]);
            obj->mesh.push_back(this->vertices[obj->faces[j][0]-1][1]);
            obj->mesh.push_back(this->vertices[obj->faces[j][0]-1][2]);

            //Normals
            if(!this->normals.empty())
                if(obj->faces[j][2]-1 < this->normals.size())
                {
                    obj->mesh.push_back(this->normals[obj->faces[j][2]-1][0]);
                    obj->mesh.push_back(this->normals[obj->faces[j][2]-1][1]);
                    obj->mesh.push_back(this->normals[obj->faces[j][2]-1][2]);
                }
            //UV
            if(!this->uvs.empty())
                if(obj->faces[j][1]-1 < this->uvs.size())
                {
                    obj->mesh.push_back(this->uvs[obj->faces[j][1]-1][0]);
                    obj->mesh.push_back(this->uvs[obj->faces[j][1]-1][1]);
                    obj->mesh.push_back(this->uvs[obj->faces[j][1]-1][2]);
                    obj->isUv = true;
                }
                    //glVertex3f(obj->vertices[lObj->faces[j][0]-1][0],obj->vertices[lObj->faces[j][0]-1][1],obj->vertices[lObj->faces[j][0]-1][2] );
           //
        }

        // Allocate the buffer
        //glGenBuffers(1, &obj->vertexId);
        //glBindBuffer(GL_ARRAY_BUFFER, obj->vertexId);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * obj->mesh.size(), &obj->mesh[0], GL_DYNAMIC_DRAW);
        //glVertexPointer(3, GL_FLOAT, GL_FALSE,0, 0);
        //glVertexAttribPointer(obj->vertexId, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    }

    Rwavefront * l_CheckRwavefront(lua_State * l, int n)
	{
		return *(Rwavefront **)luaL_checkudata(l, n, "luaL_Rwavefront");
	}
    int l_Rwavefront_constructor(lua_State * l)
    {
        const char*  uid= luaL_checkstring(l, 1);
        Rwavefront ** udata = (Rwavefront **) lua_newuserdata(l, sizeof(Rwavefront *));
        *udata = new Rwavefront(uid);

        luaL_getmetatable(l, "luaL_Rwavefront");

        lua_setmetatable(l, -2);


        return 1;
    }
	int l_Rwavefront_loadFile(lua_State * l)
	{
        Rwavefront *w = l_CheckRwavefront(l, 1);
        const char *a = luaL_checkstring(l, 2);
        w->loadFile(a);

        return 1;
	}

	int l_Rwavefront_destructor(lua_State * l)
	{
		Rwavefront * foo = l_CheckRwavefront(l, 1);
		delete foo;

        return 1;
	}
    int l_Rwavefront_setLoc(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setLoc(x,y,z);

        return 1;
    }
    int l_Rwavefront_setLocX(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setLocX(x);

        return 1;
    }
    int l_Rwavefront_setLocY(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setLocY(y);

        return 1;
    }
    int l_Rwavefront_setLocZ(lua_State * l)
    {

        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setLocZ(z);

        return 1;
    }

    int l_Rwavefront_setRot(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        locate->setRot(x,y,z);

        return 1;
    }
    int l_Rwavefront_setRotX(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float x = luaL_checknumber(l, 2);

        locate->setRotX(x);

        return 1;
    }
    int l_Rwavefront_setRotY(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float y = luaL_checknumber(l, 2);

        locate->setRotY(y);

        return 1;
    }
    int l_Rwavefront_setRotZ(lua_State * l)
    {

        Rwavefront * locate = l_CheckRwavefront(l, 1);
        float z = luaL_checknumber(l,2);

        locate->setRotZ(z);

        return 1;
    }
    int l_Rwavefront_getLocX(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getLocX());

        return 1;
    }
    int l_Rwavefront_getLocY(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getLocY());

        return 1;
    }
    int l_Rwavefront_getLocZ(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getLocZ());

        return 1;
    }
    int l_Rwavefront_getRotX(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getRotX());

        return 1;
    }
    int l_Rwavefront_getRotY(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getRotY());

        return 1;
    }
    int l_Rwavefront_getRotZ(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getRotZ());

        return 1;
    }
    int l_Rwavefront_setScale(lua_State * l)
    {
        Rwavefront * scale = l_CheckRwavefront(l, 1);
        float x = luaL_checknumber(l, 2);
        float y = luaL_checknumber(l, 3);
        float z = luaL_checknumber(l, 4);

        scale->setScale(x,y,z);

        return 1;
    }
    int l_Rwavefront_setScaleX(lua_State * l)
    {
        Rwavefront * scale = l_CheckRwavefront(l, 1);
        float n = luaL_checknumber(l, 2);
        scale->setScaleX(n);

        return 1;
    }
    int l_Rwavefront_setScaleY(lua_State * l)
    {
        Rwavefront * scale = l_CheckRwavefront(l, 1);
        float n = luaL_checknumber(l, 2);
        scale->setScaleY(n);

        return 1;
    }
    int l_Rwavefront_setScaleZ(lua_State * l)
    {
        Rwavefront * scale = l_CheckRwavefront(l, 1);
        float n = luaL_checknumber(l, 2);
        scale->setScaleZ(n);

        return 1;
    }
    int l_Rwavefront_getScaleX(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getScaleX());

        return 1;
    }
    int l_Rwavefront_getScaleY(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getScaleY());

        return 1;
    }
    int l_Rwavefront_getScaleZ(lua_State * l)
    {
        Rwavefront * locate = l_CheckRwavefront(l, 1);
        lua_pushnumber(l,locate->getScaleZ());

        return 1;
    }


    void RegisterRwavefront(lua_State *l)
	{
		luaL_Reg sRwavefrontRegs[] =
		{
		    { "new", l_Rwavefront_constructor },
		    { "loadFile", l_Rwavefront_loadFile},
		    { "__gc", l_Rwavefront_destructor },

            { "setLoc", l_Rwavefront_setLoc },
            { "setLocX", l_Rwavefront_setLocX },
            { "setLocY", l_Rwavefront_setLocY },
            { "setLocZ", l_Rwavefront_setLocZ },
            { "getLocX", l_Rwavefront_getLocX },
            { "getLocY", l_Rwavefront_getLocY },
            { "getLocZ", l_Rwavefront_getLocZ },

            { "setRot", l_Rwavefront_setRot },
            { "setRotX", l_Rwavefront_setRotX },
            { "setRotY", l_Rwavefront_setRotY },
            { "setRotZ", l_Rwavefront_setRotZ },
            { "getRotX", l_Rwavefront_getRotX },
            { "getRotY", l_Rwavefront_getRotY },
            { "getRotZ", l_Rwavefront_getRotZ },

            { "setScale", l_Rwavefront_setScale },
            { "setScaleX", l_Rwavefront_setScaleX },
            { "setScaleY", l_Rwavefront_setScaleY },
            { "setScaleZ", l_Rwavefront_setScaleZ },
            { "getScaleX", l_Rwavefront_getScaleX },
            { "getScaleY", l_Rwavefront_getScaleY },
            { "getScaleZ", l_Rwavefront_getScaleZ },

		    { NULL, NULL }
		};

		// Create a luaL metatable. This metatable is not 
		// exposed to Lua. The "luaL_Rscene" label is used by luaL
		// internally to identity things.
		luaL_newmetatable(l, "luaL_Rwavefront");

		// Register the C functions _into_ the metatable we just created.
		//luaL_register(l, NULL, sRsceneRegs); --> VERSION <= 5.1
		luaL_setfuncs(l,sRwavefrontRegs,0);

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
		lua_setglobal(l, "Rwavefront");
	}
}
