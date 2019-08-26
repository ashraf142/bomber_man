/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

 #include <stdlib.h>
#include<Windows.h>
#ifdef APPLE
#include <GLUT/glut.h>

#else
#include <GL/glut.h>
#endif
#include<math.h>

#include<stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/GLAUX.h>
#include <time.h>
#include <string.h>

#define PI 3.1415927

class Bomb
{

    public:

    float x, y;
    clock_t tim;
    bool alrT;
    int ang;
    bool ex;
    GLfloat ccx = 0.0;
    GLfloat ccy = 0.0;
    GLfloat ccangle = 0.0;

    int hit(float gx, float gy)
    {
        float minx = x-1.0;
        float miny = y-1.0;
        float maxx = x+1.0;
        float maxy = y+1.0;

        //printf("minx: %f; maxx: %f\nxx: %f; yy: %f\n\n", minx, maxx, gx, gy);

        if(gx == x && gy > miny && gy < maxy){
            return 1;
        }
        if(gy == y && gx > minx && gx < maxx){
            return 1;
        }
        return 0;
    }
    void rgb(int x, int y, int z)
    {
    glColor3f(x/256.0,y/256.0,z/256.0);
    }
    void vQuad(float x, float y, float z)
    {
      // Draw A variable Quad
            glBegin(GL_QUADS);


                glVertex3f(x,y,z);					    // Top front Of The Quad (right)
                glVertex3f(x,y,1.0f);					// Top back Of The Quad (right)
                glVertex3f(x,-y,1.0f);					// Bottom back Of The Quad (right)
                glVertex3f(x,-y,z);					// Bottom front Of The Quad (right)


                glVertex3f(-x,y,z);					// Top front Of The Quad (left)
                glVertex3f(-x,y,1.0f);					// Top back Of The Quad (left)
                glVertex3f(-x,-y,1.0f);					// Bottom back Of The Quad (left)
                glVertex3f(-x,-y,z);					// Bottom front Of The Quad (left)



                glVertex3f(x,y,z);					    // Right front Of The Quad (top)
                glVertex3f(x,y,1.0f);					    // Right back Of The Quad (top)
                glVertex3f(-x,y,1.0f);				    // Left back Of The Quad (top)
                glVertex3f(-x,y,z);				    // Left front Of The Quad (top)



                glVertex3f(x,-y,z);					// Right front Of The Quad (bottom)
                glVertex3f(x,-y,1.0f);					// Right back Of The Quad (bottom)
                glVertex3f(-x,-y,1.0f);				    // Left back Of The Quad (bottom)
                glVertex3f(-x,-y,z);				    // Left front Of The Quad (bottom)



                glVertex3f(x,y,1.0f);					 // Top Right Of The Quad (Back)
                glVertex3f(-x,y,1.0f);					// Top Left Of The Quad (Back)
                glVertex3f(-x,-y,1.0f);					// Bottom Left Of The Quad (Back)
                glVertex3f(x,-y,1.0f);					// Bottom Right Of The Quad (Back)



                glVertex3f(x,y,z);					    // Top Right Of The Quad (Front)
                glVertex3f(-x,y,z);					// Top Left Of The Quad (Front)
                glVertex3f(-x,-y,z);					// Bottom Left Of The Quad (Front)
                glVertex3f(x,-y,z);					// Bottom Right Of The Quad (Front)


            glEnd();
    }

