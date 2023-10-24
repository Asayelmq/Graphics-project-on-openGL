#ifdef APPLE
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Windows.h>//«·’Ê
#define GLFW_KEY_SPACE
#endif
#include <stdlib.h>
#include <iostream>

using namespace std;

GLint win_width = 500,
win_hight = 500;

GLdouble PI = 3.14159265359;

float transValueX;
float transValueY;

float obsX = -1;
float obsY = 0;
float appleSc;
bool col = true;
int i = 0;    //apples counter
int j = 0;   //obstecle counter
int sence;
float appcount = 0.0;

int iAp = 0;
int story = 0;
float applesPlace[4] = { 0.6,1.4,2.2 ,2.6 };
float gx = -1.0;
float gy = 0;
int replaceg;

bool flag = true;  //desplay story 

///for textures///
float transValueX1 = 0.0;
float transValueY1 = 0.0;
float transValueZ1 = 0.0;
float n;
float f;


GLuint myTexture1;
GLuint myTexture2;
GLuint myTexture3;
GLuint myTexture4;
char image1Path[] = "C:/Users/ames8/Desktop/houu_1.bmp";
char image2Path[] = "C:/Users/ames8/Desktop/ppp.bmp";
char image3Path[] = "C:/Users/ames8/Desktop/grannyQFinal.bmp";
char image4Path[] = "C:/Users/ames8/Desktop/gameoverQFinal.bmp";


/////////////END DECLEARATION/////////////////

//http://stackoverflow.com/questions/12518111/how-to-load-a-bmp-on-glut-to-use-it-as-a-texture
GLuint LoadTexture(const char* filename, int width, int height)
{
    GLuint texture;
    unsigned char* data;
    FILE* file;

    //The following code will read in our RAW file

    fopen_s(&file, filename, "rb");

    //file = fopen(&file, "rb");

    if (file == NULL)
    {
        cout << "Unable to open the image file" << endl << "Program will exit :(" << endl;
        exit(0);
        return 0;
    }

    data = (unsigned char*)malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);

    fclose(file);


    // reorder the image colors to RGB not BGR
    for (int i = 0; i < width * height; ++i)
    {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];

        data[index] = R;
        data[index + 2] = B;

    }


    /////////////////////////////////////////
    // All Exercises TODO: load another texture image
    //////
    glGenTextures(1, &texture);            //generate the texture with the loaded data
    glBindTexture(GL_TEXTURE_2D, texture); //bind the texture to it's array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //set texture environment parameters

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    /////////////////////////////////////////

    free(data); //free the texture array

    if (glGetError() != GL_NO_ERROR)
        printf("GLError in genTexture()\n");

    return texture; //return whether it was successfull
}
void init() {
    transValueX1 = 0.0;
    transValueY1 = 0.0;
    transValueZ1 = 2.0;
    n = 0.01;
    f = 50;


    myTexture1 = LoadTexture(image1Path, 612, 612);

    if (myTexture1 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture1 << endl;



    myTexture2 = LoadTexture(image2Path, 612, 612);

    if (myTexture2 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture2 << endl;


    myTexture3 = LoadTexture(image3Path, 612, 612);

    if (myTexture3 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture3 << endl;


    myTexture4 = LoadTexture(image4Path, 612, 612);

    if (myTexture4 == -1)
    {
        cout << "Error in loading the texture" << endl;
    }
    else
        cout << "The texture value is: " << myTexture4 << endl;




    //----------------------


    glMatrixMode(GL_PROJECTION);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);


}

static
void special(int key, int x, int y) //THIS IS THE GIRL BASIC MOVEMENT KEYS CODE :JUMANA
{
    //handle special keys
    switch (key) {

    case GLUT_KEY_HOME:

        break;

    case GLUT_KEY_LEFT:
        transValueX -= .1;
        obsX -= 0.1;

        gx -= .1;
        break;

    case GLUT_KEY_RIGHT:
        transValueX += 0.1;
        obsX += 0.1;

        gx += 0.1;
      
        if ((gx >= 5) && (appleSc == 4)) {

            sence += 1;
            gx = -2.0;
            transValueX = -1;

            appcount = 0;
            appleSc = 0;
            i = 0;
            obsX = -2.0;
            j = 0;
        }

        //cout << "apple in " << applesPlace[i] << endl;
        break;

    case GLUT_KEY_UP:

        if (transValueY < 1.3) {
            transValueY += .1;
            obsY += 0.1;
            gy += 0.1;

            //cout << "girl in y " << girlY << endl;
                   //cout << "apple in " << applesPlace[i] << endl;
        }

        break;

    case GLUT_KEY_DOWN:

        if (transValueY > 0) { //make the girls doesn't go underground

            transValueY -= .1;
            obsY -= 0.1;
            gy -= 0.1;
        }
        break;



    default:

        break;
        //----------------------
    }



}
void key(unsigned char keyPressed, int x, int y) // key handling
{


    switch (keyPressed)
    {
    case 32:
        flag = false;
        break;

    case 'q':


    case'Q':

        exit(0);

        break;



    default:  // instructin
        fprintf(stderr, "\nKeyboard commands:\n\n"
            "q, Q - Quit\n"
            "^ - Jump \n"
            "v - Down \n"
            "> - Go staright \n"
            "< - Go Back\n");
        break;
    }
}
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int triangleAmount = 20; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // center of circle
    for (i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
    int i;
    int lineAmount = 100; //# of triangles used to draw circle

    //GLfloat radius = 0.8f; //radius
    GLfloat twicePi = 2.0f * PI;

    glBegin(GL_LINE_LOOP);
    for (i = 0; i <= lineAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / lineAmount)),
            y + (radius * sin(i * twicePi / lineAmount))
        );
    }
    glEnd();
}
void DrawCurve(float cx, float cy, float r, int num_segments, float arc_length)
{//GL_LINE_STRIP
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = arc_length * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();

}
void Draweys(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle

        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}
static void play(void)
{
    glutPostRedisplay();
}


static void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON) {

        if (state == GLUT_UP) {
            story -= 1;

        }
    }


    if (button == GLUT_RIGHT_BUTTON) {

        if (state == GLUT_UP) {
            story += 1;
        }
    }
}

void Wolf() {


    glColor4f(0.3f, 0.3f, 0.3f, 1);
    drawFilledCircle(-0.45, 0.22, 0.1);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.41, 0.24, 0.023);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.49, 0.24, 0.023);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(-0.49, 0.24, 0.02);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(-0.41, 0.24, 0.02);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.49, 0.24, 0.011);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.41, 0.24, 0.011);

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.47f, 0.2f);
    glVertex2f(-0.45f, 0.22f);
    glVertex2f(-0.43f, 0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(-0.51f, 0.3f);
    glVertex2f(-0.48f, 0.36f);
    glVertex2f(-0.46f, 0.31f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(-0.43f, 0.31f);
    glVertex2f(-0.41f, 0.36f);
    glVertex2f(-0.39f, 0.3f);
    glEnd();


    glPointSize(1.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.49f, 0.16f);
    glVertex2f(-0.47f, 0.18f);
    glVertex2f(-0.45f, 0.16f);
    glVertex2f(-0.43f, 0.18f);
    glVertex2f(-0.41f, 0.16f);
    glEnd();


    glLineWidth(3.0);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.49f, 0.16f);
    glVertex2f(-0.47f, 0.18f);
    glVertex2f(-0.45f, 0.16f);
    glVertex2f(-0.43f, 0.18f);
    glVertex2f(-0.41f, 0.16f);
    glEnd();
}




