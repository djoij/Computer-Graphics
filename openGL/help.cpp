#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void) 
{
   //GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   //GLfloat mat_shininess[] = { 50 };
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 2.0, 0.0, 0.0, 0.0 };
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv(GL_LIGHT0, GL_POSITION, light_position);


GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_position[] = { -2.0, 0.0, 0.0, 0.0 };
//GLfloat spot_direction[] = { -1.0, -1.0, 0.0 };
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    //glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);



glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5);
//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
//glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);
//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
//glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);


   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   //glEnable(GL_LIGHT1);
   glEnable(GL_DEPTH_TEST);
}
void wall(double thickness)    // function to create the walls with given thickness
{
    //glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    //glPopMatrix();
}

void display(void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0); 
    wall(0.2);
    
   glutSolidSphere (0.5, 20, 16);

    glScaled(-1.0,-1.0,-1.0);
   glutSolidTeapot(0.2);
   glFlush ();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-1.5, 1.5, -1.5*(GLfloat)h/(GLfloat)w,
         1.5*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
   else
      glOrtho (-1.5*(GLfloat)w/(GLfloat)h,
         1.5*(GLfloat)w/(GLfloat)h, -1.5, 1.5, -10.0, 10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1920, 1080); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}