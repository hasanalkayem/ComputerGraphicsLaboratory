#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1416



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    {
        glColor3f(1,1,1);
        glVertex2d(-25,0);
        glVertex2d(25, 0);

        glVertex2d(0,-25);
        glVertex2d(0,25);
    }
    glEnd();

    glBegin(GL_LINE_LOOP);
    {
        glColor3f(1,1,0);
        glVertex2d(-20,20);
        glVertex2d(20,20);
        glVertex2d(20,-20);
        glVertex2d(-20,-20);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor3f(1,0,0);
        glVertex2d(0,15);
        glVertex2d(15,0);
        glVertex2d(0,-15);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
        glColor3f(0,1,0);
        glVertex2d(-18,15);
        glVertex2d(0,15);
        glVertex2d(0,0);
        glVertex2d(-18,0);
    }
    glEnd();

    glBegin(GL_POLYGON);
    {
        glColor3f(0,0,1);
        glVertex2d(-18,0);
        glVertex2d(0,0);
        glVertex2d(0,-15);
        glVertex2d(-5,-15);
        glVertex2d(-18,-5);
    }
    glEnd();

	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-25.0, 25.0, -25.0, 25.0, -25.0, 25.0);
}


int main()
{
    //Rasterization
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("2D Objects");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}