void homeTect() {

    glBindTexture(GL_TEXTURE_2D, myTexture1);
    glEnable(GL_TEXTURE_2D);


    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.135); glVertex3f(0.24, 0.17, 0.5);
    glTexCoord2f(1.0, 0.135); glVertex3f(0.54, 0.17, 0.5);
    glTexCoord2f(1.0, 0.99); glVertex3f(0.54, 0.37, 0.5);
    glTexCoord2f(0.0, 0.99); glVertex3f(0.24, 0.37, 0.5);
    // //.... continue the other vertices and texCoord
    glEnd();

    glDisable(GL_TEXTURE_2D);

}
//////////////////////////////////////////////////////////////////////////////////////////////////
void homeTect2() {
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, myTexture2);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.135); glVertex3f(0, -0.3, -1.0);
    glTexCoord2f(1.0, 0.135); glVertex3f(1, -0.3, -1.0);
    glTexCoord2f(1.0, 0.99); glVertex3f(1, 0.6, -1.0);
    glTexCoord2f(0.0, 0.99); glVertex3f(0, 0.6, -1.0);
    // //.... continue the other vertices and texCoord
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////



void forTxtwin() { //winning screen
    //To write on the screen
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-1.2f, 0.95f);
    const char* text1 = "We win! Thank you for helping me ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void Arrow() {


    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.7f, 0.1f);
    glVertex2f(-0.1f, 0.1f);
    glVertex2f(0.1f, 0.1f);
    glVertex2f(0.1f, -0.1f);
    glVertex2f(-0.1f, -0.1f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.7f, 0.1f);
    glVertex2f(0.1f, 0.2f);
    glVertex2f(0.3f, 0.0f);
    glVertex2f(0.1f, -0.2f);
    glEnd();



}

void reshapeFun(GLint newWidth, GLint newHight)
{
    glViewport(0, 0, newWidth, newHight);
    win_width = newWidth;
    win_hight = newHight;
}

void Wall() {

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.2f, 0.4f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.1f, 0.6f);
    glVertex2f(0.2f, 0.4f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.4f, 0.4f);
    glVertex2f(-0.2f, 0.4f);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f(-0.4f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.4f, 0.4f);
    glVertex2f(-0.3f, 0.6f);
    glVertex2f(-0.2f, 0.4f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.8f, 0.4f);
    glVertex2f(-0.6f, 0.4f);
    glVertex2f(-0.6f, 0.0f);
    glVertex2f(-0.8f, 0.0f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.8f, 0.4f);
    glVertex2f(-0.7f, 0.6f);
    glVertex2f(-0.6f, 0.4f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(0.0f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.8f, 0.3f, 0.0f);
    glVertex2f(-0.6f, 0.3f);
    glVertex2f(-0.4f, 0.3f);
    glVertex2f(-0.4f, 0.2f);
    glVertex2f(-0.6f, 0.2f);
    glEnd();




}

void Red()
{
    glPointSize(6.0f);                     //apples
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.1f, 0.3f);
    glEnd();


    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.14f, 0.35f);
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, 0.35f);
    glEnd();




    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.03f, 0.36f);
    glEnd();


    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(0.016f, 0.31f);
    glEnd();

    glPointSize(6.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex2f(-0.22f, 0.34f);
    glEnd();

}

//moring
void cloud1()
{
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.1, 0.1, 0.137);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.1, 0.1, 0.137);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.3, 0.1, 0.137);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.2, 0.2, 0.137);


    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.0, 0.2, 0.137);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.3, 0.1, 0.137);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.19, 0.2, 0.137);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.1, 0.1, 0.129);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.1, 0.1, 0.129);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.3, 0.1, 0.129);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.2, 0.2, 0.129);


    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(0.0, 0.2, 0.129);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.3, 0.1, 0.129);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.19, 0.2, 0.129);

}

void forTxt11() {
    //To write on the screen
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-0.099f, 0.5f);
    const char* text1 = "Hi my name is layla ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
///////////////////for sence1///////////////////////////
void forTxt22() {
    //To write on the screen
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-0.1f, 0.4f);
    const char* text1 = "and I’m on my way";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void forTxt33() {
    //To write on the screen
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(-0.2f, 0.3f);
    const char* text1 = "to my grandma house !";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
//////////////////////for sence2////////////////////////
void brown1() {

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.3f, 0.1f);
    glVertex2f(-0.37f, 0.11f);
    glVertex2f(-0.37f, 0.0f);
    glEnd();


}

void Aleaf1() {
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.39f, 0.07f);
    glEnd();


}

void Apple1() {

    glDisable(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.35, 0.0, 0.06);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.4, 0.0, 0.06);


}
void init1()
{
    glClearColor(0.8f, 0.9f, 0.7f, 0.0f);
    glMatrixMode(GL_PROJECTION);
}

void MyMainObj1()
{
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.6f, -0.45f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(-0.2f, -0.65f);
    glVertex2f(0.0f, -0.65f);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(0.35f, -0.35f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.15f, 0.05f);

    glEnd();


    glBegin(GL_QUADS);


    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.25f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();



    glColor3f(1.0f, 0.9f, 0.9f);
    drawFilledCircle(0, 0.29, 0.15);




    glBegin(GL_LINE_STRIP);
    glColor3f(0.9f, 0.4f, 0.4f);
    glVertex2f(0.0f, 0.21f);
    glVertex2f(0.01f, 0.18f);
    glVertex2f(0.04f, 0.21f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.05f, 0.51f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.0f, 0.32f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.02f, 0.49f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.14f, 0.21f);
    glVertex2f(0.25f, 0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.1f, 0.15f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.25f, 0.3f);


    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.1f, 0.14f);


    glEnd();


    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.038);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.038);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.035);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.035);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.02);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.02);

    void forTxt();
    {

        glLineWidth(2.4f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.3f, 0.4f);
        glEnd();


        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.4f, 0.25f);
        glEnd();

        // drawing the filled circle
        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledCircle(0.4, 0.4, .20);

        // drawing the border around the circle
        glLineWidth(2.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawHollowCircle(0.4, 0.4, .20);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.3f, 0.4f);
        glVertex2f(0.44f, 0.27f);
        glEnd();



    }
}

