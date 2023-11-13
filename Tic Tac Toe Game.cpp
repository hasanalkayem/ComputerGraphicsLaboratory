#include<windows.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1416
#define CROSS 1
#define DONUT 2
#define NOTHING 0

int windowSize = 500;
int boardLeft = 0;
int boardRight = 90;
int boardBottom = 0;
int boardTop = 90;

int gameMatrix[3][3] =
{
    {NOTHING, NOTHING, NOTHING},
    {NOTHING, NOTHING, NOTHING},
    {NOTHING, NOTHING, NOTHING}
};




int squareLength = 30;

bool PlayerIsCross = true;
bool IsGameFinished = false;

void drawCirlePerimeter(float cx, float cy, float radius, int slices);
void drawRectangle(float length, float width);
void drawPlusObject(float length, float width);
void drawCircleWithPolygon(float cx, float cy, float radius, int slices);

bool IsPlayerWin(int player)
{
    int i,j;
    bool flag = (gameMatrix[0][0] == player) && (gameMatrix[0][1] == player) && (gameMatrix[0][2] == player);
    flag |= (gameMatrix[1][0] == player) && (gameMatrix[1][1] == player) && (gameMatrix[1][2] == player);
    flag |= (gameMatrix[2][0] == player) && (gameMatrix[2][1] == player) && (gameMatrix[2][2] == player);

    flag |= (gameMatrix[0][0] == player) && (gameMatrix[1][0] == player) && (gameMatrix[2][0] == player);
    flag |= (gameMatrix[0][1] == player) && (gameMatrix[1][1] == player) && (gameMatrix[2][1] == player);
    flag |= (gameMatrix[0][2] == player) && (gameMatrix[1][2] == player) && (gameMatrix[2][2] == player);

    flag |= (gameMatrix[0][0] == player) && (gameMatrix[1][1] == player) && (gameMatrix[2][2] == player);
    flag |= (gameMatrix[0][2] == player) && (gameMatrix[1][1] == player) && (gameMatrix[2][0] == player);

    return flag;
}

void drawGameBoard()
{
    glBegin(GL_LINE_LOOP);
    {
        glVertex2d(boardLeft, boardBottom);
        glVertex2d(boardLeft,boardTop);
        glVertex2d(boardRight,boardTop);
        glVertex2d(boardRight,boardBottom);
    }
    glEnd();

    glBegin(GL_LINES);
    {
        glVertex2d(0,30);
        glVertex2d(90,30);

        glVertex2d(0,60);
        glVertex2d(90,60);

        glVertex2d(30,0);
        glVertex2d(30,90);

        glVertex2d(60,0);
        glVertex2d(60,90);
    }
    glEnd();
}

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

void drawRectangle(float length, float width)
{
    glBegin(GL_QUADS);
    {
        glVertex2d(0, width/2);
        glVertex2d(length, width/2);
        glVertex2d(length, -width/2);
        glVertex2d(0, -width/2);
    }
    glEnd();
}

void drawDonut(float radius, float width, float cx, float cy)
{
    glColor3f(1,0,0);
    drawCircleWithPolygon(cx, cy, radius+width, 40);
    glColor3f(0,0,0);
    drawCircleWithPolygon(cx, cy, radius, 40);
}


void drawPlusObject(float length, float width)
{
    glPushMatrix();
    {
        //Simple Transformation
        glTranslated(-length/2, 0, 0);
        drawRectangle(length, width);
    }
    glPopMatrix();

    glPushMatrix();
    {
        //Composite Transformation
        glRotated(90,0,0,1);
        glTranslated(-length/2, 0, 0);
        drawRectangle(length, width);
    }
    glPopMatrix();

}


void drawCrossObject(float length, float width, float cx, float cy)
{
    glColor3f(0,0,1);
    glPushMatrix();
    {
        glTranslated(cx, cy, 0);
        glRotated(45, 0, 0, 1);
        drawPlusObject(length, width);
    }
    glPopMatrix();
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



void display(void)
{
    int i,j;

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


    glColor3f(0,1,0);
    drawGameBoard();

    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            float cx = 15.0 + i*30.0;
            float cy = 75.0 - j*30.0;

            if(gameMatrix[i][j] == CROSS)
            {
                drawCrossObject(20,2,cx,cy);
            }
            else if(gameMatrix[i][j] == DONUT)
            {
                drawDonut(10,2,cx,cy);
            }
        }
    }

	glFlush();
}

void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-2.0, 100.0, -2.0, 100.0, -25.0, 25.0);
}

void playGame(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && !IsGameFinished)
    {
        printf("P(%d, %d)\n",x,y);

        float px = -2 + (x/500.0) * 102;
        float py = 100 - (y/500.0) * 102;

        printf("PX (%f, %f)\n", px, py);

        int ix = (int)(px/30);
        int iy = 2 - (int)(py/30);

        printf("IX (%d, %d)\n", ix, iy);

        if(gameMatrix[ix][iy] == NOTHING)
        {
            if(PlayerIsCross)
            {
                gameMatrix[ix][iy] = CROSS;
                PlayerIsCross = false;

                if(IsPlayerWin(CROSS))
                {
                    printf("CROSS WIN");
                    IsGameFinished = true;
                }
            }
            else{
                gameMatrix[ix][iy] = DONUT;
                PlayerIsCross = true;

                if(IsPlayerWin(DONUT))
                {
                    printf("DONUT WIN");
                    IsGameFinished = true;
                }
            }
        }

        glutPostRedisplay();
    }
}


int main()
{
    //Rasterization
	glutInitWindowSize (windowSize, windowSize);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("2D Objects");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(playGame);
	glutMainLoop();
	return 0;
}