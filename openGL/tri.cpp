#include <GL/glut.h>
#include <math.h>

GLfloat xRotated, yRotated, zRotated;
GLint day=0;
GLfloat xForEarth,yForEarth,xForMars,yForMars,xForJupiter,yForJupiter,xForNept,yForNept;
GLint orbitMars=687;
GLint orbitJupiter=4329;
GLint orbitNept=60182;
GLint orbitEarth=365;
GLfloat PI=3.14;
GLfloat sunRot=50;

void sphere(void);
void reshape(int x, int y);

void idleFunc(void)
{
 
     yRotated += 1.0;
     
    sphere();
}

void timer(int)
{
    /* update animation */
    yRotated += 1.0;
    sunRot += 0.1;
    sphere();
    glutTimerFunc(1000.0/60.0, timer, 0);
}

int main (int argc, char **argv)
{
    glutInit(&argc, argv); 
    glutInitWindowSize(1920,1080);
    glutCreateWindow("SolarSystem");
    xRotated = yRotated = zRotated = 30.0;
    xRotated=43;
    yRotated=50;
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glutDisplayFunc(sphere);
    glutReshapeFunc(reshape);
    //glutTimerFunc(1000.0/60.0, timer, 0); //set to use 60fps
    //glutIdleFunc(idleFunc); //for higher frames

    glutMainLoop();
    return 0;
}

void wall(double thickness)    // function to create the walls with given thickness
{
    glPushMatrix();
    glTranslated(0.5,0.5*thickness,0.5);
    glScaled(1.0,thickness,1.0);
    glutSolidCube(1.0);
    glPopMatrix();
}
void sphere(void)
{
    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    if(day==2*orbitNept)
        day=0;
     else
        day++;
    //SUN
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double winlet=1.0;
    glOrtho(-winlet*64/48,winlet*64/48.0,-winlet*64/48,winlet*64/48,0.6,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.3,1.38,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glTranslated(0.08,0.08,0.08);
    glPushMatrix();
    glTranslated(0.6,0.38,0.5);
    glRotated(30,0,1,0);
    //glutSolidSphere(0.5,20,20);//radius,..
    //EARTHglPopMatrix();
    glPushMatrix();
    glTranslated(0.25,0.42,0.35);
    glPopMatrix();
    glPushMatrix();
    glTranslated(0.4,0,0.4);    
    glPopMatrix();
    
    glColor3f(1.0, 1.0, 0.0); 
    wall(0.2);
    glPushMatrix();
    glRotated(-90.0,1.0,0.0,0.0);
    glColor3f(1.0, 0.0, 1.0); 
    wall(0.02);
    glPopMatrix();
    glRotated(90.0,0.0,0.0,180.0);
    glColor3f(1.0, 0.0, 0.0); 
    wall(0.02);
    glPopMatrix();
    glRotated(0,0.0,0.0,180.0);
    glColor3f(1.0, 1.0, 1.0); 
    wall(0.02);
    glPopMatrix();
    glFlush();        
}

void reshape(int x, int y)
{
    if (y == 0 || x == 0) return;   
    glMatrixMode(GL_PROJECTION);  
    glLoadIdentity(); 
    gluPerspective(39.0,(GLdouble)x/(GLdouble)y,0.6,21.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}