    void explod(float x, float y)
    {
        glPushMatrix();
        glTranslatef(x-1.0,y-1.0,11.0);
        glRotatef(ang,1.0,0.0,0.0);
        glScalef(0.85,0.1,0.1);
        vQuad(1.0,1.0,2.0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(x-1.0,y-1.0,11.0);
        glRotatef(ang,0.0,1.0,0.0);
        glScalef(0.1,0.85,0.1);
        vQuad(1.0,1.0,2.0);
        glPopMatrix();

        ang += 5.0;
    }

    int drop()
    {
       double fnlT = ((double)(time(NULL) - tim));
        if(fnlT <= 3.0){
                if(fnlT >= 2){
                    alrT = !alrT;
                }
               glPushMatrix();
               glTranslatef(x,y,0.0);

               glPushMatrix();//body
               glTranslatef(-1.0,-1.0,11.2);
               glScalef(0.12,0.12,0.12);

               if(alrT){
                    rgb(255, 4, 12);
                    if(fnlT == 3.0){
                        rgb(244, 97, 2);
                    }
               }else{
                   rgb(23, 41, 55);//rgb(0, 67, 70);
               }
               glutSolidSphere(1,16,16);
               glPopMatrix();//body

               glPopMatrix();

               glPushMatrix();// sh
               glTranslatef(x-1.13,y-1.0,11.0);
               glRotatef(30.0,0.0,1.0,0.0);
               glScalef(0.01,0.01,0.215);
               if(alrT){
                    rgb(255, 4, 12);
                    if(fnlT == 3.0){
                        rgb(244, 97, 2);
                    }
               }else{
                   rgb(118, 98, 70);//rgb(130, 117, 96);
               }
               vQuad(1.0,1.0,2.0);
               glPopMatrix();// sh

               glPushMatrix();
               glTranslatef(x-1.04,y-1.0,11.15);
               glRotatef(30.0,0.0,1.0,0.0);
               glScalef(0.04,0.04,0.1);
               if(alrT){
                    rgb(255, 4, 12);
                    if(fnlT == 3.0){
                        rgb(244, 97, 2);
                    }
               }else{
                   rgb(57, 72, 82);//rgb(55, 67, 70);
               }
               glPushMatrix();
               gluCylinder(gluNewQuadric(), 1.2, 1.2, 2, 16, 16);
               glTranslatef(0.0,0.0,2.0);
               if(alrT){
                    rgb(255, 4, 12);
                    if(fnlT == 3.0){
                        rgb(244, 97, 2);
                    }
               }else{
                   rgb(23, 41, 55);//rgb(0, 67, 70);
               }
               gluDisk(gluNewQuadric(), 0.0, 1.2, 16, 16);
               glPopMatrix();
               glPopMatrix();

               if(fnlT == 2.0){
                    PlaySound("bmb.wav", NULL, SND_FILENAME);
                    //PlaySound("bomb.wav", NULL, SND_FILENAME | SND_ASYNC);
                    //return 3;
                }
               if(fnlT == 3.0){
                        explod(x, y);
                        if(!ex){
                            ex = true;

                            return 2;
                        }
                }

               return 1;
        }

        return 0;
    }

};


static float p1_life = 1.0, p2_life = 1.0;
static Bomb bmb1, bmb2;
static int p1_bomb = 0;
static int p2_bomb = 0;
static float	tx1	=  0.0;
static float	ty1	=  0.0;
static float	tx2	=  2.0;
static float	ty2	=  2.0;

bool alr1 = false;
bool alr2 = false;
double a=0.0,b=0.0,c=15.0;
GLfloat	l_t=0;

// Simple QUAD Draw

void rgb(int x, int y, int z){
    glColor3f(x/256.0,y/256.0,z/256.0);
}

void vQuad(float x, float y, float z)
{
  // Draw A variable Quad
        glBegin(GL_QUADS);


            glVertex3f(x,y,z);					    // Top front Of The Quad (right)
            glVertex3f(x,y,1.0f);					// Top back Of The Quad (right)
            glVertex3f(x,-y,1.0f);					// Bottom back Of The Quad (right)
            glVertex3f(x,-y,z);					// Bottom front Of The Quad (right)


            glVertex3f(-x,y,z);					// Top front Of The Quad (left)
            glVertex3f(-x,y,1.0f);					// Top back Of The Quad (left)
            glVertex3f(-x,-y,1.0f);					// Bottom back Of The Quad (left)
            glVertex3f(-x,-y,z);					// Bottom front Of The Quad (left)



            glVertex3f(x,y,z);					    // Right front Of The Quad (top)
            glVertex3f(x,y,1.0f);					    // Right back Of The Quad (top)
            glVertex3f(-x,y,1.0f);				    // Left back Of The Quad (top)
            glVertex3f(-x,y,z);				    // Left front Of The Quad (top)



            glVertex3f(x,-y,z);					// Right front Of The Quad (bottom)
            glVertex3f(x,-y,1.0f);					// Right back Of The Quad (bottom)
            glVertex3f(-x,-y,1.0f);				    // Left back Of The Quad (bottom)
            glVertex3f(-x,-y,z);				    // Left front Of The Quad (bottom)



            glVertex3f(x,y,1.0f);					 // Top Right Of The Quad (Back)
            glVertex3f(-x,y,1.0f);					// Top Left Of The Quad (Back)
            glVertex3f(-x,-y,1.0f);					// Bottom Left Of The Quad (Back)
            glVertex3f(x,-y,1.0f);					// Bottom Right Of The Quad (Back)



            glVertex3f(x,y,z);					    // Top Right Of The Quad (Front)
            glVertex3f(-x,y,z);					// Top Left Of The Quad (Front)
            glVertex3f(-x,-y,z);					// Bottom Left Of The Quad (Front)
            glVertex3f(x,-y,z);					// Bottom Right Of The Quad (Front)


        glEnd();
}

void player1(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(tx1,ty1,0);
    glTranslatef(-1.0,-1.0,11);
    glScalef(0.1,0.1,0.1);

    glPushMatrix();
    rgb(237, 211, 118);
    vQuad(x,y,z);

    rgb(153, 197, 247);
    glBegin(GL_QUADS);
        glVertex3f(x-0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,-y+0.2,z+0.1);
        glVertex3f(x-0.2,-y+0.2,z+0.1);

        rgb(0, 0, 0);
        glVertex3f(-x+0.8,y-0.3,z+0.19);// Top Right Of The Quad (Front)
        glVertex3f(-x+0.3,y-0.3,z+0.19);// Top Left Of The Quad (Front)
        glVertex3f(-x+0.3,-y+0.8,z+0.19);// Bottom Left Of The Quad (Front)
        glVertex3f(-x+0.8,-y+0.8,z+0.19);// Bottom Right Of The Quad (Front)

        rgb(0, 0, 0);
        glVertex3f(x-0.3,y-0.3,z+0.19);// Top Right Of The Quad (Front)
        glVertex3f(x-0.8,y-0.3,z+0.19);// Top Left Of The Quad (Front)
        glVertex3f(x-0.8,-y+0.8,z+0.19);// Bottom Left Of The Quad (Front)
        glVertex3f(x-0.3,-y+0.8,z+0.19);// Bottom Right Of The Quad (Front)

    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void player2(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(tx2,ty2,0);
    glTranslatef(-1.0,-1.0,11);
    glScalef(0.1,0.1,0.1);

    glPushMatrix();
    rgb(237, 211, 118);
    vQuad(x,y,z);

    rgb(238, 179, 205);
    glBegin(GL_QUADS);
        glVertex3f(x-0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,-y+0.2,z+0.1);
        glVertex3f(x-0.2,-y+0.2,z+0.1);

        rgb(0, 0, 0);
        glVertex3f(-x+0.8,y-0.3,z+0.19);// Top Right Of The Quad (Front)
        glVertex3f(-x+0.3,y-0.3,z+0.19);// Top Left Of The Quad (Front)
        glVertex3f(-x+0.3,-y+0.8,z+0.19);// Bottom Left Of The Quad (Front)
        glVertex3f(-x+0.8,-y+0.8,z+0.19);// Bottom Right Of The Quad (Front)

        rgb(0, 0, 0);
        glVertex3f(x-0.3,y-0.3,z+0.19);// Top Right Of The Quad (Front)
        glVertex3f(x-0.8,y-0.3,z+0.19);// Top Left Of The Quad (Front)
        glVertex3f(x-0.8,-y+0.8,z+0.19);// Bottom Left Of The Quad (Front)
        glVertex3f(x-0.3,-y+0.8,z+0.19);// Bottom Right Of The Quad (Front)

    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void stageBlock(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(-1.0,-1.0,11);
    glScalef(0.1,0.1,0.1);

    glPushMatrix();
    rgb(164, 138, 111);
    vQuad(x,y,z);

    rgb(207, 194, 177);
    glBegin(GL_QUADS);
        glVertex3f(x-0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,y-0.2,z+0.1);
        glVertex3f(-x+0.2,-y+0.2,z+0.1);
        glVertex3f(x-0.2,-y+0.2,z+0.1);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

void plane(float x, float y, float z)
{
  // Draw A plane
        glBegin(GL_QUADS);
            rgb(91, 139, 65);
            glVertex3f(x,y,z+0.1);
            glVertex3f(-x,y,z+0.1);
            glVertex3f(-x,-y,z+0.1);
            glVertex3f(x,-y,z+0.1);


            rgb(42, 62, 27);
            glVertex3f(x+0.1,y+0.1,z);
            glVertex3f(-x-0.1,y+0.1,z);
            glVertex3f(-x-0.1,-y-0.1,z);
            glVertex3f(x+0.1,-y-0.1,z);
        glEnd();
}

void init(void)
{

   glClearColor (0, 0, 0, 0);
   //glOrtho(-50.0, 50.0, -50.0, 50.0, -50.0, 50.0);
}

void showText(char text[], float x, float y, float z)
{
    glRasterPos3f( x , y , z);
    for(int i = 0; text[i] != '\0'; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
}

void display(void)
{

   glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); // GL_COLOR_BUFFER_BIT indicates that the buffer is currently enabled for color writing, GL_DEPTH_BUFFER_BIT indicates that the buffer is currently enabled for depth buffer

   glMatrixMode(GL_PROJECTION);       // Specify which matrix is the current matrix mode
   glLoadIdentity();                  // Replace the current matrix with the identity matrix and essentially resets the matrix back to its default state
   int w=glutGet(GLUT_WINDOW_WIDTH);
   int h=glutGet(GLUT_WINDOW_HEIGHT);
   gluPerspective(40,w/h,0.1,100);    // fovy specifies the field of view angle in degrees in y direction, aspect specifies aspect ratio that determines the field of view in the x direction, znear and zfar specifies the distance from viewer to the near and far clipping plane respectively (always positive)
   glMatrixMode(GL_MODELVIEW);       //  To allow modeling and viewing transformation on 3D object

   glLoadIdentity();
   gluLookAt(                       //  eyex, eyey, eyez specify the position of the eye point, centerx, centery, centerz specify the position of reference point, upx, upy, upz specify the direction of up vector
               //a,b,c,
               0.0,-1.2,14.5,
               0,3.0,0,
               0,1,0
             );



	glPushMatrix();
   //glRotatef(l_t,0.0f,1.0f,0.0f);
   plane(1.1,1.1,11.0);
   glPopMatrix();

   for(float i = 0.25; i < 2.0; i+=0.5){
        for(float j = 0.25; j < 2.0; j+=0.5){
            glPushMatrix();
            glTranslatef(i,j,0.0);
            stageBlock(1.5, 1.5, 2.0);
            glPopMatrix();
        }
   }

    player1(1.0, 1.0, 2.0);


    player2(1.0, 1.0, 2.0);


    for(float i = 0.2; i <= p1_life; i+=0.2){
        glPushMatrix();
        // player 1 life
        rgb(153, 197, 247);
        glPushMatrix();
            glTranslatef(-2.5+i,0.5,11.0);
            glScalef(0.1,0.1,0.1);
            vQuad(1.0,1.0,2.0);
        glPopMatrix();
        glPopMatrix();
    }


    for(float i = 0.2; i <= p2_life; i+=0.2){
        glPushMatrix();
        // player 2 life
        rgb(238, 179, 205);
        glPushMatrix();
            glTranslatef(1.3+i,0.5,11.0);
            glScalef(0.1,0.1,0.1);
            vQuad(1.0,1.0,2.0);
        glPopMatrix();
        glPopMatrix();
    }




    if(p1_bomb){
        p1_bomb = bmb1.drop();
        glutPostRedisplay();

        if(p1_bomb == 2){

        if(bmb1.hit(tx1, ty1)){
            p1_life -= 0.2;
        }
        if(bmb1.hit(tx2, ty2)){
            p2_life -= 0.2;
        }



        }
    }


    if(p2_bomb){
        p2_bomb = bmb2.drop();
        glutPostRedisplay();

        if(p2_bomb == 2){

        if(bmb2.hit(tx1, ty1)){
            p1_life -= 0.2;
        }
        if(bmb2.hit(tx2, ty2)){
            p2_life -= 0.2;
        }


        }
    }

        if(p1_life-0.2<=0 || p2_life-0.2<=0){
            if(p1_life-0.2<=0 && p2_life-0.2<=0){
                    rgb(255, 128, 51);
                showText("draw match!", -0.17, -0.32, 12);
            }
            if(p1_life-0.2 <= 0){
                rgb(238, 179, 205);
                showText("pink wins!", 1.07, 0.2, 12.0);
            }
            if(p2_life-0.2 <= 0){
                rgb(153, 197, 247);
                showText("blue wins!", -1.8, 0.2, 12.0);
            }
        }

//    printf("tx1: %f; ty1: %f\ntx2: %f; ty2: %f\n\n", tx1, ty1, tx2, ty2);

   glutSwapBuffers();

}
void my_keyboard(unsigned char key, int p, int q)
{
switch (key) {
    case 'w':  //player1 up
        if(ty1+0.5 <= 2.0)
        ty1 +=0.5;
        glutPostRedisplay();
		break;
	case 's':  //player1 down
	    if(ty1-0.5 >= 0.0)
	    ty1 -=0.5;
        glutPostRedisplay();
		break;
	case 'a':  //player1 left
	    if(tx1-0.5 >= 0.0)
	    tx1 -=0.5;
        glutPostRedisplay();
		break;
	case 'd':  //player1 right
	    if(tx1+0.5 <= 2.0)
	    tx1 +=0.5;
        glutPostRedisplay();
		break;
    case ' ':  //drop bomb1
        if(p1_bomb){
            break;
        }
        bmb1.x = tx1;
        bmb1.y = ty1;
        bmb1.tim = time(NULL);
        bmb1.alrT = false;
        bmb1.ang = 30.0;
        bmb1.ex = false;
        p1_bomb = 1;
        glutPostRedisplay();
		break;
    case '8':  //player2 up
        if(ty2+0.5 <= 2.0)
        ty2 +=0.5;
        glutPostRedisplay();
		break;
	case '5':  //player2 down
	    if(ty2-0.5 >= 0.0)
	    ty2 -=0.5;
        glutPostRedisplay();
		break;
	case '4':  //player2 left
	    if(tx2-0.5 >= 0.0)
	    tx2 -=0.5;
        glutPostRedisplay();
		break;
	case '6':  //player2 right
	    if(tx2+0.5 <= 2.0)
	    tx2 +=0.5;
        glutPostRedisplay();
		break;
    case '0':  //drop bomb2
        if(p2_bomb){
            break;
        }
        bmb2.x = tx2;
        bmb2.y = ty2;
        bmb2.tim = time(NULL);
        bmb2.alrT = false;
        bmb2.ang = 30.0;
        bmb2.ex = false;
        p2_bomb = 1;
        glutPostRedisplay();
		break;
    case 'f':  //front view
        a=0.0,b=0.0,c=15.0;
        glutPostRedisplay();
		break;
    case 'b':  //back view
        a=0.0,b=0.0,c=-15.0;
        glutPostRedisplay();
		break;
    case 'l':  //left view
        a=-50.0,b=0.0,c=0.0;
        glutPostRedisplay();
		break;
    case 'r':  //right view
        a=50.0,b=0.0,c=0.0;
        glutPostRedisplay();
		break;
    case 't': //top view
        a=0.0,b=50.0,c=0.0001;
        glutPostRedisplay();
		break;
    case 'm': //bottom view
        a=0.0,b=-50.0,c=0.0001;
        glutPostRedisplay();
		break;
     default:
        break;
}
//printf("tx1: %f; ty1: %f\ntx2: %f; ty2: %f\n\n", tx1, ty1, tx2, ty2);
}

void spinDisplay_left(void)		//spin speed
{

    l_t =l_t-0.2;
    glutPostRedisplay();
}

void spinDisplay_right(void)		//spin speed
{

    l_t =l_t+0.2;
    glutPostRedisplay();
}

void specialKeys(int key,int x,int y)
{
    	switch (key) {

		case GLUT_KEY_LEFT:
				//tx1 -=0.5;
				glutPostRedisplay();
				break;

		case GLUT_KEY_RIGHT:
				//tx1 +=0.5;
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
				//ty1 -=0.5;
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
				//ty1 +=0.5;
				glutPostRedisplay();
				break;
	  default:
			break;
	}
	//printf("tx:%f; ty:%f\n", tx,ty);
}

void mouse(int button, int state, int s, int t)
{

   switch (button)
   {
      case GLUT_LEFT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay_left);
         break;
      case GLUT_RIGHT_BUTTON:
         if (state == GLUT_DOWN)
            glutIdleFunc(spinDisplay_right);
          break;
      case GLUT_MIDDLE_BUTTON:
          if (state == GLUT_DOWN)
            glutIdleFunc(NULL);
         break;
      default:
         break;
   }
}



int main()
{

    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1200, 600);
	glutInitWindowPosition (0, 0);
	glutCreateWindow ("bomberman 3D");
	init();
	glEnable(GL_DEPTH_TEST);
    glutSpecialFunc(specialKeys);
    glutDisplayFunc(display);
    glutKeyboardFunc(my_keyboard);
    //glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
