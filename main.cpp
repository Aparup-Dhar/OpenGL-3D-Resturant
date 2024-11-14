#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>
#include<math.h>
#include "BmpLoader.h"

unsigned int ID;
double windowHeight=700, windowWidth=1000;
double eyeX=15.0, eyeY=4.0, eyeZ=17.0, refX = 0, refY=0,refZ=0;//eyeX=15.0, eyeY=4.0, eyeZ=17.0, refX = 0, refY=0,refZ=0;
//double eyeX=7.0, eyeY=2.0, eyeZ=15.0, refX = 0, refY=0,refZ=0; original
GLboolean switchOne = false, switchTwo=false, switchThree=false;

static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 0.0, 0.0},
    {1.0, 4.0, 1.0}
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2},
    {4, 2, 3},
    {4, 3, 0},
    {4, 0, 1}
};

static GLubyte PquadIndices[1][4] =
{
    {0, 3, 2, 1}
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void drawpyramid(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { ambX, ambY, ambZ, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0], v_pyramid[p_Indices[i][0]][1], v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0], v_pyramid[p_Indices[i][1]][1], v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0], v_pyramid[p_Indices[i][2]][1], v_pyramid[p_Indices[i][2]][2]);
        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);
        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[PquadIndices[i][0]][0], v_pyramid[PquadIndices[i][0]][1], v_pyramid[PquadIndices[i][0]][2],
                    v_pyramid[PquadIndices[i][1]][0], v_pyramid[PquadIndices[i][1]][1], v_pyramid[PquadIndices[i][1]][2],
                    v_pyramid[PquadIndices[i][2]][0], v_pyramid[PquadIndices[i][2]][1], v_pyramid[PquadIndices[i][2]][2]);
        glVertex3fv(&v_pyramid[PquadIndices[i][0]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][1]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][2]][0]);
        glVertex3fv(&v_pyramid[PquadIndices[i][3]][0]);
    }
    glEnd();

}
static GLfloat v_cube[8][3] =
{
    {0.0, 0.0, 0.0}, //0s
    {0.0, 0.0, 3.0}, //1
    {3.0, 0.0, 3.0}, //2
    {3.0, 0.0, 0.0}, //3
    {0.0, 3.0, 0.0}, //4
    {0.0, 3.0, 3.0}, //5
    {3.0, 3.0, 3.0}, //6
    {3.0, 3.0, 0.0}  //7
};

static GLubyte quadIndices[6][4] =
{
    {0, 1, 2, 3}, //bottom
    {4, 5, 6, 7}, //top
    {5, 1, 2, 6}, //front
    {0, 4, 7, 3}, // back is clockwise
    {2, 3, 7, 6}, //right
    {1, 5, 4, 0}  //left is clockwise
};


static GLfloat colors[6][3] =
{
    {0.4, 0.1, 0.0}, //bottom
    {0.6, 0.0, 0.7}, //top
    {0.0, 1.0, 0.0},
    {0.0, 1.0, 1.0},
    {0.8, 0.0, 0.0},
    {0.3, 0.6, 0.7}
};




void drawCube(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine=50)
{
    GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat mat_ambient[] = { 0.05, 0.05, 0.05, 1.0 };
    GLfloat mat_diffuse[] = { difX, difY, difZ, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {shine};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}

void drawCube2()
{

    glBegin(GL_QUADS);

    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_cube[quadIndices[i][0]][0], v_cube[quadIndices[i][0]][1], v_cube[quadIndices[i][0]][2],
                    v_cube[quadIndices[i][1]][0], v_cube[quadIndices[i][1]][1], v_cube[quadIndices[i][1]][2],
                    v_cube[quadIndices[i][2]][0], v_cube[quadIndices[i][2]][1], v_cube[quadIndices[i][2]][2]);
        glVertex3fv(&v_cube[quadIndices[i][0]][0]);glTexCoord2f(1,1);
        glVertex3fv(&v_cube[quadIndices[i][1]][0]);glTexCoord2f(1,0);
        glVertex3fv(&v_cube[quadIndices[i][2]][0]);glTexCoord2f(0,0);
        glVertex3fv(&v_cube[quadIndices[i][3]][0]);glTexCoord2f(0,1);
    }
    glEnd();
}




void base()
{
    // right wall
    //glColor3f(0.3, 0.2, 1.0);
    glPushMatrix();
    glTranslatef(-2,-0.8,0.0);
    glScalef(5, 2, 0.1);
    drawCube(0.3, 0.2, 1.0,0.3, 0.2, 1.0);
    glPopMatrix();

    // left wall
    //glColor3f(0.3, 0.2, 1.0);
    glPushMatrix();
    glTranslatef(-2.0,-0.8,0);
    glScalef(0.1, 2, 5);
    drawCube(0.3, 0.2, 1.0,0.3, 0.2, 1.0);
    glPopMatrix();

    //new wall
    //glPushMatrix();
    //glTranslatef(12.7,-0.8,0);
    //glScalef(0.1, 2, 5);
    //drawCube(0.3, 0.2, 1.0,0.3, 0.2, 1.0);
    //glPopMatrix();

   //ceiling
    //glColor3f(0.9, 0.8, 1.0);
    glPushMatrix();
    glTranslatef(-2,5.1,0);
    glScalef(5, 0.1, 5);
    drawCube(0.9, 0.8, 1.0,0.9, 0.8, 1.0);
    glPopMatrix();

    // carpet
    //glColor3f(0.4, 0.1, 0.0);
    //glPushMatrix();
    //glTranslatef(3,-0.2,7);
    //glScalef(1.3, 0.01, 1.7);
    //drawCube();
    //glPopMatrix();

     // surface
    //glColor3f(0.7, 0.7, 1.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,1);
    glPushMatrix();
    glTranslatef(-2,-1,0);
    glScalef(5, 0.1, 5);//glScalef(5, 0.1, 5);
    drawCube2();
    //drawCube(0.7, 0.7, 1.0,0.7, 0.7, 1.0);
    glPopMatrix();
        glDisable(GL_TEXTURE_2D);
}


