#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1416

void drawCirlePerimeter(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_LINE_LOOP);
    {
        for(i=0;i<slices;i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithPolygon(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_POLYGON);
    {
        for(i=0;i<slices;i++)
        {
            angle = ((2 * PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawCircleWithTriangles(float cx, float cy, float radius, int slices)
{
    int i;
    float angle1, angle2;

    glBegin(GL_TRIANGLES);
    {
        for(i=0; i<slices; i++)
        {
            angle1 = ((2*PI)/slices) * i;
            angle2 = ((2*PI)/slices) * (i+1);

            glVertex2f(cx, cy);
            glVertex2f(cx + radius * cos(angle1), cy + radius * sin(angle1));
            glVertex2f(cx + radius * cos(angle2), cy + radius * sin(angle2));
        }
    }
    glEnd();
}

void drawUpperCircleWithPolygon(float cx, float cy, float radius, int slices)
{
    int i;
    float angle, x, y;
    glBegin(GL_POLYGON);
    {
        for(i=0;i<=slices;i++)
        {
            angle = ((PI)/slices) * i;
            x = cx + radius * cos(angle);
            y = cy + radius * sin(angle);
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void drawTree()
{

    glBegin(GL_QUADS);
    {
        glColor3f(0, 0, 1);
        glVertex2f(60, 0);
        glVertex2f(65, 0);
        glVertex2f(65, 10);
        glVertex2f(60, 10);

        glColor3f(0,1,0);
        glVertex2f(75, 10);
        glVertex2f(65, 20);
        glVertex2f(60, 20);
        glVertex2f(50, 10);
    }
    glEnd();

    glBegin(GL_TRIANGLES);
    {
        glColor3f(0, 1, 0);
        glVertex2f(70, 20);
        glVertex2f(62.5, 30);
        glVertex2f(55, 20);
    }
    glEnd();
}



void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    /*
    glBegin(GL_LINES);
    {
        glColor3f(1,1,1);
        glVertex2d(-2,0);
        glVertex2d(100, 0);

        glVertex2d(0,-20);
        glVertex2d(0,50);
    }
    glEnd();
    */

    glColor3f(1, 0, 0);
    drawUpperCircleWithPolygon(20, 0, 10, 40);

    drawTree();

	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-2, 100, -20, 50, 0, 100);
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