void Basket1() {


    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.3f, 0.2f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.5f, -0.3f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.1f, -0.5f);
    glEnd();
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(0.6f, 0.5f, 0.4f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.5f, -0.49f);
    glEnd();
    glLineWidth(5.0);
    glBegin(GL_LINES);
    glColor3f(0.6f, 0.5f, 0.4f);
    glVertex2f(0.5f, -0.3f);
    glVertex2f(0.1f, -0.49f);
    glEnd();
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(0.5f, 0.3f, 0.2f);
    glVertex2f(0.1f, -0.3f);
    glVertex2f(0.2f, -0.2f);
    glVertex2f(0.4f, -0.2f);
    glVertex2f(0.5f, -0.3f);
    glBegin(GL_LINE_STRIP);
    glEnd();



}
//////////////////////////////////////////////
///////////for SENCE4///////////////////

void init2()
{
    glClearColor(0.7f, 0.8f, 0.9f, 0.0f);
    glMatrixMode(GL_PROJECTION);
}

void brown2() {

    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.3f, 0.1f);
    glVertex2f(-0.37f, 0.11f);
    glVertex2f(-0.37f, 0.0f);
    glEnd();


}

void Aleaf2() {
    glPointSize(8.0f);                      //         
    glBegin(GL_POINTS);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.39f, 0.07f);
    glEnd();


}

void Apple2() {
    glDisable(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);                   //      
    drawFilledCircle(-0.35, 0.0, 0.06);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.4, 0.0, 0.06);


}

void MyMainObj2()
{
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.6f, -0.45f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(-0.2f, -0.65f);
    glVertex2f(0.0f, -0.65f);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(0.35f, -0.35f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.15f, 0.05f);

    glEnd();


    glBegin(GL_QUADS);


    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.25f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();



    glColor3f(1.0f, 0.9f, 0.9f);
    drawFilledCircle(0, 0.29, 0.15);




    glBegin(GL_LINE_STRIP);
    glColor3f(0.9f, 0.4f, 0.4f);
    glVertex2f(0.0f, 0.21f);
    glVertex2f(0.01f, 0.18f);
    glVertex2f(0.04f, 0.21f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.05f, 0.51f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.0f, 0.32f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.02f, 0.49f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.14f, 0.21f);
    glVertex2f(0.25f, 0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.1f, 0.15f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.25f, 0.3f);


    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.1f, 0.14f);


    glEnd();


    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.038);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.038);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.035);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.035);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.02);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.02);

    void forTxt2();
    {

        glLineWidth(2.4f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.3f, 0.4f);
        glEnd();


        glLineWidth(2.5f);
        glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.4f, 0.25f);
        glEnd();

        // drawing the filled circle
        glColor3f(1.0f, 1.0f, 1.0f);
        drawFilledCircle(0.4, 0.4, .20);

        // drawing the border around the circle
        glLineWidth(2.0f);
        glColor3f(0.0f, 0.0f, 0.0f);
        drawHollowCircle(0.4, 0.4, .20);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.2f, 0.2f);
        glVertex2f(0.3f, 0.4f);
        glVertex2f(0.44f, 0.27f);
        glEnd();

    }
}

void stares() {

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.9f, 0.5f);
    glVertex2f(-0.69f, 0.05f);
    glVertex2f(-0.77f, 0.05f);
    glVertex2f(-0.73f, 0.0f);         //1
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.9f, 0.5f);
    glVertex2f(-0.69f, 0.05f);
    glVertex2f(-0.77f, 0.05f);
    glVertex2f(-0.73f, 0.1f);
    glEnd();



}


////////////////////////////////
void sun() {
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-1.0, 0.3, 0.137);
    glColor3f(1.0f, 1.0f, 0.5f);
    drawFilledCircle(-1.0, 0.3, 0.133);
}
void cloud2() {

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.90, -0.1, 0.107);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.80, -0.2, 0.107);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.95, -0.2, 0.107);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-1.0, -0.2, 0.107);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.90, -0.1, 0.1);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.80, -0.2, 0.1);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-0.95, -0.2, 0.1);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(-1.0, -0.2, 0.1);
}
void ground()
{

    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.90, -0.7, 0.71);

    glColor3f(0.0f, 0.7f, 0.4f);
    drawFilledCircle(-0.90, -0.7, 0.7);
    ////////
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.8, -0.7, 0.71);

    glColor3f(0.0f, 0.7f, 0.4f);
    drawFilledCircle(0.8, -0.7, 0.7);
    ////////
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(0.5, -0.8, 0.61);


    glColor3f(0.0f, 0.8f, 0.3f);
    drawFilledCircle(0.5, -0.8, 0.6);

    ////////
    glColor3f(0.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.4, -0.8, 0.61);


    glColor3f(0.0f, 0.8f, 0.3f);
    drawFilledCircle(-0.4, -0.8, 0.6);
}
//scond background

void Hline()
{
    glColor3f(0.5f, 0.2f, 0.0f);
    // glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.7f); // Define the starting point of the line
    glVertex2f(1.0f, -0.7f);  // Define the ending point of the line
    glEnd();

    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.5f); // Define the starting point of the line
    glVertex2f(1.0f, -0.5f);  // Define the ending point of the line
    glEnd();

    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.9f); // Define the starting point of the line
    glVertex2f(1.0f, -0.9f);  // Define the ending point of the line
    glEnd();
}
void Hlinewhite()
{
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.7f); // Define the starting point of the line
    glVertex2f(1.0f, -0.7f);  // Define the ending point of the line
    glEnd();

    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.5f); // Define the starting point of the line
    glVertex2f(1.0f, -0.5f);  // Define the ending point of the line
    glEnd();

    glBegin(GL_LINES); // Begin drawing lines
    glVertex2f(-1.0f, -0.9f); // Define the starting point of the line
    glVertex2f(1.0f, -0.9f);  // Define the ending point of the line
    glEnd();
}
void Vline()
{
    glColor3f(0.5f, 0.2f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.5f);
    glVertex2f(0.0f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.7f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.7f, -0.5f);
    glVertex2f(-0.7f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.7f);
    glVertex2f(0.0f, -0.9f);
    glEnd();
}
void Vlinewhite()
{
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.5f);
    glVertex2f(0.0f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.5f);
    glVertex2f(0.7f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.7f, -0.5f);
    glVertex2f(-0.7f, -0.3f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.5f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, -0.7f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.7f);
    glVertex2f(0.0f, -0.9f);
    glEnd();
}
void flower()
{
    glColor4f(0.0f, 0.0f, 1.0f, 0.3);
    drawFilledCircle(-0.90, -0.10, 0.04);
    glColor4f(0.0f, 0.0f, 1.0f, 0.3);
    drawFilledCircle(-0.95, -0.15, 0.04);
    glColor4f(0.0f, 0.0f, 1.0f, 0.3);
    drawFilledCircle(-0.85, -0.15, 0.04);
    glColor4f(0.0f, 0.0f, 1.0f, 0.3);
    drawFilledCircle(-0.90, -0.2, 0.04);
    glColor4f(1.0f, 1.0f, 0.0f, 0.7);
    drawFilledCircle(-0.90, -0.15, 0.03);
}
//socnd background
void moon()
{

    glColor4f(1.0f, 1.0f, 1.0f, 0.3);
    drawFilledCircle(-0.30, -0.60, 1);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3);
    drawFilledCircle(-0.30, -0.60, 0.9);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3);
    drawFilledCircle(-0.30, -0.60, 0.8);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3);
    drawFilledCircle(-0.30, -0.60, 0.7);

    glColor4f(1.0f, 1.0f, 1.0f, 0.3);
    drawFilledCircle(-0.30, -0.60, 0.9);
}
void purbleBackground()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.9f, 0.5f, 1.0f);
    glVertex2f(1, -0.5);
    glVertex2f(0.0, -0.5);
    glVertex2f(-1, -0.5);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glVertex2f(0.0, 1);

    glEnd();

}
void pinkBackground()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.9f, 0.8f, 0.0f);
    glVertex2f(1, -0.5);
    glVertex2f(0.0, -0.5);
    glVertex2f(-1, -0.5);
    glColor3f(0.9f, 0.7f, 0.6f);
    glVertex2f(1, 1);
    glVertex2f(-1, 1);
    glVertex2f(0.0, 1);

    glEnd();

}
void tree2()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, -0.3f);
    glVertex2f(0.05f, -0.3f);
    glVertex2f(0.05f, 0.2f);
    glVertex2f(-0.05f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Green color for branches
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.6f);
    glVertex2f(0.3f, 0.2f);
    glVertex2f(-0.3f, 0.2f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Green color for branches
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.7f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(-0.3f, 0.4f);
    glEnd();
}
void MyExtra()

