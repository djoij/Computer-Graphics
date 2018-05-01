#include <GL/glut.h>
#include <math.h>

GLfloat xRotated, yRotated, zRotated;
GLint count=0;
GLfloat xForEarth,yForEarth;
GLfloat DEG2RAD=3.14/180;
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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glutDisplayFunc(sphere);
    glutReshapeFunc(reshape);
    glutTimerFunc(1000.0/60.0, timer, 0);
    //glutIdleFunc(idleFunc);

    glutMainLoop();
    return 0;
}


void sphere(void)
{

    glMatrixMode(GL_MODELVIEW);
    // clear the drawing buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // clear the identity matrix.
    glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
    glTranslatef(0,0.0,-5.0);
    // yellowcolor used to draw.
    glColor3f(1.0, 1.0, 0); 
    // changing in transformation matrix.
    // rotation about X axis
    // glRotatef(xRotated,1.0,0.0,0.0);
    // // rotation about Y axis
    // glRotatef(yRotated,0.0,1.0,0.0);
    // // rotation about Z axis
    // glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.
    glutSolidSphere(0.3,20,20);//radius,..
    // Flush buffers to screen
     glLoadIdentity();
    // traslate the draw by z = -4.0
    // Note this when you decrease z like -8.0 the drawing will looks far , or smaller.
     if(count>359)
        count=0;
     else
        count++;
     xForEarth = cos(count*DEG2RAD)*1.5f;//to change the x co-ordinate
     yForEarth = sin(count*DEG2RAD)*1.0;//to change the y co-ordinate
    //Red color used to draw.
    glColor3f(0.0, 0.0, 1.0); 
    // changing in transformation matrix.
    // rotation about X axis
    glTranslatef(xForEarth,yForEarth,-5.0f);
     glRotatef(xRotated,1.0,0.0,0.0);
    // // rotation about Y axis
     glRotatef(yRotated,0.0,1.0,0.0);
    // rotation about Z axis
    glRotatef(zRotated,0.0,0.0,1.0);
    // scaling transfomation 
    glScalef(1.0,1.0,1.0);
    // built-in (glut library) function , draw you a sphere.

    
    glutSolidSphere(0.2,20,20);
    glFlush();        
    // sawp buffers called because we are using double buffering 
   // glutSwapBuffers();
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