void chairfront(){

       //seat
       //glColor3f(0.6, 0.6, 0.4);
           glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.4,8);
       glScalef(0.20, 0.02, 0.25);
       drawCube(0.6, 0.6, 0.4,0.6, 0.6, 0.4);
       glPopMatrix();
        glDisable(GL_TEXTURE_2D);

       //back
       //glColor3f(0.8,0.6,0.4);
                  glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.4,8);
       glScalef(0.20, 0.25, 0.02);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
         glDisable(GL_TEXTURE_2D);

       //leg1
       //glColor3f(0.8,0.6,0.4);
                         glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,3);
       glPushMatrix();
       glTranslatef(4,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();


              //leg2
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

                     //leg3
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg4
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);


}

void chairback(){

       //seat
       //glColor3f(0.6, 0.6, 0.4);
                                glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.4,8);
       glScalef(0.20, 0.02, 0.25);
       drawCube(0.6, 0.6, 0.4,0.6, 0.6, 0.4);
       glPopMatrix();

       //back
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,0.4,8.7);
       glScalef(0.20, 0.25, 0.02);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
              glDisable(GL_TEXTURE_2D);

       //leg1
       //glColor3f(0.8,0.6,0.4);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,3);
       glPushMatrix();
       glTranslatef(4,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg2
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

                     //leg3
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg4
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);


}

void chair_right(){

       //seat
       //glColor3f(0.6, 0.6, 0.4);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.4,8);
       glScalef(0.20, 0.02, 0.25);
       drawCube(0.6, 0.6, 0.4,0.6, 0.6, 0.4);
       glPopMatrix();

       //back
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,0.4,8.0); //4,0.4/8.7
       glScalef(0.02, 0.25, 0.25);//0.20,0.25,0.02
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
              glDisable(GL_TEXTURE_2D);

       //leg1
       //glColor3f(0.8,0.6,0.4);
               glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,3);
       glPushMatrix();
       glTranslatef(4,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg2
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

                     //leg3
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg4
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);


}

void chair_left(){

       //seat
       //glColor3f(0.6, 0.6, 0.4);
                      glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.4,8);
       glScalef(0.20, 0.02, 0.25);
       drawCube(0.6, 0.6, 0.4,0.6, 0.6, 0.4);
       glPopMatrix();

       //back
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.55,0.4,8.0); //4,0.4/8.7
       glScalef(0.02, 0.25, 0.25);//0.20,0.25,0.02
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
              glDisable(GL_TEXTURE_2D);

       //leg1
       //glColor3f(0.8,0.6,0.4);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,3);
       glPushMatrix();
       glTranslatef(4,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg2
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

                     //leg3
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8.65);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg4
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.54,-0.2,8);
       glScalef(0.02, 0.20, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);


}

void table(){

       //table
       //glColor3f(0.8, 0.4, 0.0);
               glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,2);
       glPushMatrix();
       glTranslatef(4,0.75,8);
       glScalef(0.30, 0.02, 0.35);
       drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
       glPopMatrix();
       glDisable(GL_TEXTURE_2D);

              //leg1
       //glColor3f(0.8,0.6,0.4);
                      glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,3);
       glPushMatrix();
       glTranslatef(4,-0.2,8);
       glScalef(0.02, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg2
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4,-0.2,8.95);
       glScalef(0.02, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

                     //leg3
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.85,-0.2,8.95);
       glScalef(0.02, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

              //leg4
       //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(4.84,-0.2,8);
       glScalef(0.02, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();
              glDisable(GL_TEXTURE_2D);

}



//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// DEMO CODE FOR DRAW WINDOW
void window_right()
{
    //Window ********************************************

    //window white open
    //glColor3f(0.1,0.7,0.9);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9); //0.5,1,9.6
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, .6, .3);
    drawCube(0.1,0.7,0.9,0.1,0.7,0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //window side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.04, 0.6, 0.0001);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window left side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.9,1,9.8);
    glScalef(0.04, 0.6, 0.0001);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window upper side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.8,2.7,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.05, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();


    //window lower side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.8,1.02,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.05, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window vertical bar 1
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.87,1.8,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.03, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window vertical bar 2
    //glColor3f(0.0,0.0,0.0);
    //glPushMatrix();
    //glTranslatef(-0.87,1.6,8.9);
    //glRotatef(22, 0,0,1);
    //glScalef(0.0001, 0.02, 0.3);
    //drawCube();
    //glPopMatrix();

    //window horizontal bar
    //glColor3f(0.0,0.0,0.0);
    //glPushMatrix();
    //glTranslatef(-0.87,1,9.3);
    //glRotatef(22, 0,0,1);
    //glScalef(0.0001, 0.6, 0.02);
    //drawCube();
    //glPopMatrix();
}

void window_left()
{
    //Window ********************************************

    //window white open
    //glColor3f(0.1,0.7,0.9);
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,7);
    glPushMatrix();
    glTranslatef(-0.9,1,8.9); //0.5,1,9.6
    //glRotatef(22, 0,0,1);
    glScalef(0.3, .6, 0.0001);//(0.0001, .6, .3);
    drawCube(0.1,0.7,0.9,0.1,0.7,0.9);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    //window side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(0.0,1,8.9);
    //glRotatef(22, 0,0,1);
    glScalef(0.0001, 0.6, 0.04);//(0.04, 0.6, 0.0001);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window left side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-1.0,1,8.8);
    glScalef(0.0001, 0.6, 0.04);//(0.04, 0.6, 0.0001);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window upper side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.9,2.7,9.0);
    //glRotatef(22, 0,0,1);
    glScalef(0.3, 0.05, 0.0001);//0.0001, 0.05, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();


    //window lower side corner
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.9,1.02,9.0);
    //glRotatef(22, 0,0,1);
    glScalef(0.3, 0.05, 0.0001);//(0.0001, 0.05, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

    //window vertical bar 1
    //glColor3f(0.9,1,0.8);
    glPushMatrix();
    glTranslatef(-0.87,1.8,9.0);
    //glRotatef(22, 0,0,1);
    glScalef(0.3, 0.03, 0.0001);//(0.0001, 0.03, 0.3);
    drawCube(0.9,1,0.8,0.9,1,0.8);
    glPopMatrix();

}