{
    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(0.2f, 0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.2f, 0.2f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.2f, 0.2f);
    glEnd();

    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.1, -0.3);  // Top-left
    glVertex2f(-0.0, -0.3);   // Top-right
    glVertex2f(-0.0, -0.9);   // Bottom-right
    glVertex2f(-0.1, -1.0);  // Bottom-left
    glEnd();




    glColor3f(0.2, 0.2, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.3);  // Top-left
    glVertex2f(-0.4, -0.3);   // Top-right
    glVertex2f(-0.4, -0.9);   // Bottom-right
    glVertex2f(-0.5, -1.0);  // Bottom-left
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.3f, 0.4f);
    glVertex2f(0.2f, -0.2f);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.2f, -0.3f);
    glVertex2f(0.3f, 0.4f);
    glVertex2f(0.2f, 0.2f);
    glEnd();
}

void draw() {
    glColor3f(0.2, 0.2f, 0.2f);
    drawFilledCircle(0.0, 0.0, 0.3);

    glColor3f(0.2, 0.2f, 0.2f);
    drawFilledCircle(-0.2, -0.5, 0.3);
    glColor3f(0.2, 0.2f, 0.2f);
    drawFilledCircle(-0.1, -0.5, 0.3);
    glColor3f(0.2, 0.2f, 0.2f);
    drawFilledCircle(-0.4, -0.5, 0.3);

    glColor3f(1.0f, 0.0f, 0.0f);
    Draweys(-0.1, 0.1, 0.05, 25);

    glColor3f(0.0f, 0.0f, 0.0f);
    Draweys(-0.1, 0.1, 0.02, 25);


    glColor3f(1.0f, 0.0f, 0.0f);
    Draweys(0.1, 0.1, 0.05, 25);


    glColor3f(0.0f, 0.0f, 0.0f);
    Draweys(0.1, 0.1, 0.02, 25);

    glColor3f(1.0, 1.0, 1.0f);
    DrawCurve(0.0, 0.0, 0.20, 20, -2.2);


    glColor3f(1.0f, 1.0f, 1.0f);
    DrawCurve(0.01, 0.020, 0.04, 20, -3.3);

    glColor3f(0.2f, 0.2f, 0.2f);
    DrawCurve(0.08, -0.1, 0.06, 25, -2.5);


    glColor3f(0.2f, 0.2f, 0.2f);
    DrawCurve(-0.0, -1.0, 0.1, 25, 4.9);

    glColor3f(0.2f, 0.2f, 0.2f);
    DrawCurve(-0.4, -1.0, 0.1, 25, 4.9);
    glColor3f(0.2f, 0.2f, 0.2f);
    DrawCurve(-0.3, -1.0, 0.1, 25, 4.9);

    glColor3f(0.2f, 0.2f, 0.2f);
    DrawCurve(-0.6, -0.2, -0.3, 25, 1.8);

}

void tree4()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, -0.3f);
    glVertex2f(0.05f, -0.3f);
    glVertex2f(0.05f, 0.0f);
    glVertex2f(-0.05f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Green color for branches
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Green color for branches
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.4f);
    glVertex2f(0.2f, 0.1f);
    glVertex2f(-0.2f, 0.1f);
    glEnd();

}

void stars()
{
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.7f, 0.8f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.9f, 0.9f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.7f, 0.8f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.8f, 0.6f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.5f, 0.5f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.5f, 0.8f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.4f, 1.0f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.2f, 0.4f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.0f, 0.8f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.1f, 0.4f);
    glEnd(); // End drawing points

    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.3f, 0.3f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.2f, 0.7f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.5f, 0.9f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-0.6f, 0.6f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.5f, 0.9f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.9f, 0.9f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.7f, 0.4f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-1.0f, 0.9f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(-1.0f, 0.8f);
    glEnd(); // End drawing points
    glPointSize(3);
    glBegin(GL_POINTS);
    glColor4f(1.0f, 1.0f, 1.0f, 0.4);
    glVertex2f(0.4f, 0.9f);
    glEnd(); // End drawing points
}
void la1()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(1, -0.1);
    glVertex2f(0.0, -0.1);
    glVertex2f(-1, -0.1);
    glVertex2f(1, -0.8);
    glVertex2f(0.0, -0.8);
    glVertex2f(-1, -0.8);
    glEnd();
}
void lo1()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex2f(1, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(-1, 0.0);
    glVertex2f(1, -0.7);
    glVertex2f(0.0, -0.7);
    glVertex2f(-1, -0.7);
    glEnd();
}


//3rd ground

