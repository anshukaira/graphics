//heres a heart beating. 
#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;
float x= 0.0;//used in animation to change the axis of z
int state=1;
void display()
{
  glClear(GL_COLOR_BUFFER_BIT);//clear
  glLoadIdentity();//reset all transformation meaning origin //remains same;
  //draw
  glTranslatef(0.0, 0.0, x);//used for transforming the origin and hence the objcan not be called bw glbegin nd glend need to call b4 making the actual drawing.
 glColor3f(1.0, 0.0, 0.0);
 glPointSize(5.0);
 glBegin(GL_POINTS);//if we use POLYGONS instead of point the heart will be colored.
        for (float x = -1.139; x <= 1.139; x += 0.001) //loop for drawing a heart
        {
            float delta = cbrt(x*x) * cbrt(x*x) - 4*x*x + 4;
            float y1 = (cbrt(x*x) + sqrt(delta)) / 2;
            float y2 = (cbrt(x*x) - sqrt(delta)) / 2;
            glVertex2f(x, y1);//sets the points
            glVertex2f(x, y2);
        }

  glEnd();
 glutSwapBuffers();//this is basically used for providing two frames, to cope up with distortion which might be resulted from not loading the full img nd finishing of time of a particular unit of time in animation.
}
void reshape(int w, int h)
{
  //viewport
  glViewport(0,0, (GLsizei)w, (GLsizei)h);//whole screen
  glMatrixMode(GL_PROJECTION);//change matrix mode
   glLoadIdentity();//reset
gluPerspective(60,(GLsizei)w/(GLsizei)h , 2.0, 50.0);//it is the frustum of the view in 3 d
   glMatrixMode(GL_MODELVIEW);
}
void init()//initializing function
{
  glClearColor(0.0, 0.0, 0.0, 0.0);//
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
glEnable(GL_COLOR_MATERIAL);
}
void timer(int)
{
  glutPostRedisplay();//opengl will call the display fn;
  glutTimerFunc(1000/60, timer, 0);
    switch(state)
    {
        case 1: 
        if(x<-5)
        x+= 0.30;
        else
        state =-1;
        break;
        case -1: 
        if(x>-15)
        x-=0.30;
        else
        {
            state=1;
        }
        break;
        
    }
}
int main(int argc, char* argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB  | GLUT_DOUBLE);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(500, 500);

  glutCreateWindow("Window 1");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);//if reshape is needed
  glutTimerFunc(0, timer, 0);//animation timing fn
  init();


  glutMainLoop();
  
    return 0;
}