void tree(){
    //glColor3f(0.4, 0.1, 0.0);
                          glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,5);
    glPushMatrix();
    glTranslatef(0.0,-0.5,0.0);
    glScalef(0.22, 0.3, 0.20);//(0.04, 0.6, 0.0001);
    drawCube(0.4, 0.1, 0.0,0.4, 0.1, 0.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

           //glColor3f(0.8,0.6,0.4);
       glPushMatrix();
       glTranslatef(0.3,0.2,0.3);
       glScalef(0.03, 0.32, 0.03);
       drawCube(0.8,0.6,0.4,0.8,0.6,0.4);
       glPopMatrix();

           //glColor3f(0.6, 0.9, 0.2);
          glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,4);
    glPushMatrix();
    glTranslatef(0.2,0.8,0.2);
    glScalef(0.1, 0.05, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();

               //glColor3f(0.6, 0.8, 0.1);
    glPushMatrix();
    glTranslatef(0.1,0.9,0.1);
    glScalef(0.15, 0.2, 0.15);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.8, 0.1,0.6, 0.8, 0.1);
    glPopMatrix();

               //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,1.4,0.2);
    glScalef(0.1, 0.08, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void bar(){
    //glColor3f(0.6, 0.6, 0.4);
            glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,3);
    glPushMatrix();
    glTranslatef(0.0,-0.5,0.0);
    glScalef(0.3, 0.3, 3.3);//(0.04, 0.6, 0.0001);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

        //glColor3f(0.8, 0.4, 0.0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,6);
    glPushMatrix();
    glTranslatef(-0.3,0.4,0.0);
    glScalef(0.5, 0.05, 3.3);//(0.04, 0.6, 0.0001);
    drawCube(1.0, 1.0, 1.0,1.0, 1.0, 1.0);
    glPopMatrix();
      glDisable(GL_TEXTURE_2D);
}

void fan(){
    //glColor3f(0.3, 0.1, 0.4);
    glPushMatrix();
    glTranslatef(0.0,0.45,0.0);
    glScalef(0.22, 0.05, 0.20);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
    glPopMatrix();

    //glColor3f(0.3, 0.1, 0.4);
       glPushMatrix();
       glTranslatef(0.3,0.6,0.3);
       glScalef(0.03, 0.30, 0.03);
       drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
       glPopMatrix();

           //glColor3f(0.9, 0.5, 0.0);
    glPushMatrix();
    glTranslatef(0.2,0.38,0.2);
    glScalef(0.1, 0.05, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 0.5, 0.0,0.9, 0.5, 0.0);
    glPopMatrix();

    //glColor3f(0.3, 0.1, 0.4);
    glPushMatrix();
    glTranslatef(0.4,0.5,0.15);
    glScalef(0.5, 0.03, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
    glPopMatrix();

    //glColor3f(0.3, 0.1, 0.4);
    glPushMatrix();
    glTranslatef(-1.2,0.5,0.15);
    glScalef(0.5, 0.03, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
    glPopMatrix();

    //glColor3f(0.3, 0.1, 0.4);
    glPushMatrix();
    glTranslatef(0.15,0.5,0.15);
    glScalef(0.1, 0.03, 0.5);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
    glPopMatrix();

    //glColor3f(0.3, 0.1, 0.4);
    glPushMatrix();
    glTranslatef(0.15,0.5,-1);
    glScalef(0.1, 0.03, 0.5);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4);
    glPopMatrix();

        //glColor3f(0.7, 0.7, 0.6);
    glPushMatrix();
    glTranslatef(0.0,1.5,0.0);
    glScalef(0.22, 0.05, 0.20);//(0.04, 0.6, 0.0001);
    drawCube(0.7, 0.7, 0.6,0.7, 0.7, 0.6);
    glPopMatrix();


}

void burger(){

    //glColor3f(0.9, 1.0, 0.8);
    glPushMatrix();
    glTranslatef(0.0,-2.6,0.0);
    glScalef(0.24, 0.030, 0.24);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.8,0.9, 1.0, 0.8);
    glPopMatrix();

    //glColor3f(0.9, 0.7, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.5,0.1);
    glScalef(0.18, 0.040, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 0.7, 0.0,0.9, 0.7, 0.0);
    glPopMatrix();

        //glColor3f(0.3, 1.0, 0.1);
    glPushMatrix();
    glTranslatef(0.05,-2.4,0.1);
    glScalef(0.21, 0.025, 0.19);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 1.0, 0.1,0.3, 1.0, 0.1);
    glPopMatrix();

        //glColor3f(0.6, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.35,0.1);
    glScalef(0.18, 0.025, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.0, 0.0,0.6, 0.0, 0.0);
    glPopMatrix();

            //glColor3f(0.8, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.25,0.1);
    glScalef(0.18, 0.025, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(0.8, 0.0, 0.0,0.8, 0.0, 0.0);
    glPopMatrix();

                //glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.15,0.1);
    glScalef(0.18, 0.025, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(1.0, 1.0, 0.0,1.0, 1.0, 0.0);
    glPopMatrix();


    //glColor3f(0.9, 0.7, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.05,0.1);
    glScalef(0.18, 0.040, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 0.7, 0.0,0.9, 0.7, 0.0);
    glPopMatrix();

        //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.2,-1.95,0.2);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();

            //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.4,-1.95,0.2);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();

            //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.2,-1.95,0.4);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();


            //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.4,-1.95,0.4);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();

}

void pizza(){

    //glColor3f(0.9, 1.0, 0.8);
    glPushMatrix();
    glTranslatef(0.0,-2.6,0.0);
    glScalef(0.24, 0.030, 0.24);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.8,0.9, 1.0, 0.8);
    glPopMatrix();

    //glColor3f(0.9, 0.7, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.5,0.1);
    glScalef(0.18, 0.040, 0.18);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 0.7, 0.0,0.9, 0.7, 0.0);
    glPopMatrix();

                //glColor3f(0.8, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.15,-2.40,0.15);
    glScalef(0.15, 0.023, 0.15);//(0.04, 0.6, 0.0001);
    drawCube(0.8, 0.0, 0.0,0.8, 0.0, 0.0);
    glPopMatrix();


        //glColor3f(0.3, 1.0, 0.1);
    glPushMatrix();
    glTranslatef(0.2,-2.38,0.2);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 1.0, 0.1,0.3, 1.0, 0.1);
    glPopMatrix();

            //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.45,-2.38,0.2);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();

            //glColor3f(0.9, 1.0, 0.5);
    glPushMatrix();
    glTranslatef(0.2,-2.38,0.4);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.5,0.9, 1.0, 0.5);
    glPopMatrix();


            //glColor3f(0.3, 1.0, 0.1);
    glPushMatrix();
    glTranslatef(0.45,-2.38,0.4);
    glScalef(0.03, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(0.3, 1.0, 0.1,0.3, 1.0, 0.1);
    glPopMatrix();

}

