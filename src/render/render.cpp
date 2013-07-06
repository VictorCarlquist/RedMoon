#include <iostream>
#include <cmath>

#include "render.h"
#include "../material/material.h"

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <lua5.2/lua.hpp>

#include <SOIL/SOIL.h>

namespace red
{
	Rrender::Rrender(void){}
	Rrender::Rrender(Rscene *cena)
	{
		this->scene = cena; 
	}
	void Rrender::setScene(Rscene *cena)
	{
		this->scene = cena; 
	}
    void Rrender::setCamera(Rcamera *camera)
    {
        this->camera = camera;
    }
	Rscene *Rrender::getScene(void)
	{
		return this->scene;
	}
	
    void Rrender::initWindow(int w, int h, float near, float far)
	{
        atexit(SDL_Quit);
        if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
            fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }

         SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*

        SDL_Surface *screen = SDL_SetVideoMode(w, h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL);

		glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        gluPerspective(45, w / h, (GLfloat)near,(GLfloat)far);

		glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);
        glDepthFunc(GL_LEQUAL);
        glShadeModel(GL_FLAT);
        glEnable(GL_BLEND);
        glEnable(GL_NORMALIZE);

        glClearColor( 0.0, 0.0, 1.0, 1.0 );
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        GLfloat ambientColor[] = {0.5, 1, 1, 1.0f}; //Color(0.2, 0.2, 0.2)
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
        GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	}
