//hi. this code rotates a cube. #practice_from_utube_tut
#include<bits/stdc++.h>
#include<GL/glut.h>
#include<graphics.h>
using namespace std;
float x= 0.0;
void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear
  glLoadIdentity();//reset all transformation meaning origin //remains same;
  //draw
  glTranslatef(0.0, 0.0, -8.0);//can not call bw glbegin nd glend need to call b4 making the actual drawing.
    glRotatef(x, 1.0, 1.0, 1.0);
  glBegin(GL_QUADS);//specify vertwx
  // glPointSize(10.0);//resize points
  //gl traingles;
  //glcuboid
     glColor3f(1.0,1.0,0.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,1.0,1.0);//cclockwise
    //back
    glColor3f(0.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,1.0,-1.0);//clockwise
    //right
    glColor3f(1.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    //left
    glColor3f(0.5,0.0,0.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    //top
    glColor3f(0.0,0.5,0.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    //bottom
    glColor3f(0.0,0.0,0.5);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);


  glEnd();
 glutSwapBuffers();
}
void reshape(int w, int h)
{
  //viewport
  glViewport(0,0, (GLsizei)w, (GLsizei)h);  //whole screen
  glMatrixMode(GL_PROJECTION);              //change matrix mode
   glLoadIdentity();                        //reset
gluPerspective(60, 1, 2.0, 50.0);           //it is the frustum of the view in 3 d
   glMatrixMode(GL_MODELVIEW);
}
void init()
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
   glEnable(GL_DEPTH_TEST);

}
void timer(int)
{
  glutPostRedisplay();//opengl will call the display fn;
  glutTimerFunc(1000/60, timer, 0);
    x+=0.8*2;
    if(x>360.0)
    x-=360.0;
}
int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB  | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(500, 500);

  glutCreateWindow("Window 1");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutTimerFunc(0, timer, 0);
  init();


  glutMainLoop();
  
    return 0;
}