void montain()
{

    glColor4f(0.6f, 0.3f, 0.1f, 1); // Green color for branches
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, 0.3f);
    glVertex2f(0.2f, 0.0f);
    glVertex2f(-0.2f, 0.0f);
    glEnd();
}
void treebooble()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(-0.06f, -0.3f);
    glVertex2f(0.06f, -0.3f);
    glVertex2f(0.06f, 0.2f);
    glVertex2f(-0.06f, 0.2f);
    glEnd();


    glColor3f(0.5f, 0.2f, 0.1f); // Brown color for the trunk
    glBegin(GL_POLYGON);
    glVertex2f(-0.05f, -0.30f);
    glVertex2f(0.05f, -0.30f);
    glVertex2f(0.05f, 0.20f);
    glVertex2f(-0.05f, 0.20f);
    glEnd();

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0, 0.2, 0.17);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0, 0.4, 0.17);

    // drawing the filled circle
    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.2, 0.3, 0.17);
    // drawing the filled circle
    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.2, 0.3, 0.17);
    // drawing the filled circle
    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.2, 0.4, 0.17);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.2, 0.4, 0.17);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.0, 0.5, 0.17);


    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.0, 0.5, 0.20);

    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(0, 0.2, 0.16);


    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(0, 0.4, 0.16);

    // drawing the filled circle
    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(0.2, 0.3, 0.16);

    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(-0.2, 0.3, 0.16);

    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(0.2, 0.4, 0.16);

    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(-0.2, 0.4, 0.16);

    glColor4f(0.3f, 0.6f, 0.3f, 1);
    drawFilledCircle(0.0, 0.5, 0.19);

}
void Vline1()
{
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0.2f, -0.1f);
    glVertex2f(0.2f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0.5f, -0.1f);
    glVertex2f(0.5f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0.7f, -0.1f);
    glVertex2f(0.7f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(0.9f, -0.1f);
    glVertex2f(0.9f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-0.2f, -0.1f);
    glVertex2f(-0.2f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, -0.1f);
    glVertex2f(-0.5f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-0.7f, -0.1f);
    glVertex2f(-0.7f, -0.3f);
    glEnd();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
    glVertex2f(-0.9f, -0.1f);
    glVertex2f(-0.9f, -0.3f);
    glEnd();

}

void lineoo1()
{
    glColor3f(1, 1, 1);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.1f);
    glVertex2f(1.0f, -0.1f);
    glEnd();

    glColor3f(1, 1, 1);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.2f);
    glVertex2f(1.0f, -0.2f);
    glEnd();

}
void orange()
{
    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.0, 0.6, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.0, 0.4, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.3, 0.4, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(-0.3, 0.4, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(-0.1, 0.2, 0.05);
    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.1, 0.2, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(-0.8, 0.4, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(-0.7, 0.6, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(-0.7, 0.2, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.8, 0.4, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.7, 0.6, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.7, 0.2, 0.05);

    glColor4f(0.9f, 0.4f, 0.1f, 1);
    drawFilledCircle(0.9, 0.2, 0.05);

}
void la()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.7f, 0.4f, 0.2f);
    glVertex2f(1, -0.1);
    glVertex2f(0.0, -0.1);
    glVertex2f(-1, -0.1);
    glVertex2f(1, -0.8);
    glVertex2f(0.0, -0.8);
    glVertex2f(-1, -0.8);
    glEnd();
}
void lo()
{
    glBegin(GL_QUAD_STRIP);
    glColor3f(0.5f, 0.2f, 0.0f);
    glVertex2f(1, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(-1, 0.0);
    glVertex2f(1, -0.7);
    glVertex2f(0.0, -0.7);
    glVertex2f(-1, -0.7);

    glEnd();

}
void cc() {
    glColor4f(0.5f, 0.2f, 0.0f, 0.3);
    drawFilledCircle(-0.9, -0.9, 0.3);

    glColor4f(0.5f, 0.2f, 0.0f, 0.3);
    drawFilledCircle(0.7, -0.8, 0.3);

    glColor4f(0.5f, 0.2f, 0.0f, 0.3);
    drawFilledCircle(0.2, -0.5, 0.08);

    glColor4f(0.5f, 0.2f, 0.0f, 0.3);
    drawFilledCircle(-0.2, -0.7, 0.06);
}

void obstacle()
{
    glColor3f(0.8f, 0.6f, 0.5f);
    glBegin(GL_QUADS);              //«·«’Ì’
    glVertex2f(0.3f, -0.12f);
    glVertex2f(0.3f, -0.3f);
    glVertex2f(0.5f, -0.3f);
    glVertex2f(0.5f, -0.12f);
    glEnd();


    glColor3f(0.5f, 0.7f, 0.0f);
    glBegin(GL_QUADS);              //—Ã· «·‰» …
    glVertex2f(0.38f, -0.12f);
    glVertex2f(0.38f, 0.02f);
    glVertex2f(0.42f, 0.02f);
    glVertex2f(0.42f, -0.12f);
    glEnd();

    glColor3f(0.8f, 0.6f, 0.5f);
    glBegin(GL_QUADS);               //»«ﬁÌ «·«’Ì’
    glVertex2f(0.25f, -0.17f);
    glVertex2f(0.25f, -0.1f);
    glVertex2f(0.55f, -0.1f);
    glVertex2f(0.55f, -0.17f);
    glEnd();

    //plant




    glPushMatrix();
    glRotatef(-90, 0, 0, 1);
    glTranslatef(-.51, .3, 1);

    glColor3f(0.7f, 0.1f, 0.0f);
    DrawCurve(.42, 0.1, .14, 32, -2.7);
    glColor3f(0.7f, 0.1f, 0.0f);
    DrawCurve(.42, 0.1, .14, 32, 2.7);

    glPopMatrix();

    DrawCurve(.4, 0.07, .11, 32, -3.3);

    //plant mouth



    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.47f, 0.22f);
    glVertex2f(0.399f, 0.1f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.5f, 0.19f);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(0.33f, 0.22f);
    glVertex2f(0.399f, 0.1f);
    glVertex2f(0.4f, 0.0f);
    glVertex2f(0.3f, 0.19f);
    glEnd();

    //--------left teeth---------
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.34f, 0.2f);
    glVertex2f(0.35f, 0.22f);
    glVertex2f(0.33f, 0.22f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.36f, 0.16f);
    glVertex2f(0.37f, 0.18);
    glVertex2f(0.35f, 0.18f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.38f, 0.12f);
    glVertex2f(0.39f, 0.14f);
    glVertex2f(0.37f, 0.14f);
    glEnd();

    //-------Right teeth-------

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.46f, 0.2f);
    glVertex2f(0.47f, 0.22f);
    glVertex2f(0.45f, 0.22f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.44f, 0.16f);
    glVertex2f(0.45f, 0.18);
    glVertex2f(0.43f, 0.18f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.42f, 0.12f);
    glVertex2f(0.43f, 0.14f);
    glVertex2f(0.41f, 0.14f);
    glEnd();


    // the circles in the plant

    glColor3f(1.0f, 1.0f, 1.0f);
    drawFilledCircle(.29, .09, 0.03);

    drawFilledCircle(.35, .01, 0.03);

    drawFilledCircle(.49, .02, 0.03);

    drawFilledCircle(.45, .1, 0.03);
}
void MyMainObj()
{
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f(-0.6f, -0.45f);
    glVertex2f(-0.4f, -0.6f);
    glVertex2f(-0.2f, -0.65f);
    glVertex2f(0.0f, -0.65f);
    glVertex2f(0.2f, -0.6f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(0.35f, -0.35f);
    glVertex2f(0.15f, -0.15f);
    glVertex2f(0.05f, 0.05f);
    glVertex2f(-0.15f, 0.05f);

    glEnd();


    glBegin(GL_QUADS);


    glColor3f(0.7f, 0.0f, 0.0f);
    glVertex2f(-0.4f, 0.25f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.0f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.03f, 0.0f);
    glVertex2f(0.25f, 0.3f);
    glVertex2f(0.1f, 0.6f);

    glEnd();



    glColor3f(1.0f, 0.9f, 0.9f);
    drawFilledCircle(0, 0.29, 0.15);




    glBegin(GL_LINE_STRIP);
    glColor3f(0.9f, 0.4f, 0.4f);
    glVertex2f(0.0f, 0.21f);
    glVertex2f(0.01f, 0.18f);
    glVertex2f(0.04f, 0.21f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.05f, 0.51f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.0f, 0.32f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.02f, 0.49f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.15f, 0.45f);
    glVertex2f(0.1f, 0.4f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.14f, 0.21f);
    glVertex2f(0.25f, 0.3f);
    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(0.1f, 0.15f);
    glVertex2f(0.15f, 0.3f);
    glVertex2f(0.25f, 0.3f);


    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.7f, 0.4f, 0.0f);
    glVertex2f(-0.2f, 0.3f);
    glVertex2f(-0.1f, 0.3f);
    glVertex2f(-0.1f, 0.14f);


    glEnd();

    /* glColor3f(1.0f, 0.9f, 0.9f);
     drawFilledCircle(0, 0.29, 0.15);*/

    glColor4f(1.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.01, 0.18, 0.04);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.06);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.06);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.053);

    glColor4f(1.0f, 1.0f, 1.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.053);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(0.1, 0.3, 0.03);

    glColor4f(0.0f, 0.0f, 0.0f, 1);
    drawFilledCircle(-0.01, 0.3, 0.03);
}
//-----The Apple----