void hotdog(){

    //glColor3f(0.9, 1.0, 0.8);
    glPushMatrix();
    glTranslatef(0.0,-2.6,0.0);
    glScalef(0.24, 0.030, 0.24);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 1.0, 0.8,0.9, 1.0, 0.8);
    glPopMatrix();

    //glColor3f(0.9, 0.7, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.5,0.3);
    glScalef(0.18, 0.040, 0.08);//(0.04, 0.6, 0.0001);
    drawCube(0.9, 0.7, 0.0,0.9, 0.7, 0.0);
    glPopMatrix();

                //glColor3f(0.8, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(0.04,-2.40,0.30);
    glScalef(0.21, 0.023, 0.06);//(0.04, 0.6, 0.0001);
    drawCube(0.8, 0.0, 0.0,0.8, 0.0, 0.0);
    glPopMatrix();


        //glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.1,-2.38,0.3);
    glScalef(0.17, 0.020, 0.03);//(0.04, 0.6, 0.0001);
    drawCube(1.0, 1.0, 0.0,1.0, 1.0, 0.0);
    glPopMatrix();



}

void bottle(){



           //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.2,0.8,0.2);
    glScalef(0.1, 0.2, 0.1);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();

               //glColor3f(0.6, 0.9, 0.2);
    glPushMatrix();
    glTranslatef(0.27,1.3,0.27);
    glScalef(0.05, 0.16, 0.05);//(0.04, 0.6, 0.0001);
    drawCube(0.6, 0.9, 0.2,0.6, 0.9, 0.2);
    glPopMatrix();

                   //glColor3f(0.4, 0.3, 1.);
    glPushMatrix();
    glTranslatef(0.24,1.7,0.24);
    glScalef(0.07, 0.03, 0.07);//(0.04, 0.6, 0.0001);
    drawCube(0.4, 0.3, 1.0,0.4, 0.3, 1.0);
    glPopMatrix();

                       //glColor3f(0.4, 0.3, 1.);
    glPushMatrix();
    glTranslatef(0.17,0.95,0.17);
    glScalef(0.12, 0.09, 0.12);//(0.04, 0.6, 0.0001);
    drawCube(0.4, 0.3, 1.0,0.4, 0.3, 1.0);
    glPopMatrix();

}

void many_bottle(){
    glPushMatrix();
    glTranslatef(0.09,0,1.3);
    bottle();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.09,0,1.9);
    bottle();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(0.09,0,2.5);
    bottle();
    glPopMatrix();

            glPushMatrix();
    glTranslatef(0.09,0,3.1);
    bottle();
    glPopMatrix();

                glPushMatrix();
    glTranslatef(0.09,0,3.7);
    bottle();
    glPopMatrix();
}

void cupboard()
{
    //Wardrobe *******************************************

       //wardrobe
       //glColor3f(0.4,0.4,0.4);
       glPushMatrix();
       glTranslatef(0,0,4);
       glScalef(0.12, 0.6, 0.4);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();

       //wardrobe's 1st drawer
       //glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,1.4,4.02);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube(0.5,0.2,0.2,0.5,0.2,0.2);
       glPopMatrix();

       //wardrobe's 2nd drawer
       //glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,1,4.02);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube(0.5,0.2,0.2,0.5,0.2,0.2);
       glPopMatrix();

       //wardrobe's 3rd drawer
       //glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,0.6,4.02);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube(0.5,0.2,0.2,0.5,0.2,0.2);
       glPopMatrix();

       //wardrobe's 4th drawer
       //glColor3f(0.5,0.2,0.2);
       glPushMatrix();
       glTranslatef(0.36,0.2,4.02);
       //glRotatef(22, 0,0,1);
       glScalef(0.0001, 0.11, 0.38);
       drawCube(0.5,0.2,0.2,0.5,0.2,0.2);
       glPopMatrix();

       glPushMatrix();
       glTranslatef(0.16,1.2,3.45);
       glScalef(0.4, 0.3, 0.4);
       many_bottle();
       glPopMatrix();

              glPushMatrix();
       glTranslatef(0.16,0.8,3.45);
       glScalef(0.4, 0.3, 0.4);
       many_bottle();
       glPopMatrix();

                     glPushMatrix();
       glTranslatef(0.16,0.4,3.45);
       glScalef(0.4, 0.3, 0.4);
       many_bottle();
       glPopMatrix();

        glPushMatrix();
       glTranslatef(0.16,0.0,3.45);
       glScalef(0.4, 0.3, 0.4);
       many_bottle();
       glPopMatrix();

    }


