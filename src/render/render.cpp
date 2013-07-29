
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "render.h"
#include "../material/material.h"
#include "../text/text.h"


#include <SDL/SDL.h>
//#include <GL/glut.h>
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
	
    // Loading shader function
    GLhandleARB loadShader(char* filename, unsigned int type)
    {
        FILE *pfile;
        GLhandleARB handle;
        const GLcharARB* files[1];

        // shader Compilation variable
        GLint result;				// Compilation code result
        GLint errorLoglength ;
        char* errorLogText;
        GLsizei actualErrorLogLength;

        char buffer[400000];
        memset(buffer,0,400000);

        // This will raise a warning on MS compiler
        pfile = fopen(filename, "rb");
        if(!pfile)
        {
            printf("Sorry, can't open file: '%s'.\n", filename);
            exit(0);
        }

        fread(buffer,sizeof(char),400000,pfile);
        //printf("%s\n",buffer);


        fclose(pfile);

        handle = glCreateShaderObjectARB(type);
        if (!handle)
        {
            //We have failed creating the vertex shader object.
            printf("Failed creating vertex shader object from file: %s.",filename);
            exit(0);
        }

        files[0] = (const GLcharARB*)buffer;
        glShaderSourceARB(
                          handle, //The handle to our shader
                          1, //The number of files.
                          files, //An array of const char * data, which represents the source code of theshaders
                          NULL);

        glCompileShaderARB(handle);

        //Compilation checking.
        glGetObjectParameterivARB(handle, GL_OBJECT_COMPILE_STATUS_ARB, &result);

        // If an error was detected.
        if (!result)
        {
            //We failed to compile.
            printf("Shader '%s' failed compilation.\n",filename);

            //Attempt to get the length of de aplicar a sombra consiste em renderizar a cena vista da posição da câmera, e para cada pixel criado, o mesmo é transformado para a visão da luz. Então é feita uma comparação da distancia desse pixel com a luz e o valor armazenado no shadow map. Se a distância pixel-luz for maior que o valor armazenado no shadow map entã our error log.
            glGetObjectParameterivARB(handle, GL_OBJECT_INFO_LOG_LENGTH_ARB, &errorLoglength);

            //Create a buffer to read compilation error message
            //errorLogText = malloc(sizeof(char) * errorLoglength);

            //Used to get the final length of the log.
            //glGetInfoLogARB(handle, errorLoglength, &actualErrorLogLength, errorLogText);

            // Display errors.
            //printf("%s\n",errorLogText);

            // Free the buffer malloced earlier
            free(errorLogText);
        }

        return handle;
    }


    void Rrender::initWindow(int w, int h, float near, float far, bool fullScreen)
    {
        atexit(SDL_Quit);
        if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
            fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
            exit(1);
        }


        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        if(fullScreen)
            SDL_Surface *screen = SDL_SetVideoMode(w, h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL | SDL_FULLSCREEN);
        else
            SDL_Surface *screen = SDL_SetVideoMode(w, h, 32, SDL_DOUBLEBUF | SDL_HWSURFACE | SDL_OPENGL);
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        gluPerspective(60, w / h, (GLfloat)near,(GLfloat)far);

        glMatrixMode(GL_MODELVIEW);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_TEXTURE_2D);

        glShadeModel(GL_FLAT);
        glEnable (GL_BLEND);
        glEnable(GL_CULL_FACE);

        glEnable(GL_NORMALIZE);

        glClearColor( 0.0, 0.0, 1.0, 1.0 );

        glEnable(GL_LIGHTING);

        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

        glEnable(GL_NORMALIZE);
        glewInit();

	}

    void Rrender::loadLights()
    {
        int i;
        int LIGHTn = 0x4000; // == GL_LIGHT0 enum
        if(!this->scene->LightLamps.empty())
        {

            glShadeModel(GL_SMOOTH);
            for(i = 0; i < this->scene->LightLamps.size();++i)
            {
                glEnable(LIGHTn);
                RlightLamp *lamp = this->scene->LightLamps[i];
                glLightfv(LIGHTn, GL_AMBIENT, lamp->getAmbient());
                glLightfv(LIGHTn, GL_DIFFUSE, lamp->getDiffuse());
                glLightfv(LIGHTn, GL_SPECULAR, lamp->getSpecular());
                float pos[4] = {lamp->getLocX(),lamp->getLocY(),lamp->getLocZ(),1.0f};

                glLightfv(LIGHTn, GL_POSITION, pos);
               //glDisable(LIGHTn);

            }

        }
    }

    void Rrender::draw()
    {

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

                    //glBegin(GL_TRIANGLES);
                   /*
                    for(j=0;j<obj->faces.size();j++)
                    {
                        if(!obj->uvs.empty())
                            glTexCoord2f(obj->uvs[obj->faces[j][1]-1][0],obj->uvs[obj->faces[j][1]-1][1]);
                       // cout << obj->uvs[obj->faces[j][1]-1][0] << endl;
                        if(!obj->normals.empty())
                            glNormal3f(obj->normals[obj->faces[j][2]-1][0],obj->normals[obj->faces[j][2]-1][1],obj->normals[obj->faces[j][2]-1][2]);
                       // glVertex3f(obj->vertices[obj->faces[j][0]-1][0],obj->vertices[obj->faces[j][0]-1][1],obj->vertices[obj->faces[j][0]-1][2] );

                    }
                    glEnd();
                    */

                    int x = 6;
                    if(obj->isUv)
                        x = 9;
                    glEnableClientState(GL_NORMAL_ARRAY);
                    glEnableClientState(GL_VERTEX_ARRAY);

                    if(obj->isUv)
                        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                        //glBindBuffer(GL_ARRAY_BUFFER, obj->vertexId);

                        glNormalPointer(GL_FLOAT, x * sizeof(GLfloat), &obj->mesh[0] + 3);
                    if(obj->isUv)
                        glTexCoordPointer(2, GL_FLOAT, 9 * sizeof(GLfloat), &obj->mesh[0] + 6);
                    glVertexPointer(3, GL_FLOAT,x * sizeof(GLfloat), &obj->mesh[0]);

                        glDrawArrays(GL_TRIANGLES,0,(sizeof(float)*obj->mesh.size())/sizeof(float)/x);
                    if(obj->isUv)
                       glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                    glDisableClientState(GL_VERTEX_ARRAY);
                    glDisableClientState(GL_NORMAL_ARRAY);
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


                        int x = 6;
                        if(lObj->isUv)
                            x = 9;
                        glEnableClientState(GL_NORMAL_ARRAY);
                        glEnableClientState(GL_VERTEX_ARRAY);
                        if(lObj->isUv)
                            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
                            //glBindBuffer(GL_ARRAY_BUFFER, obj->vertexId);

                        glVertexPointer(3, GL_FLOAT,sizeof(float)*x, &lObj->mesh[0]);
                        glNormalPointer(GL_FLOAT, sizeof(float)*x, &lObj->mesh[0]+3);
                        if(lObj->isUv)
                            glTexCoordPointer(2, GL_FLOAT, 9 * sizeof(float), &lObj->mesh[0] + 6);

                        glDrawArrays(GL_TRIANGLES,0,lObj->mesh.size()/x);

                        if(lObj->isUv)
                            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                        glDisableClientState(GL_VERTEX_ARRAY);
                        glDisableClientState(GL_NORMAL_ARRAY);

                    }
                }

                glPopMatrix();

            }

        }
    }

    int frameCount = 0,  previousTime;
    void calculateFPS()
    {
        //  Increase frame count
        frameCount++;

        int currentTime;
        //  Get the number of milliseconds since glutInit called
        //  (or first call to glutGet(GLUT ELAPSED TIME)).
        currentTime = glutGet(GLUT_ELAPSED_TIME);

        //  Calculate time passed
        int timeInterval = currentTime - previousTime;

        if(timeInterval > 1000)
        {
            float fps;
            //  calculate the number of frames per second
            fps = frameCount / (timeInterval / 1000.0f);

            //  Set time
            previousTime = currentTime;

            cout << "FPS: " << fps << endl;

            //  Reset frame count
            frameCount = 0;

        }
    }
	void Rrender::render(void)
    {

        //First pass - from light's point of view
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1000.0f);
        glLoadIdentity();

        if(this->scene->fog_enable)
            this->scene->enableFog();
        else
            this->scene->disableFog();
        gluLookAt (this->camera->getLocX(), this->camera->getLocY(), this->camera->getLocZ(),
           this->camera->getLocTX(), this->camera->getLocTY(),this->camera->getLocTZ(),
            0,1,0);

        this->loadLights();
        this->draw();

        calculateFPS();
		SDL_GL_SwapBuffers();
	}

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
        bool fullscreen = lua_toboolean( l, 6 );
        render->initWindow(a,b,near, far, fullscreen);

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
