#include "text.h"
#include <GL/glut.h>

void Rtext::drawText(char *string, float x, float y, float z)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    return;
}