void fridge(){

       //glColor3f(0.4,0.4,0.4);
       glPushMatrix();
       glTranslatef(-7.2,0.0,1.2);
       glScalef(0.5, 1.8, 0.9);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();

       //glColor3f(0.7, 0.7, 0.6);
              glPushMatrix();
       glTranslatef(-6.55,0.48,1.4);
       glScalef(0.3, 1.5, 0.75);
       drawCube(0.7, 0.7, 0.6,0.7, 0.7, 0.6);
       glPopMatrix();

              //glColor3f(0.4,0.4,0.4);
       glPushMatrix();
       glTranslatef(-7.1,3.5,1.3);
       glScalef(0.5, 0.05, 0.8);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();

                     //glColor3f(0.4,0.4,0.4);
       glPushMatrix();
       glTranslatef(-7.1,3.9,1.5);
       glScalef(0.5, 0.05, 0.2);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();

                            //glColor3f(0.4,0.4,0.4);
       glPushMatrix();
       glTranslatef(-7.1,2.9,1.5);
       glScalef(0.5, 0.05, 0.2);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();
}

void fish(){

           //glColor3f(1.0,0.6,0.0);
       glPushMatrix();
       glTranslatef(8,0,11);
       glScalef(0.2, 0.08, 0.02);
       drawCube(1.0,0.6,0.0,1.0,0.6,0.0);
       glPopMatrix();

                  //glColor3f(1.0,0.7,0.0);
       glPushMatrix();
       glTranslatef(7.8,-0.16,11);
       glScalef(0.15, 0.18, 0.02);
       drawCube(1.0,0.7,0.0,1.0,0.7,0.0);
       glPopMatrix();

       //glColor3f(0.0,0.0,0.0);
       glPushMatrix();
       glTranslatef(7.9,0.2,11);
       glScalef(0.03, 0.03, 0.03);
       drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
       glPopMatrix();

              //glColor3f(1.0,1.0,0.4);
       glPushMatrix();
       glTranslatef(7.8,0.0,11);
       glScalef(0.03, 0.03, 0.03);
       drawCube(1.0,1.0,0.4,1.0,1.0,0.4);
       glPopMatrix();
}

void fish_right(){

           //glColor3f(1.0,0.6,0.0);
       glPushMatrix();
       glTranslatef(7.7,0,10.8);
       glScalef(0.02, 0.08, 0.2);
       drawCube(1.0,0.6,0.0,1.0,0.6,0.0);
       glPopMatrix();

                  //glColor3f(1.0,0.7,0.0);
       glPushMatrix();
       glTranslatef(7.71,-0.16,11);
       glScalef(0.02, 0.18, 0.15);
       drawCube(1.0,0.7,0.0,1.0,0.7,0.0);
       glPopMatrix();

       //glColor3f(0.0,0.0,0.0);
       glPushMatrix();
       glTranslatef(7.72,0.2,11.3);
       glScalef(0.03, 0.03, 0.03);
       drawCube(0.0,0.0,0.0,0.0,0.0,0.0);
       glPopMatrix();

              glColor3f(1.0,1.0,0.4);
       glPushMatrix();
       glTranslatef(7.72,0.0,11.37);
       glScalef(0.03, 0.03, 0.03);
       drawCube(1.0,1.0,0.4,1.0,1.0,0.4);
       glPopMatrix();
}

void aqua(){

       //glColor3f(0.7,0.4,0.0);
       glPushMatrix();
       glTranslatef(2,-2,10);
       glScalef(1.7, 0.5, 0.4);
       drawCube(0.7,0.4,0.0,0.7,0.4,0.0);
       glPopMatrix();

        //glColor3f(0.8,0.6,0.3);
       glPushMatrix();
       glTranslatef(2.65,-1.8,10.2);
       glScalef(1.5, 0.4, 0.3);
       drawCube(0.8,0.6,0.3,0.8,0.6,0.3);
       glPopMatrix();

               //glColor3f(0.8,0.6,0.3);
       glPushMatrix();
       glTranslatef(2.4,-1.8,10.35);
       glScalef(1.5, 0.4, 0.3);
       drawCube(0.8,0.6,0.3,0.8,0.6,0.3);
       glPopMatrix();

              //glColor3f(0.4,0.4,0.9);
       glPushMatrix();
       glTranslatef(2,-0.48,10);
       glScalef(1.7, 0.38, 0.4);
       drawCube(0.4,0.4,0.9,0.4,0.4,0.9);
       glPopMatrix();

       //glColor3f(0.7,0.4,0.0);
       glPushMatrix();
       glTranslatef(2,0.7,10);
       glScalef(1.7, 0.05, 0.4);
       drawCube(0.7,0.4,0.0,0.7,0.4,0.0);
       glPopMatrix();

       glPushMatrix();
       glTranslatef(-0.2,0.0,2.4);
       glScalef(0.8, 0.8, 0.8);
       fish();
       glPopMatrix();

              glPushMatrix();
       glTranslatef(-1.2,0.0,2.4);
       glScalef(0.8, 0.8, 0.8);
       fish();
       glPopMatrix();

                     glPushMatrix();
       glTranslatef(-2.2,0.0,2.4);
       glScalef(0.8, 0.8, 0.8);
       fish();
       glPopMatrix();

               glPushMatrix();
       glTranslatef(-3.2,0.0,2.4);
       glScalef(0.8, 0.8, 0.8);
       fish();
       glPopMatrix();

             glPushMatrix();
       glTranslatef(0.9,0.0,1.7);
       glScalef(0.8, 0.8, 0.8);
       fish_right();
       glPopMatrix();


}