/*	void *Rrender::rendering(void *)
	{


	}
*/
	void Rrender::render(void)
	{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        gluLookAt (this->camera->getLocX(), this->camera->getLocY(), this->camera->getLocZ(),
           this->camera->getLocTX(),this->camera->getLocTY(),this->camera->getLocTZ(),
        0,1,0);


        if(this->scene != NULL && this->camera != NULL)
        {
            int i,j,k;
            Rwavefront *obj;

            for(i=0;i<this->scene->WavefrontObjects.size();++i)
            {
                obj = this->scene->WavefrontObjects[i];

                glPushMatrix();

                glTranslatef (obj->getLocX(), obj->getLocY(), obj->getLocZ());
                glRotatef (obj->getRotX(), 1,0,0);
                glRotatef (obj->getRotY(), 0,1,0);
                glRotatef (obj->getRotZ(), 0,0,1);
                glScalef(obj->getScaleX(),obj->getScaleY(),obj->getScaleZ());

                if(obj->listObjects.empty())
                {
                    if(obj->smooth)
                        glShadeModel(GL_SMOOTH);
                    else
                        glShadeModel(GL_FLAT);

                    Rmaterial *mat = obj->listMaterials[obj->textureName];
                    if(mat->textureId != 0)
                    {
                        glBindTexture(GL_TEXTURE_2D, mat->textureId);
                    }
                    if(!mat->ambient.empty())
                    {
                        glMaterialfv(GL_FRONT,GL_AMBIENT , &mat->ambient[0][0]);
                    }
                    if(!mat->diffuse.empty())
                    {
                        glMaterialfv(GL_FRONT,GL_DIFFUSE , &mat->diffuse[0][0]);

                    }

                    glBegin(GL_TRIANGLES);

                    for(j=0;j<obj->faces.size();j++)
                    {
                        if(!obj->uvs.empty())
                            glTexCoord2f(obj->uvs[obj->faces[j][1]-1][0],obj->uvs[obj->faces[j][1]-1][1]);
                       // cout << obj->uvs[obj->faces[j][1]-1][0] << endl;
                        if(!obj->normals.empty())
                            glNormal3f(obj->normals[obj->faces[j][2]-1][0],obj->normals[obj->faces[j][2]-1][1],obj->normals[obj->faces[j][2]-1][2]);
                        glVertex3f(obj->vertices[obj->faces[j][0]-1][0],obj->vertices[obj->faces[j][0]-1][1],obj->vertices[obj->faces[j][0]-1][2] );
                    }
                    glEnd();

                }else{


                    for(k = 0; k < obj->listObjects.size();++k)
                    {
                        Rwavefront *lObj;
                        lObj = obj->listObjects[k];


                        if(lObj->smooth)
                            glShadeModel(GL_SMOOTH);
                        else
                            glShadeModel(GL_FLAT);


                        Rmaterial *mat;
                        if(lObj->textureName != "")
                            mat = obj->listMaterials[lObj->textureName];
                        else
                            mat = obj->listMaterials[obj->textureName];

                            if(mat->textureId != 0)
                            {
                                glBindTexture(GL_TEXTURE_2D, mat->textureId);
                            }
                            if(!mat->ambient.empty())
                            {
                                glMaterialfv(GL_FRONT,GL_AMBIENT , &mat->ambient[0][0]);

                            }
                            if(!mat->diffuse.empty())
                            {

                                glMaterialfv(GL_FRONT,GL_DIFFUSE , &mat->diffuse[0][0]);

                            }


                        glBegin(GL_TRIANGLES);

                        for(j=0;j<lObj->faces.size();++j)
                        {
                           // glColor4f(j*0.1, 0.5f, 0.0f, 1.0f);
                            if(!obj->uvs.empty())
                                if(lObj->faces[j][1]-1 < obj->uvs.size())
                                    glTexCoord2f(obj->uvs[lObj->faces[j][1]-1][0],obj->uvs[lObj->faces[j][1]-1][1]);
                           // cout << obj->uvs[obj->faces[j][1]-1][0] << endl;

                            if(!obj->normals.empty())
                                if(lObj->faces[j][2]-1 < obj->faces.size())
                                    glNormal3f(obj->normals[lObj->faces[j][2]-1][0],obj->normals[lObj->faces[j][2]-1][1],obj->normals[lObj->faces[j][2]-1][2]);

                            glVertex3f(obj->vertices[lObj->faces[j][0]-1][0],obj->vertices[lObj->faces[j][0]-1][1],obj->vertices[lObj->faces[j][0]-1][2] );
                           //
                        }
                        glEnd();

                    }
                }
                glPopMatrix();
            }

        }

		SDL_GL_SwapBuffers();
		
		
	}
	/*
	void render(void) 
	{
	   glColor3f(0.0, 0.0, 1.0);
	   glPushMatrix ();
	   glRotatef (30.0, 1.0, 0.0, 0.0);
	   glPushMatrix ();
	   glTranslatef (-0.80, 0.35, 0.0); 
	   glRotatef (100.0, 1.0, 0.0, 0.0);
	//   glutSolidTorus (0.275, 0.85, 16, 16);
	   glutWireTorus (0.275, 0.85, 16, 16);
	   glPopMatrix ();

	   glColor3f(1.0, 0.0, 0.0);
	   glPushMatrix ();
	   glTranslatef (-0.75, -0.50, 0.0); 
	   glRotatef (10.0, 0.0, 0.0, 1.0);
	   glRotatef (10.0, 1.0, 0.0, 0.0);
	//   glutSolidCube (1.5);
	   glutWireCube (1.5);
	   glPopMatrix ();

	   glColor3f(0.0, 1.0, 0.0);
	   glPushMatrix ();
	   glTranslatef (0.75, 0.60, 0.0); 
	   glRotatef (30.0, 1.0, 0.0, 0.0);
	//   glutSolidSphere (1.0, 16, 16);
	   glutWireSphere (1.0, 16, 16);
	   glPopMatrix ();

	   glColor3f(1.0, 1.0, 0.0);
	   glPushMatrix ();
	   glTranslatef (0.70, -0.90, 0.25); 
	//   glutSolidOctahedron ();
	   glutWireOctahedron ();
	   glPopMatrix ();

	   glPopMatrix ();
	   glutSwapBuffers();
	}
	*/
	int l_Rrender_constructor(lua_State * l)
	{
		//const char * name = luaL_checkstring(l, 1);

		Rrender ** udata = (Rrender **) lua_newuserdata(l, sizeof(Rrender *));
		*udata = new Rrender();

		luaL_getmetatable(l, "luaL_Rrender");

		lua_setmetatable(l, -2);

		return 1;
	}

	Rrender * l_CheckRrender(lua_State * l, int n)
	{
		return *(Rrender **)luaL_checkudata(l, n, "luaL_Rrender");
	}

	int l_Rrender_initWindow(lua_State * l)
	{
		//initWindow(argc,argv,400,400);

		Rrender * render= l_CheckRrender(l, 1);
		int a = luaL_checknumber(l, 2);
		int b = luaL_checknumber(l, 3);
        float near = luaL_checknumber(l, 4);
        float far = luaL_checknumber(l, 5);
        render->initWindow(a,b,near, far);

		return 1;
	}
	
	int l_Rrender_setScene(lua_State * l)
	{

		Rrender * foo = l_CheckRrender(l, 1);
        Rscene *scene = l_CheckRscene(l, 2);
		//Rscene *scene = (Rscene *)lua_touserdata(l, 2);
       // cout << scene->WavefrontObjects[0]->faces.size() << "F" <<endl;
		foo->setScene(scene);

		return 1;
	}
    int l_Rrender_setCamera(lua_State * l)
    {

        Rrender * foo = l_CheckRrender(l, 1);
        Rcamera *c = l_CheckRcamera(l, 2);
        //Rscene *scene = (Rscene *)lua_touserdata(l, 2);
       // cout << scene->WavefrontObjects[0]->faces.size() << "F" <<endl;
        foo->setCamera(c);

        return 1;
    }
	int l_Rrender_render(lua_State * l)
	{
		//Rscene *scene = (Rscene *)lua_touserdata(l, 1);
		Rrender * foo = l_CheckRrender(l, 1);
		//Rscene *scene = (Rscene *)lua_touserdata(l, 2);

		foo->render();

		return 1;
	}

	int l_Rrender_destructor(lua_State * l)
	{
		Rrender * foo = l_CheckRrender(l, 1);
		delete foo;

		return 0;
	}

	void RegisterRrender(lua_State *l)
	{
		luaL_Reg sRrenderRegs[] =
		{
		    { "new", l_Rrender_constructor },
		    { "initWindow", l_Rrender_initWindow },
		    { "setScene", l_Rrender_setScene },
            { "setCamera", l_Rrender_setCamera },
		    { "render", l_Rrender_render },
		    { "__gc", l_Rrender_destructor },
		    { NULL, NULL }
		};

		// Create a luaL metatable. This metatable is not 
		// exposed to Lua. The "luaL_Rrender" label is used by luaL
		// internally to identity things.
		luaL_newmetatable(l, "luaL_Rrender");

		// Register the C functions _into_ the metatable we just created.
		//luaL_register(l, NULL, sRrenderRegs); --> VERSION <= 5.1
		luaL_setfuncs(l,sRrenderRegs,0);

		// The Lua stack at this point looks like this:
		//     
		//     1| metatable "luaL_Rrender"   |-1
		lua_pushvalue(l, -1);

		// The Lua stack at this point looks like this:
		//     
		//     2| metatable "luaL_Rrender"   |-1
		//     1| metatable "luaL_Rrender"   |-2

		// Set the "__index" field of the metatable to point to itself
		// This pops the stack
		lua_setfield(l, -1, "__index");

		// The Lua stack at this point looks like this:
		//     
		//     1| metatable "luaL_Rrender"   |-1

		// The luaL_Rrender metatable now has the following fields
		//     - __gc
		//     - __index
		//     - add
		//     - new

		// Now we use setglobal to officially expose the luaL_Rrender metatable 
		// to Lua. And we use the name "Rrender".
		//
		// This allows Lua scripts to _override_ the metatable of Rrender.
		// For high security code this may not be called for but 
		// we'll do this to get greater flexibility.
		lua_setglobal(l, "Rrender");
	}
	
}
