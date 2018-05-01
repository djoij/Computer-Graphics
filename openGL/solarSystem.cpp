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
    glutTimerFunc(1000.0/60.0, timer, 0); //set to use 60fps
    //glutIdleFunc(idleFunc); //for higher frames

    glutMainLoop();
    return 0;
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
    glLoadIdentity();
    glTranslatef(0.0,0.0,-3.0);
    glColor3f(1.0, 1.0, 0); 
    glRotatef(sunRot,1.0,0.0,0.0);
    glRotatef(sunRot,0.0,1.0,0.0);
    glRotatef(sunRot,0.0,0.0,1.0);
    glScalef(0.2,0.2,0.2);
    glutSolidSphere(0.5,20,20);//radius,..
    //EARTH
    glLoadIdentity();
    xForEarth = cos((day%orbitEarth)*2*PI/orbitEarth)*0.1183f*1.75;
    yForEarth = sin((day%orbitEarth)*2*PI/orbitEarth)*0.117307f*1.75;
    //glColor3f(0.0, 0.0, 1.0); //blue
    glColor4f(0.0f, 1.0f, 1.0f, 1.0f);//lightblue
    glTranslatef(xForEarth-0.0019766747,yForEarth,-3.0f);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(0.2,0.2,0.2);
    glutSolidSphere(0.03,20,20); //comment this line for teapot
    //glutWireTeapot(0.2); //Uncomment this line to add teapot 
    //NEPTUNE
    glLoadIdentity();
    xForNept = cos((day%orbitNept)*2*PI/orbitNept)*1.0f*1.75;
    yForNept = sin((day%orbitNept)*2*PI/orbitNept)*0.995261f*1.75;
    glColor3f(0.0, 0.0, 1.0); 
    glTranslatef(xForNept-0.009456,yForNept,-3.0f);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(0.2,0.2,0.2);
    //glutSolidSphere(0.12,20,20); //comment this line for teapot
    glutWireTeapot(0.5); //Uncomment this line to add teapot 
    //MARS
    glLoadIdentity();
    xForMars = cos((day%orbitMars)*2*PI/orbitMars)*0.177f*1.75;
    yForMars = sin((day%orbitMars)*2*PI/orbitMars)*0.16f*1.75;
    glColor3f(1.0, 0.0, 0.0); 
    glTranslatef(xForMars-0.016638,yForMars,-3.0f);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(0.2,0.2,0.2);
    glutSolidSphere(0.02,20,20);
    //JUPITER
    glLoadIdentity();
    xForJupiter = cos((day%orbitJupiter)*2*PI/orbitJupiter)*0.605578f*1.75;
    yForJupiter = sin((day%orbitJupiter)*2*PI/orbitJupiter)*0.590586f*1.75;
    glColor3f(0.5f, 0.35f, 0.05f); 
    glTranslatef(xForJupiter-0.0296127642,yForJupiter,-3.0f);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);
    glScalef(0.2,0.2,0.2);
    //glutSolidSphere(0.2,20,20); //comment this line for teapot
    glutWireTeapot(0.5); //Uncomment this line to add teapot 
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