void setA(int x){
        glPushMatrix();
    glTranslatef(0.09,0,1.3);
    glScalef(0.8, 0.8, 0.8);
    chairfront();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.09,0,2.9);
    glScalef(0.8, 0.8, 0.8);
    chairback();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-0.6,0,2.15);
    glScalef(0.8, 0.8, 0.8);
    chair_right();
    glPopMatrix();

            glPushMatrix();
    glTranslatef(0.8,0,2.15);
    glScalef(0.8, 0.8, 0.8);
    chair_left();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2);
    glScalef(0.8, 0.8, 0.8);
    table();
    glPopMatrix();

    if(x==1){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    burger();
    glPopMatrix();
    }
    else if (x==2){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    pizza();
    glPopMatrix();
    }
    else if (x==3){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    hotdog();
    glPopMatrix();
    }

}

void cellight(){

       glPushMatrix();
       glTranslatef(16,5,10);
       glScalef(0.6, 0.05, 0.3);
       drawCube(0.4,0.4,0.4,0.4,0.4,0.4);
       glPopMatrix();


       glPushMatrix();
       glTranslatef(16.1,4.9,10.17);
       glScalef(0.55, 0.05, 0.2);
       drawCube(1.0,1.0,1.0,1.0,1.0,1.0);
       glPopMatrix();


}

void light0()
{
        glPushMatrix();
    //top right farthest corner
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 5.0, 5.0, -10.0, 1.0 };


glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
glLightfv( GL_LIGHT0, GL_POSITION, light_position);
 glPopMatrix();

}

void light1()
{
        glPushMatrix();
    //top left farthest corner
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.3, 0.3, 0.3, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { -5.0, 5.0, -10.0, 1.0 };



    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);

    GLfloat spot_direction[] ={0.0,-1.0,0.0};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spot_direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45);

    glPopMatrix();

}

void light2()
{
        glPushMatrix();
    //top left near corner
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.05, 0.05, 0.05, 1.0};
    GLfloat light_diffuse[]  = { 1.0, 1.0, 1.0, 1.0 };

    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = {-5.0, 5.0, -7.0, 1.0 };//{ 16.0, 6.0, -16.0, 1.0 };


    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    glPopMatrix();

}

void drawTexturedSphere(GLfloat difX, GLfloat difY, GLfloat difZ, GLfloat ambX, GLfloat ambY, GLfloat ambZ, GLfloat shine = 90) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 3); // Replace 2 with the actual texture ID

    GLfloat no_mat[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat mat_ambient[] = {ambX, ambY, ambZ, 1.0};
    GLfloat mat_diffuse[] = {difX, difY, difZ, 1.0};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {shine};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    for (int i = 0; i < 20; i++) {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= 16; j++) {
            for (int k = 0; k < 2; k++) {
                float u = static_cast<float>(j) / 16.0f;
                float v = static_cast<float>(i + k) / 20.0f;

                float theta = 2.0f * M_PI * u;
                float phi = M_PI * v;

                float x = 3.0f * sin(phi) * cos(theta);
                float y = 3.0f * sin(phi) * sin(theta);
                float z = 3.0f * cos(phi);

                glTexCoord2f(u, v);
                glVertex3f(x, y, z);

                u = static_cast<float>(j) / 16.0f;
                v = static_cast<float>(i + k + 1) / 20.0f;

                theta = 2.0f * M_PI * u;
                phi = M_PI * v;

                x = 3.0f * sin(phi) * cos(theta);
                y = 3.0f * sin(phi) * sin(theta);
                z = 3.0f * cos(phi);

                glTexCoord2f(u, v);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}


void setB(int x){
        glPushMatrix();
    glTranslatef(0.09,0,1.3);
    glScalef(0.8, 0.8, 0.8);
    chairfront();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.09,0,2.9);
    glScalef(0.8, 0.8, 0.8);
    chairback();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-0.6,0,2.15);
    glScalef(0.8, 0.8, 0.8);
    chair_right();
    glPopMatrix();

            glPushMatrix();
    glTranslatef(0.8,0,2.15);
    glScalef(0.8, 0.8, 0.8);
    chair_left();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2);
    glScalef(0.8, 0.8, 0.8);
    table();
    glPopMatrix();

    if(x==1){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    burger();
    glPopMatrix();
    }
    else if (x==2){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    pizza();
    glPopMatrix();
    }
    else if (x==3){
    glPushMatrix();
    glTranslatef(3.28,2.5,8.6);
    glScalef(0.7, 0.7, 0.7);
    hotdog();
    glPopMatrix();
    }
        glPushMatrix();
    glTranslatef(2.2,3.0,7.6);
    glScaled(1.3,0.3,1.3);
    drawpyramid(0.9, 0., 0.1,0.9, 0.0, 0.1,60);
    glPopMatrix();

            glPushMatrix();
    glTranslatef(3.5,-0.2,8.8);
    glScaled(0.05,1.3,0.05);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();

}

void border(){

            glPushMatrix();
    glTranslatef(-20.0,-0.6,11.15);
    glScaled(8.4,0.2,0.05);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();

                glPushMatrix();
    glTranslatef(-20.0,-0.6,-11.15);
    glScaled(8.4,0.2,0.05);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();

                glPushMatrix();
    glTranslatef(-20.0,-0.6,-11);
    glScaled(0.05,0.2,7.4);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();

                    glPushMatrix();
    glTranslatef(5.17,-0.6,-10.9);
    glScaled(0.05,0.2,7.4);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();
}

void grill(){

                        glPushMatrix();
    glTranslatef(-16.0,-0.3,5.0);
    glScaled(0.7,0.1,0.8);
    drawCube(0.3, 0.1, 0.4,0.3, 0.1, 0.4,60);
    glPopMatrix();

                            glPushMatrix();
    glTranslatef(-16.25,-0.0,4.75);
    glScaled(0.9,0.1,1.0);
    drawCube(0.0, 0.0, 0.0,0.0, 0.0, 0.0,60);
    glPopMatrix();
}