void Apple() {

    glPushMatrix();
    glTranslatef(-.1, -.26, 0);

    //brown
    glLineWidth(4.0);
    glBegin(GL_LINES);
    glColor3f(0.5f, 0.3f, 0.1f);
    glVertex2f(-0.37f, 0.11f);
    glVertex2f(-0.37f, 0.0f);
    glEnd();


    //apple
    glDisable(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f); //«· ›«Õ
    drawFilledCircle(-0.35, 0.0, 0.06);
    glColor3f(1.0f, 0.0f, 0.0f);
    drawFilledCircle(-0.4, 0.0, 0.06);

    //leaf
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glColor3f(0.1f, 0.5f, 0.2f);
    glVertex2f(-0.39f, 0.07f);
    glEnd();
    glPopMatrix();


}
void MyMainObjBack()
{
    glColor3f(0.7f, 0.0f, 0.1f);
    //arm
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.25f, -0.70f);
    glVertex2f(0.3f, -0.80f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.25f, -0.70f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.3f, -0.80f);
    glEnd();

    //fingers 
    glColor3f(1.0f, 0.9f, 0.8f);

    glBegin(GL_POINTS);

    glVertex2f(0.26f, -0.70f);
    glVertex2f(0.269f, -0.72f);
    glVertex2f(0.28f, -0.75f);


    glEnd();
    glPointSize(5.0);

    //body
    glColor3f(0.7f, 0.0f, 0.1f);

    glBegin(GL_TRIANGLES);
    glVertex2f(0.0f, -0.4f);
    glVertex2f(-0.2f, -1.0f);
    glVertex2f(0.2f, -1.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0f, -0.4f);
    glVertex2f(-0.2f, -1.0f);
    glVertex2f(0.2f, -1.0f);
    glEnd();


    //head
    glColor3f(0.7f, 0.0f, 0.1f);

    glBegin(GL_QUADS);
    glVertex2f(0.0f, -0.3f);
    glVertex2f(-0.4f, -0.50f);
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.4f, -0.50f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.3f);
    glVertex2f(-0.4f, -0.50f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-0.4f, -0.50f);
    glVertex2f(0.0f, -0.9f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.9f);
    glVertex2f(0.4f, -0.50f);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(0.0f, -0.3f);
    glVertex2f(0.4f, -0.50f);
    glEnd();
}

void GameOver(int num) {

    float xx1[2] = { -0.3,3.4 };
    float xx2[2] = { 0.7,4.5 };

    float ycor = 0.5;
    float WolY = 1.0;
    switch (num) {

    case(1):

        if (obsX >= xx1[1] and obsX <= xx2[1]) { //last obstecle
            if (obsY <= ycor) {
                sence = 6;
            }

        }
        break;

    case(2):

        if (obsX >= xx1[0] and obsX <= xx2[0]) {
            if (obsY <= ycor) { //first obstelce
                
                sence = 6;
            }

        }
        break;

    case(3):

        if (obsX >= 2.3 and obsX <= 3.3) {//second obstcle
            if (obsY <= ycor) {  
                sence = 6;
            }

        }
    case(4):

        if (obsX >= 3.6 and obsX <= 4.7) {
            if (obsY <= WolY) {  
                sence = 6;      //wolf obstlce
            }

        }
        break;


    }


}




void AppleCaount() {

    if (gx > applesPlace[i] and gy < 0.1) {  //collect the apple and translate it


        glPushMatrix();
        glTranslatef(.8, 0.0, 0.0);
        Apple();
        glPopMatrix();


        appleSc += 1;
        cout << "Your apple score is" << appleSc << endl;

        i++;
        appcount += 0.3;
    }
    else if (gx != applesPlace[i]) {

        if (appcount <= 1.16) {

            glPushMatrix();
            glTranslatef(appcount, 0.0, 0.0);
            Apple();
            glPopMatrix();
        }

        else if (appcount > 1.16) {

            glPushMatrix();
            glTranslatef(10, 0.0, 0.0);
            Apple();
            glPopMatrix();

        };


    };


}
void squareForTxt()
{
    //instruction message 
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(0.0f, 0.9f);
    glVertex2f(0.9f, 0.9f);
    glVertex2f(0.9f, -0.3f);
    glVertex2f(0.0f, -0.3f);
    glEnd();

    glLineWidth(2.4f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(0.01f, 0.08f);
    glEnd();


    glLineWidth(2.5f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.1f, 0.0f);
    glVertex2f(-0.01f, 0.01f);
    glEnd();




}
/////////// instructions texts////////////
void forTxtI1() {
    //To write on the screen
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(0.05f, 0.8f);
    const char* text1 = "instructions: ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void forTxtI2() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);
    glRasterPos2f(0.05f, 0.67f);
    const char* text1 = "To go up click up";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void forTxtI3() {
    //To write on the screen
    glColor3f(1.0, 0.2, 0.2);
    glRasterPos2f(0.05f, 0.44f);
    const char* text1 = "To go right click right ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void forTxtI4() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);
    glRasterPos2f(0.05f, 0.2f);
    const char* text1 = "To go left click left ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }

}

void forTxtI5() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);
    glRasterPos2f(0.05f, 0.58f);
    const char* text1 = "arrow. ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
void forTxtI6() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);

    glRasterPos2f(0.05f, 0.34f);
    const char* text1 = " arrow. ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
