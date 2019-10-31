#include <GL/glut.h>
#include <bits/stdc++.h>
#include <math.h>

GLfloat light0_ambient[] =
{0.2, 0.2, 0.2, 1.0};
GLfloat light0_diffuse[] =
{0.0, 0.0, 0.0, 1.0};
GLfloat light1_diffuse[] =
{1.0, 0.0, 0.0, 1.0};
GLfloat light1_position[] =
{1.0, 1.0, 1.0, 0.0};
GLfloat light2_diffuse[] =
{0.0, 1.0, 0.0, 1.0};
GLfloat light2_position[] =
{-1.0, -1.0, 1.0, 0.0};
float s = 0.0;
GLfloat angle1 = 0.0, angle2 = 0.0;

void 
display(void)
{
  static GLfloat amb[] =
  {0.4, 0.4, 0.4, 0.0};
  static GLfloat dif[] =
  {1.0, 1.0, 1.0, 0.0};

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
  glEnable(GL_LIGHT1);
  glDisable(GL_LIGHT2);
  amb[3] = dif[3] = cos(s) / 2.0 + 0.5;
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

  glPushMatrix();  
  glTranslatef(-0.3, -0.3, 0.0);
  glRotatef(angle1, 1.0, 5.0, 0.0);
  glCallList(1);        /* render ico display list */
  glPopMatrix();

  glClear(GL_DEPTH_BUFFER_BIT);
  glEnable(GL_LIGHT2);
  glDisable(GL_LIGHT1);
  amb[3] = dif[3] = 0.5 - cos(s * .95) / 2.0;
  glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);

  glPushMatrix();
  glTranslatef(0.3, 0.3, 0.0);
  glRotatef(angle2, 1.0, 0.0, 5.0);
  glCallList(1);        /* render ico display list */
  glPopMatrix();

  glPushAttrib(GL_ENABLE_BIT);
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_LIGHTING);
  glMatrixMode(GL_PROJECTION); //change matrix mode
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, 1500, 0, 1500);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  /* Rotate text slightly to help show jaggies. */
  glRotatef(4, 0.0, 0.0, 1.0);
 // output(200, 225, "This is antialiased.");
  glDisable(GL_LINE_SMOOTH);
  glDisable(GL_BLEND);
 // output(160, 100, "This text is not.");
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
  glMatrixMode(GL_MODELVIEW);

  glutSwapBuffers();
}

void idle(void)
{
  angle1 = (GLfloat) fmod(angle1 + 0.5, 360.0);
  angle2 = (GLfloat) fmod(angle2 + 1.1, 360.0);
  s += 0.05;
  glutPostRedisplay();
}

void visible(int vis)
{
  if (vis == GLUT_VISIBLE)
    glutIdleFunc(idle);
  else
    glutIdleFunc(NULL);
}

void reshape(int w, int h)
{
  //viewport
  glViewport(0,0, (GLsizei)w, (GLsizei)h);//whole screen
  glMatrixMode(GL_PROJECTION);//change matrix mode
  glLoadIdentity();//reset
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 100.0);//it is the frustum of the view in 3 d
  glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(200, 100);
  glutInitWindowSize(500, 500);
  glutCreateWindow("pattern");
  glutDisplayFunc(display);
  glutVisibilityFunc(visible);
  glutReshapeFunc(reshape);
 
  glNewList(1, GL_COMPILE);  /* create ico display list *///here the list is created 
  glutSolidIcosahedron();
  glEndList();
//init
//gl_enable enables derver side gl capabilities,
  glEnable(GL_LIGHTING);//use the current lighting parameters to compute the vertex color or index
  glEnable(GL_LIGHT0);// include light i(here 0) in the evaluation of the lighting equation. 
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
  glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
  glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
  glEnable(GL_DEPTH_TEST);//do depth comparisons and update the depth buffer. Note that even if the depth buffer exists and the depth mask is non-zero, the depth buffer is not updated if the depth test is disabled.
  glEnable(GL_CULL_FACE);//cull polygons based on their winding in window coordinates
  glEnable(GL_BLEND);// here gl_blend enables blending of rgba values of background nd foreground
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//src nd destiantion for blendfunc
  glEnable(GL_LINE_SMOOTH);//DRAWS line with correct filtering otherwise line would be drawn with aliasing
  glLineWidth(2.0);

  gluLookAt(0.0, 0.0, 5.0,  /* eye is at (0,0,5) */
    0.0, 0.0, 0.0,      /* center is at (0,0,0) */
    0.0, 1.0, 0.);      /* up is in positive Y direction */
  glTranslatef(0.0, 0.0, -1.0);

  glutMainLoop(); //to keep the looping continue until u press cross button
  return 0;             /* ANSI C requires main to return int. */
}