void earth(){
        glEnable(GL_TEXTURE_2D);
        glColor3b(0,0,1
                  );
    glutSolidSphere(2,16,16);
        glDisable(GL_TEXTURE_2D);
}


void display(void)


{
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective(90,1,1,100);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ,  refX,refY,refZ,  0,1,0); //7,2,15, 0,0,0, 0,1,0

    glViewport(200, 50, 800, 570);

    base();  // DRAW THE BASE OF THE HOUSE

    glPushMatrix();
    glTranslatef(-1.5,-0.5, -3);
    glScalef(1.2, 1.9, 1.7);
    cupboard();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-1.5,-0.5, 1.9);
    glScalef(1, 1.2, 1.3);
    cupboard();
    glPopMatrix();




    glPushMatrix();
    glTranslatef(-0.6,-0.5,1);
    glScalef(1.2, 1.3, 1.2);
    window_right();
    glPopMatrix();



        glPushMatrix();
    glTranslatef(-0.6,-0.5,-2);
    glScalef(1.2, 1.3, 1.2);
    window_right();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-0.6,-0.5,-5);
    glScalef(1.2, 1.3, 1.2);
    window_right();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(-0.6,-0.5,-8);
    glScalef(1.2, 1.3, 1.2);
    window_right();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1.0,-1.0,-10.2);
    glScalef(1.2, 1.5, 1.2);
    window_left();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(4.0,-1.0,-10.2);
    glScalef(1.2, 1.5, 1.2);
    window_left();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(7.0,-1.0,-10.2);
    glScalef(1.2, 1.5, 1.2);
    window_left();
    glPopMatrix();

        glPushMatrix();
    glTranslatef(10.0,-1.0,-10.2);
    glScalef(1.2, 1.5, 1.2);
    window_left();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(1,-0.5,-1);
    setA(2);
    glPopMatrix();

        glPushMatrix();
    glTranslatef(1,-0.5,2);
    setA(1);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(1,-0.5,-4);
    setA(3);
    glPopMatrix();

        glPushMatrix();
    glTranslatef(4,-0.5,-1);
    setA(1);
    glPopMatrix();

        glPushMatrix();
    glTranslatef(4,-0.5,2);
    setA(2);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(4,-0.5,-4);
    setA(3);
    glPopMatrix();

            glPushMatrix();
    glTranslatef(7,-0.5,-1);
    setA(3);
    glPopMatrix();

        glPushMatrix();
    glTranslatef(7,-0.5,2);
    setA(2);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(7,-0.5,-4);
    setA(1);
    glPopMatrix();

    ////////////////////////////////////////




        glPushMatrix();
    glTranslatef(2,5.5,2);
    setB(2);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(2,5.5,-4);
    setB(1);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(7,5.5,2);
    setB(2);
    glPopMatrix();


        glPushMatrix();
    glTranslatef(7,5.5,-4);
    setB(1);
    glPopMatrix();



        glPushMatrix();
    glTranslatef(-1.6,0,10.5);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

            glPushMatrix();
    glTranslatef(-1.6,0,13.3);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();


                    glPushMatrix();
    glTranslatef(4.7,0,0.7);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

        glTranslatef(7.7,0,0.7);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

            glTranslatef(2.7,0,0.0);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

                glTranslatef(-9.0,0.0,0.0);
    glScalef(1.0, 1.1, 1.15);//(0.04, 0.6, 0.0001);
    bar();
    glPopMatrix();

                    glTranslatef(3.0,2.6,7.0);
    glScalef(0.8, 0.8, 0.8);//(0.04, 0.6, 0.0001);
    fan();
    glPopMatrix();

                        glTranslatef(6.0,0.1,0.07);
    glScalef(0.8, 0.8, 0.8);//(0.04, 0.6, 0.0001);
    fan();
    glPopMatrix();

                        glTranslatef(-7.2,-0.1,-5.0);
    glScalef(1.2, 1.2, 1.2);//(0.04, 0.6, 0.0001);
    fan();
    glPopMatrix();

                            glTranslatef(5.8,0.0,0.1);
    glScalef(1, 1, 1);//(0.04, 0.6, 0.0001);
    fan();
    glPopMatrix();


    glTranslatef(-9.5,-0.3,6.0);
    glScalef(0.9, 0.9, 0.9);//(0.04, 0.6, 0.0001);
    burger();
    glPopMatrix();


    glTranslatef(-0.01,-0.1,-2.0);
    glScalef(0.95, 0.95, 0.95);//(0.04, 0.6, 0.0001);
    pizza();
    glPopMatrix();

        glTranslatef(-0.01,-0.1,-2.0);
    glScalef(0.95, 0.95, 0.95);//(0.04, 0.6, 0.0001);
    hotdog();
    glPopMatrix();

            glTranslatef(-0.01,-3.5,-2.0);
    glScalef(0.95, 0.95, 0.95);//(0.04, 0.6, 0.0001);
    bottle();
    glPopMatrix();

            glPushMatrix();
    glTranslatef(15.0,-0.5,11.0);
    glScalef(1.2, 1.2, 1.2);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

                glPushMatrix();
    glTranslatef(1.0,-0.8,-9.0);
    glScalef(1.0, 1.0, 1.0);//(0.04, 0.6, 0.0001);
    fridge();
    glPopMatrix();

                    glPushMatrix();
    glTranslatef(1.0,1.0,1.0);
    glScalef(1.0, 1.0, 1.0);//(0.04, 0.6, 0.0001);
    aqua();
    glPopMatrix();

    //glPushMatrix();
    //glTranslatef(-2.0,5.0,10.0);
    //glScalef(0.33, 0.33, 0.33);
    //drawCube(1,0,0,1,0,0);
    //glPopMatrix();

    //light1
    glPushMatrix();
    glTranslatef(0.0,1.0,-12.0);
    cellight();
    glPopMatrix();


    //light0
        glPushMatrix();
    glTranslatef(-17.0,1.0,-12.0);
    cellight();
    glPopMatrix();


    //light2
    glPushMatrix();
    glTranslatef(-17.0,1.0,1.0);
    cellight();
    glPopMatrix();


        glTranslatef(6.5,7.5,11);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();


        glTranslatef(8.0,0,0);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

            glTranslatef(-7.8,0,-9);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

                glTranslatef(7.0,0,0.0);
    glScalef(1.0, 1.1, 1.0);//(0.04, 0.6, 0.0001);
    tree();
    glPopMatrix();

    glPushMatrix();
    border();
    glPopMatrix();

    //glPushMatrix();
    //glScaled(0.8,0.8,0.8);
    //grill();
    //glPopMatrix();





    glFlush();
    glutSwapBuffers();
}

