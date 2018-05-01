#include <GL/glut.h>
#include    <windows.h>                           // Header File For Windows
#include    <stdio.h>                         // Header File For Standard Input/Output ( NEW )
#include    <gl/gl.h>                         // Header File For The OpenGL32 Library
#include    <gl/glu.h>                            // Header File For The GLu32 Library
#include    <gl/glaux.h>                          // Header File For The GLaux Library
 
HDC     hDC=NULL;                           // Private GDI Device Context
HGLRC       hRC=NULL;                           // Permanent Rendering Context
HWND        hWnd=NULL;                          // Holds Our Window Handle
HINSTANCE   hInstance;                          // Holds The Instance Of The Application
 
bool        keys[256];                          // Array Used For The Keyboard Routine
bool        active=TRUE;                            // Window Active Flag
bool        fullscreen=TRUE;                        // Fullscreen Flag
 
GLfloat     xrot;                               // X Rotation ( NEW )
GLfloat     yrot;                               // Y Rotation ( NEW )
GLfloat     zrot;                               // Z Rotation ( NEW )
 
GLuint      texture[1];                         // Storage For One Texture ( NEW )
 
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);               // Declaration For WndProc

AUX_RGBImageRec *LoadBMP(char *Filename)                    // Loads A Bitmap Image
{
    FILE *File=NULL;                            // File Handle
    if (!Filename)                              // Make Sure A Filename Was Given
    {
        return NULL;                            // If Not Return NULL
    }
    File=fopen(Filename,"r");                       // Check To See If The File Exists
    if (File)                               // Does The File Exist?
    {
        fclose(File);                           // Close The Handle
        return auxDIBImageLoad(Filename);               // Load The Bitmap And Return A Pointer
    }
 return NULL;                                // If Load Failed Return NULL
}

int LoadGLTextures()                                // Load Bitmaps And Convert To Textures
{
    int Status=FALSE;                           // Status Indicator
    AUX_RGBImageRec *TextureImage[1];                   // Create Storage Space For The Texture 
    memset(TextureImage,0,sizeof(void *)*1);                // Set The Pointer To NULL
    // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
    if (TextureImage[0]=LoadBMP("Data/NeHe.bmp"))
    {
        Status=TRUE;                            // Set The Status To TRUE
        glGenTextures(1, &texture[0]);                  // Create The Texture
        // Typical Texture Generation Using Data From The Bitmap
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        // Generate The Texture
        glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering
    }


    
if (TextureImage[0])                            // If Texture Exists
{
    if (TextureImage[0]->data)                   // If Texture Image Exists
    {
        free(TextureImage[0]->data);             // Free The Texture Image Memory
    }
 
    free(TextureImage[0]);                      // Free The Image Structure
}


    
    return Status;                              // Return The Status
}


    
int InitGL(GLvoid)                              // All Setup For OpenGL Goes Here
{
    if (!LoadGLTextures())                          // Jump To Texture Loading Routine ( NEW )
    {
        return FALSE;                           // If Texture Didn't Load Return FALSE ( NEW )
    }
 
    glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective Calculations
    return TRUE;                                // Initialization Went OK
}

    
int DrawGLScene(GLvoid)                             // Here's Where We Do All The Drawing
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);         // Clear Screen And Depth Buffer
    glLoadIdentity();                           // Reset The Current Matrix
    glTranslatef(0.0f,0.0f,-5.0f);                      // Move Into The Screen 5 Units


    glRotatef(xrot,1.0f,0.0f,0.0f);                     // Rotate On The X Axis
    glRotatef(yrot,0.0f,1.0f,0.0f);                     // Rotate On The Y Axis
    glRotatef(zrot,0.0f,0.0f,1.0f);                     // Rotate On The Z Axis


glBindTexture(GL_TEXTURE_2D, texture[0]);               // Select Our Texture


glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
glEnd();

    xrot+=0.3f;                             // X Axis Rotation
    yrot+=0.2f;                             // Y Axis Rotation
    zrot+=0.4f;                             // Z Axis Rotation
    return true;                                // Keep Going
}

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
    glutCreateWindow("windows");
    glutDisplayFunc(DrawGLScene);
    //glutReshapeFunc(reshape);
    glutTimerFunc(1000.0/60.0, timer, 0); //set to use 60fps

    glutMainLoop();
    return 0;
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