#include "../locate/locate.h"

#include <GL/glut.h>
#include <vector>
#ifndef __OBJECT_H__
#define __OBJECT_H__
namespace red
{

	typedef struct{
		GLfloat x,y,z;
	} Vertex3;

	class Robject : public Rlocate
	{
		public:
			//Robject();
            Robject(const char*);
            ~Robject();
            const char* getUID();
            std::vector<GLfloat> getMesh();
            void	setMesh(std::vector<GLfloat> me);
            void	setScale(float x, float y, float z);
            void    setScaleX(float x);
            void    setScaleY(float y);
            void    setScaleZ(float z);
            float	getScaleX();
            float	getScaleY();
            float	getScaleZ();
			void 	loadFileOBJ(char *);
			char type;
            std::vector<float> mesh;
            std::vector<float> uv;
            std::vector<float> normal;
        protected:
            const char* uid;
            float sx,sy,sz;
	};
}
#endif