void myKeyboardFunc( unsigned char key, int x, int y )
{

    switch ( key )
    {
    case 'w': // move eye point upwards along Y axis
        eyeY+=1.0;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 's': // move eye point downwards along Y axis
        eyeY-=1.0;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 'a': // move eye point left along X axis
        eyeX-=1.0;
        refX-=1.0;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 'd': // move eye point right along X axis
        eyeX+=1.0;
        refX+=1.0;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 'o':  //zoom out
        eyeZ+=1;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 'i': //zoom in
        eyeZ-=1;
         std::cout<<"X:"<<eyeX<<","<<"Y:"<<eyeY<<","<<"Z:"<<eyeZ<<","<<std::endl;
        break;
    case 'q': //back to default eye point and ref point
            eyeX=16.0; eyeY=4.0; eyeZ=18.0;
            refX=0.0; refY=0.0; refZ=0.0;
        break;
    case 'j': // move ref point upwards along Y axis
        refY+=1.0;
        break;
    case 'n': // move ref point downwards along Y axis
        refY-=1.0;
        break;
    case 'b': // move ref point left along X axis
        refX-=1.0;
        break;
    case 'm': // move eye point right along X axis
        refX+=1.0;
        break;
    case 'k':  //move ref point away from screen/ along z axis
        refZ+=1;
        break;
    case '0': //move ref point towards screen/ along z axis
        refZ-=1;
        break;
 case '1': //to turn on and off light one
            if(switchOne == false)
            {
                switchOne = true;
                glEnable( GL_LIGHT0); break;
            }
            else if(switchOne == true)
            {
                switchOne = false;
                 glDisable( GL_LIGHT0); break;
            }
        case '2': //to turn on and off light two
            if(switchTwo == false)
            {
                switchTwo = true;
                glEnable( GL_LIGHT1); break;
            }
            else if(switchTwo == true)
            {
                switchTwo = false;
                glDisable( GL_LIGHT1); break;
            }
        case '3': //to turn on and off light one
            if(switchThree == false)
            {
                switchThree = true;
                glEnable( GL_LIGHT2); break;
            }
            else if(switchThree == true)
            {
                switchThree = false;
                glDisable( GL_LIGHT2); break;
            }
    case '4': //move ref point towards screen/ along z axis
        eyeX=3.0; eyeY=3.0; eyeZ=11.0;
        break;
    case '5': //move ref point towards screen/ along z axis
        eyeX=3.0; eyeY=3.0; eyeZ=9.0;
        break;
    case '6': //move ref point towards screen/ along z axis
        eyeX=3.0; eyeY=3.0; eyeZ=8.0;
        break;
    case '7': //move ref point towards screen/ along z axis
        eyeX=5.0; eyeY=3.0; eyeZ=13.0;
        break;
    case '8': //move ref point towards screen/ along z axis
        eyeX=8.0; eyeY=3.0; eyeZ=18.0;
        break;
    case '9': //move ref point towards screen/ along z axis
        eyeX=12.0; eyeY=3.0; eyeZ=16.0;
        break;

    case 27:    // Escape key
        exit(1);
    }

    glutPostRedisplay();
}


void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

int main (int argc, char **argv)
{
     glutInit(&argc, argv);
      std::cout<<"To move Eye point:"<< std::endl;
    std::cout<<"w: up"<<std::endl;
    std::cout<<"s: down"<<std::endl;
    std::cout<<"a: left"<<std::endl;
    std::cout<<"d: right"<<std::endl;
    std::cout<<"i: zoom in"<<std::endl;
    std::cout<<"o: zoom out"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"To move Camera point:"<< std::endl;
    std::cout<<"j: up"<<std::endl;
    std::cout<<"n: down"<<std::endl;
    std::cout<<"b: left"<<std::endl;
    std::cout<<"m: right"<<std::endl;
    std::cout<<"l: move nearer"<<std::endl;
    std::cout<<"k: move far"<<std::endl;
    std::cout<<"      "<<std::endl;
    std::cout<<"Press q to move to default position"<<std::endl;
    std::cout<<"      "<<std::endl;
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); glutInitWindowPosition(100,100);
     glutInitWindowSize(windowWidth, windowHeight);
     glutCreateWindow("Traingle-Demo");


    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\wood1.bmp");
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\wood2.bmp");
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\metal.bmp");
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\tree.bmp");
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\pot.bmp");
    LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\wht.bmp");
        LoadTexture("C:\\Users\\A.Dhar\\Desktop\\prototype_back\\bmp\\glass.bmp");








          glutDisplayFunc(display);
     glutKeyboardFunc(myKeyboardFunc);
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable( GL_LIGHT0);
    glEnable( GL_LIGHT1);
    glEnable( GL_LIGHT2);
    light0();
    light1();
    light2();


     glutMainLoop();
     return 0;
}
