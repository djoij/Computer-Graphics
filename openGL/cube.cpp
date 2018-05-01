#include<GL/glut.h>


void displayWalls(){
    // GLfloat mat_ambient[]={0.7f,0.7f,0.7f,0.1f};
    // GLfloat mat_diffuse[]={0.5f,0.5f,0.5f,1.0f};
    // GLfloat mat_specular[]={1.0f,1.0f,1.0f,1.0f};

    GLfloat mat_ambient[]={1.0f,1.0f,1.0f,0.0f};
    GLfloat mat_shininess[]={1000.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);
    


    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    double port=1.0;
    glOrtho(-port*64/48,port*64/48.0,-port*64/48,port*64/48,0.6,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2.3,1.38,2.0,0.0,0.25,0.0,0.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    

    glPushMatrix();
    

    // glTranslated(0.0,0.0,0.0);
    // glutSolidSphere(0.1,20,20);
    glTranslated(0.75,0.09,0.75);

    glScaled(1.52,0.2,1.52);
    glutSolidCube(1.0);
    glPopMatrix();


    glPushMatrix();
    glRotated(-90.0,1.0,0.0,0.0);


     glPushMatrix();
    glTranslated(0.75,0.75*0.02,0.75);
    glScaled(1.52,0.02,1.52);
    glutSolidCube(1.0);
    glPopMatrix();


    glPopMatrix();
    glRotated(90.0,0.0,0.0,1.0);


    glPushMatrix();
    glTranslated(0.75,0.75*0.02,0.75);
    glScaled(1.52,0.02,1.52);
    glutSolidCube(1.0);
    glPopMatrix();



    GLfloat mat1_shininess[]={0.0f};
    GLfloat mat1_ambient[]={0.0f,0.0f,0.0f,0.0f};
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat1_ambient);
    glMaterialfv(GL_FRONT,GL_SHININESS,mat1_shininess);
    glPushMatrix();
    glTranslated(0.7,0.0,.70);
    glScaled(1.52,0.02,1.52);
    glutSolidCube(0.2);
    glPopMatrix();

    

    


  



    glPopMatrix();
    glFlush();
}

int main(int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize(1920,1080);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Room");
    glutDisplayFunc(displayWalls);
    GLfloat light_Intensity[]={1.0f,1.0f,1.0f,1.0f};
    GLfloat light_Position[]={1.0f,1.0f,3.0f,0.0f};

     //GLfloat light_Intensity[]={0.7f,0.7f,0.7f,1.0f};
     GLfloat light1_Position[]={0.0,0.09,0.75};
    glLightfv(GL_LIGHT0,GL_POSITION,light_Position);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light_Intensity);
    glLightfv(GL_LIGHT1,GL_POSITION,light1_Position);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light_Intensity);


    glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glClearColor(0.1,0.1,0.1,0.0);
    glViewport(0,0,640,480);
    glutMainLoop();
    return 0;
}