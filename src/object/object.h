#include "../locate/locate.h"

#include <GL/glut.h>
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
            Vertex3*	getMesh();
            void	setMesh(Vertex3 *);
            void	setScale(float x, float y, float z);
            void    setScaleX(float x);
            void    setScaleY(float y);
            void    setScaleZ(float z);
            float	getScaleX();
            float	getScaleY();
            float	getScaleZ();
			void 	loadFileOBJ(char *);
			char type;
		protected:
            Vertex3 *mesh;
			float *uv;
			float *normal;
            const char* uid;
            float sx,sy,sz;
	};
}
#endif
