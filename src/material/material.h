
#include <vector>
#include <iostream>
#include <lua5.2/lua.hpp>
#include <GL/glut.h>

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

namespace red
{
	class Rmaterial
	{
		public:
			Rmaterial();
            ~Rmaterial(){}
            std::vector<std::vector<float> > specular;
            std::vector<std::vector<float> > diffuse;
            std::vector<std::vector<float> > ambient;
            GLuint textureId;
            float specularCof;
            float transparent;

		private:


            int shadeModel;
            //void setSpecular(float r= 0.5,float g = 0.5,float b = 0.5,float a = 1);
            //void setShininess(float r = 0.5,float g = 0.5,float b = 0.5,float a = 1);
            //void setShadeModel(int e);

            //float* getSpecular();
            //float* getShininess();
            //int getShadeModel();

	};
}

#endif