void forTxtI7() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);

    glRasterPos2f(0.05f, 0.1f);
    const char* text1 = " arrow. ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
void forTxtI8() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);

    glRasterPos2f(0.05f, -0.1f);
    const char* text1 = "To Start playing ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}
void forTxtI9() {
    //To write on the screen
    glColor3f(1, 0.2, 0.2);

    glRasterPos2f(0.05f, -0.2f);
    const char* text1 = "Press Space  ";
    while (*text1) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
        text1++;
    }
}

void BackGround(int color) {


    switch (color) {
    case 1:
        glColor3f(0.8f, 0.9f, 0.7f);

        break;
    case 2:
        glColor3f(0.7f, 0.8f, 0.9f);
        break;
    case 3:
        glColor3f(0.5f, 0.9f, 0.9f);
        break;
    }

    glBegin(GL_QUADS);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(1.0f, 1.0f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();
}
void granny() {
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, myTexture3);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 1.0);
    // //.... continue the other vertices and texCoord

    //forTxtwin();
    glEnd();
    //forTxtwin();
    glDisable(GL_TEXTURE_2D);
    //forTxtwin();
}

void lose() {

    glBindTexture(GL_TEXTURE_2D, myTexture4);
    glEnable(GL_TEXTURE_2D);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-0.5, -0.5, 1.0);
    glTexCoord2f(1.0, 0.0); glVertex3f(0.5, -0.5, 1.0);
    glTexCoord2f(1.0, 1.0); glVertex3f(0.5, 0.5, 1.0);
    glTexCoord2f(0.0, 1.0); glVertex3f(-0.5, 0.5, 1.0);
    // //.... continue the other vertices and texCoord

    //forTxtwin();
    glEnd();
    //forTxtwin();
    glDisable(GL_TEXTURE_2D);
    //forTxtwin();
}



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);


    ///for story///:
    if (flag == true) {


        /////first sence in story
        if (story == 0) {
            glClear(GL_COLOR_BUFFER_BIT);

            glEnable(GL_BLEND);
            BackGround(1);

            glPushMatrix();
            glTranslatef(-0.4, -0.35, 0.0);
            MyMainObj();
            glPopMatrix();
            glPushMatrix();
            glScalef(1.5, 1.5, 1.0);
            glTranslatef(0.2, 0.1, 0.0);
            cloud1();
            glPopMatrix();
            forTxt11();
            forTxt22();
            forTxt33();
            glDisable(GL_BLEND);

        }
        /////second sence in story
        else if (story == 1) {
            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);
            BackGround(1);

            glLoadIdentity();
            glPushMatrix();
            glTranslatef(-0.5, 0.9, 0.0);      //3
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.2, 0.8, 0.0);      //4
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, 0.8, 0.0);      //5
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.8, 0.4, 0.0);      //6
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, 0.1, 0.0);      //7
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(1.0, -0.3, 0.0);      //8
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-0.5, -0.3, 0.0);      //9
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-0.3, -0.8, 0.0);      //10
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0, -0.3, 0.0);      //11
            MyMainObj();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, -0.9, 0.0);      //12
            brown1();
            Apple1();
            Aleaf1();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0, -0.3, 0.0);
            Basket1();
            glPopMatrix();
            //To write on the screen
            glRasterPos2f(-1, 0.6f);
            const char* text4 = "The story starts with my grandma being sick ";

            while (*text4) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text4);
                text4++;
            }
            glRasterPos2f(-1, 0.5f);
            const char* text5 = "so my mom made her some food so i can give it to";
            while (*text5) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text5);
                text5++;
            }
            glRasterPos2f(-1, 0.4f);
            const char* text6 = "HER but we ran out of apples ..";
            while (*text6) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text6);
                text6++;
            }
            glDisable(GL_BLEND);

        }


        /////third sence in story

        else if (story == 2) {
            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);


            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            BackGround(2);
            glPushMatrix();
            glTranslatef(-0.5, 0.9, 0.0);      //3
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.2, 0.8, 0.0);      //4
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, 0.8, 0.0);      //5
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, 0.1, 0.0);      //7
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.0, -0.3, 0.0);      //8
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.5, -0.6, 0.0);      //10
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-0.4, -0.35, 0.0);
            MyMainObj2();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(1.2, -0.9, 0.0);      //12
            brown2();
            Apple2();
            Aleaf2();
            glPopMatrix();
            stares();
            glPushMatrix();
            glTranslatef(0.48, -0.38, 0.0);      //2
            stares();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.59, -0.25, 0.0);      //2
            stares();
            glPopMatrix();
            glColor3f(0, 0, 0);
            glRasterPos2f(-.9f, 0.6f);
            const char* text1 = "and to achieve that and get the food  ";
            while (*text1) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text1);
                text1++;
            }

            glColor3f(0, 0, 0);
            glRasterPos2f(-.9f, 0.5f);
            const char* text2 = "to my dear grandma, will you help me ?";
            while (*text2) {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *text2);
                text2++;
            }
            glDisable(GL_BLEND);

        }


        /////forth sence in story

        else if (story == 3) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            BackGround(2);
            glPushMatrix();
            MyMainObjBack();
            glScalef(-0.15, -0.15, 0.0);
            glPopMatrix();

            glPushMatrix();
            glScalef(1.9, 1.8, 0.0);
            cloud1();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.5, 0.25, 0.0);    //tree1
            glScalef(0.25, 0.25, 0.0);
            treebooble();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(-0.4, 0.25, 0.0);    //tree2
            glScalef(0.25, 0.25, 0.0);
            treebooble();
            glPopMatrix();





            glPushMatrix();
            glTranslatef(-0.3, 0.25, 0.0);    //arrow
            glScalef(0.25, 0.25, 0.0);
            Arrow();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(-0.15, 0.25, 0.0);    //tree3
            glScalef(0.25, 0.25, 0.0);
            treebooble();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(0.0, 0.25, 0.0);    //tree4
            glScalef(0.25, 0.25, 0.0);
            treebooble();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.1, 0.25, 0.0);    //tree5
            glScalef(0.25, 0.25, 0.0);
            treebooble();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(0.001, 0.15, 0.0);    //WALL
            glScalef(0.21, 0.2, 0.0);
            Wall();
            glPopMatrix();


            Red();


            glPushMatrix();
            glTranslatef(0.15, 0.25, 0.0);    //arrow
            glScalef(0.25, 0.25, 0.0);
            Arrow();
            glPopMatrix();

            homeTect();

            glPushMatrix();
            glTranslatef(-0.27, 0.12, 0.0);
            glScalef(0.4, 0.4, 0.0);
            Wolf();
            glPopMatrix();

            glDisable(GL_BLEND);

        }
        else if (story == 4) {
            glClear(GL_COLOR_BUFFER_BIT);
            glEnable(GL_BLEND);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            BackGround(3);

            glPushMatrix();
            glTranslatef(-0.4, -0.35, 0.0);
            MyMainObj();
            glPopMatrix();



            squareForTxt();




            forTxtI1();


            forTxtI2();
            forTxtI5();

            forTxtI3();
            forTxtI6();

            forTxtI4();
            forTxtI7();
            forTxtI8();
            forTxtI9();

            glDisable(GL_BLEND);


        }


    }
    ////-----------game begging-------////:
    else {

        if (sence == 0) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            BackGround(3);

            glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            cloud1();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.09, 0.5, 0.0);
            cloud2();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            sun();
            glPopMatrix();

            ground();

            glPushMatrix();
            glTranslatef(0.0, -0.30, 0.0);
            lo();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.24, 0.0);
            la();
            glPopMatrix();
            Hline();
            Vline();
            flower();


            glPushMatrix();
            glTranslatef(-1, -0.1, 0.0);
            glScalef(0.35, 0.35, 1);
            glTranslatef(transValueX, transValueY, 0);
            MyMainObj();
            glPopMatrix();

            AppleCaount();

            glDisable(GL_BLEND);


        }

        else if (sence == 1) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            BackGround(3);


            glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            cloud1();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.4, 0.0, 0.0);
            treebooble();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.4, 0.0, 0.0);
            treebooble();
            glPopMatrix();


            glPushMatrix();
            glTranslatef(-0.8, 0.0, 0.0);
            treebooble();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.8, 0.0, 0.0);
            treebooble();
            glPopMatrix();

            treebooble();

            glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            sun();
            glPopMatrix();

            Vline1();
            lineoo1();
            orange();

            glPushMatrix();
            glTranslatef(0.0, -0.30, 0.0);
            lo();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.24, 0.0);
            la();
            glPopMatrix();
            cc();

            glPushMatrix();
            glTranslatef(-0.4, -0.17, 0.0);
            glScalef(-.5, .5, 1);
            obstacle();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(-1, -0.1, 0.0);
            glScalef(0.35, 0.35, 1);
            glTranslatef(transValueX, transValueY, 0);
            MyMainObj();
            glPopMatrix();

            AppleCaount();

            GameOver(2);

            glDisable(GL_BLEND);


        }

        else if (sence == 2)
        {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);


            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();



            pinkBackground();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(0.0, -0.30, 0.0);
            lo();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.24, 0.0);
            la();
            glPopMatrix();

            Hline();
            Vline();
            stars();
            glPushMatrix();
            glTranslatef(-0.8, -0.3, 0.0);
            glScalef(3, 3, 1);
            montain();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.3, 0.0);
            glScalef(3, 3, 1);
            montain();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.8, -0.3, 0.0);
            glScalef(3, 3, 1);
            montain();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.4, -0.17, 0.0);
            glScalef(-.5, .5, 1);
            obstacle();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.9, -0.17, 0.0);
            glScalef(-.5, .5, 1);
            obstacle();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-1, -0.1, 0.0);
            glScalef(0.35, 0.35, 1);
            glTranslatef(transValueX, transValueY, 0);
            MyMainObj();
            glPopMatrix();

            AppleCaount();

            GameOver(1);
            GameOver(2);

            glDisable(GL_BLEND);

        }

        else if (sence == 3)
        {


            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
            purbleBackground();
            moon();

            glPushMatrix();
            glTranslatef(0.0, -0.30, 0.0);
            lo1();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.24, 0.0);
            la1();
            glPopMatrix();


            stars();

            glPushMatrix();
            glTranslatef(-0.8, 0.0, 0.0);
            tree2();
            glPopMatrix();
            tree2();
            glPushMatrix();
            glTranslatef(0.8, 0.0, 0.0);
            tree2();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.4, 0.0, 0.0);
            tree4();
            glPopMatrix();
            glPushMatrix();
            glTranslatef(-0.4, 0.0, 0.0);
            tree4();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.5, -0.17, 0.0);
            glScalef(-.5, .5, 1);
            obstacle();
            glPopMatrix();

            Vlinewhite();
            Hlinewhite();

            glPushMatrix();
            glScalef(0.24, 0.3, 1);
            glTranslatef(3.4, 0.0, 0.0);
            MyExtra();
            draw();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.4, -0.17, 0.0);
            glScalef(-.5, .5, 1);
            obstacle();
            glPopMatrix();



            glPushMatrix();
            glTranslatef(-1, -0.1, 0.0);
            glScalef(0.35, 0.35, 1);
            glTranslatef(transValueX, transValueY, 0);
            MyMainObj();
            glPopMatrix();

            AppleCaount();


            GameOver(2);

            GameOver(3);
            GameOver(4);

            glDisable(GL_BLEND);

        }
        else if (sence == 4) {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);
                     BackGround(3);

            homeTect2();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            
          
            glPushMatrix();
            glTranslatef(0.09, 0.5, 0.0);
            cloud2();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.5, 0.5, 0.0);
            sun();
            glPopMatrix();
            ////////
            glColor3f(0.0f, 0.0f, 0.0f);
            drawFilledCircle(-0.90, -0.7, 0.71);

            glColor3f(0.0f, 0.7f, 0.4f);
            drawFilledCircle(-0.90, -0.7, 0.7);
            glColor3f(0.0f, 0.0f, 0.0f);
            drawFilledCircle(-0.4, -0.8, 0.61);


            glColor3f(0.0f, 0.8f, 0.3f);
            drawFilledCircle(-0.4, -0.8, 0.6);
            ////////

            glPushMatrix();
            glTranslatef(0.0, -0.30, 0.0);
            lo();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(0.0, -0.24, 0.0);
            la();
            glPopMatrix();
            Hline();
            Vline();
            flower();



            glPushMatrix();
            glTranslatef(-1, -0.1, 0.0);
            glScalef(0.35, 0.35, 1);
            glTranslatef(transValueX, transValueY, 0);
            MyMainObj();
            glPopMatrix();

            AppleCaount();


        }
        /////////unchanged
        else if (sence == 5)
        {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);

            // forTxtwin();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glPushMatrix();
            glScalef(2.0, 2.0, 0.0);
            granny();
            //lose();
            glPopMatrix();
            forTxtwin();




            glDisable(GL_BLEND);



            }


        else if (sence == 6)
        {

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_BLEND);

            
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();

            glPushMatrix();
            glScalef(2.0, 2.0, 0.0);
            
            lose();
            glPopMatrix();
            forTxtwin();




            glDisable(GL_BLEND);



            }

        glEnd();
    }

    glDisable(GL_BLEND);


    glFlush();
    glutSwapBuffers();

}






int main(int argc, char** argv)
{
    glutInit(&argc, argv);                          // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);   //  Specify the display Mode ñ RGB, RGBA or color //  Index, single or double Buffer
    glutInitWindowSize(win_width, win_hight);       // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                 // Position the window's initial top-left corner
    glutCreateWindow("project");    // Create a window with the given title

    init();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glutIdleFunc(play);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutSpecialFunc(special);
    glutKeyboardFunc(key);
    glutMainLoop();                                  // Enter the infinitely event-processing loop
    return 0;

}