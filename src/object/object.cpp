
#include "object.h"

namespace red
{
   // Robject::Robject()
    //{	}
    Robject::Robject(const char* uid)
	{
		this->uid = uid;
        this->sx = 1;
        this->sy = 1;
        this->sz = 1;
    }
    Robject::~Robject(){}

    std::vector<GLfloat> Robject::getMesh()
	{
		return this->mesh;
	}
    void 	Robject::setMesh(std::vector<GLfloat> me)
	{
		this->mesh = me;	
	}
    void 	Robject::setScale(float x, float y, float z)
    {
        this->sx = x;
        this->sy = x;
        this->sz = x;
    }
    void 	Robject::setScaleX(float x)
    {
        this->sx = x;
    }
    void 	Robject::setScaleY(float y)
    {
        this->sy = y;
    }
    void 	Robject::setScaleZ(float z)
    {
        this->sz = z;
    }
    float 	Robject::getScaleX()
    {
        return this->sx;
    }
    float 	Robject::getScaleY()
    {
        return this->sy;
    }
    float	Robject::getScaleZ()
    {
        return this->sz;
    }
    const char* Robject::getUID()
	{
		return this->uid;
	}
}


