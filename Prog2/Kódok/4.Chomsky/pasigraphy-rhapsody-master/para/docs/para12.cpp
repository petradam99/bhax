// Esport Language (PaRa), first experiments
// This is a rapid prototype for planning Pasigraphy Rhapsody (Paszigráfia Rapszódia, PaRa)
//
// para12.cpp
//
// Copyright (C) 2019 Norbert Bátfai, nbatfa@gmail.com, batfai.norbert@inf.unideb.hu
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
// Version history
//
// Initial hack
//
// g++ para12.cpp -o para -lboost_system -lGL -lGLU -lglut -I/usr/include/SDL2 -lSDL2 -lSDL2_image
//
// ./para 3:2:1:1:0:3:2:1:0:2:0:2:1:1:0:3:3:0:2:0:1:1:0:1:0:1:0:1:0:2:2:0:1:1:1:3:2:1:0:2:0:2:1:1:1:2:3:0:1:1:1:1:0:3:3:0:1:0:2:1:0:1:0:2:2:0:0:0:1:3:1:0:1:3:2:1:0:2:0:3:3:0:1:0:2:1:0 cube1.png cube2.png cube3.png cube4.png cube5.png cube6.png
//
// ./para 9:2:1:1:0:3:2:1:0:2:0:2:1:1:0:3:3:0:2:0:1:1:0:1:0:1:0:1:0:2:2:0:1:1:1:3:2:1:0:2:0:2:1:1:1:2:3:0:1:1:1:1:0:3:3:0:1:0:2:1:0:1:0:2:2:0:0:0:1:3:1:0:1:3:2:1:0:2:0:3:3:0:1:0:2:1:0:2:1:1:0:3:2:1:0:2:0:2:1:1:0:3:3:0:2:0:1:1:0:1:0:1:0:1:0:2:2:0:1:1:1:3:2:1:0:2:0:2:1:1:1:2:3:0:1:1:1:1:0:3:3:0:1:0:2:1:0:1:0:2:2:0:0:0:1:3:1:0:1:3:2:1:0:2:0:3:3:0:1:0:2:1:0:2:1:1:0:3:2:1:0:2:0:2:1:1:0:3:3:0:2:0:1:1:0:1:0:1:0:1:0:2:2:0:1:1:1:3:2:1:0:2:0:2:1:1:1:2:3:0:1:1:1:1:0:3:3:0:1:0:2:1:0:1:0:2:2:0:0:0:1:3:1:0:1:3:2:1:0:2:0:3:3:0:1:0:2:1:0 cube1.png cube2.png cube3.png cube4.png cube5.png cube6.png
//

#include <iostream>
#include <vector>
#include <boost/tokenizer.hpp>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class PaRaCube
{
public:
        GLfloat x = 0.0f;
        GLfloat y = 0.0f;
        GLfloat z = 0.0f;
        GLfloat rotx = 0.0f;
        GLfloat roty = 0.0f;
        GLfloat rotz = 0.0f;
        int nn[6]  = {1,2,3,4,8,10};
        int tex[6]  = {-1,-1,-1,-1,-1,-1};
        std::vector<int> cc[6];
};

int wid;
int selectedCube = 0;
bool selectc {true};
bool transp {false};
bool pic {true};
bool mousec {true};
bool mousefc {false};
bool fullscr {false};
GLdouble fovy = 70;
int width = 640;
int height = 480;
int oldmx, oldmy;

GLfloat x = 0.0f, y = 1.0f, z = 8.0f;
GLfloat yy = 3.0f;
GLfloat a = 90.0f;
const float Pi = 3.1415926535f;

std::vector<PaRaCube> cubeLetters;

GLuint  texture[6];

void start()
{
        a=0.0f;
        x=0.0f;
        y=1.0f;
        z=8.0f;
        fovy = 70;
}

void texs ( int noftex, char* names[] )
{

        SDL_Surface *tex [noftex];

        glGenTextures ( noftex, texture );

        for ( int i = 0; i < noftex; i++ ) {

                tex[i] = IMG_Load ( names[i] );
                if ( !tex[i] )
                        std::cout << IMG_GetError() << std::endl;

                std::cout << i << " " << names[i] << " " << tex[i]->w << " " << tex[i]->h << std::endl;

                glBindTexture ( GL_TEXTURE_2D, texture[i] );

                glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
                glTexParameteri ( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST );

                glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGB, tex[i]->w, tex[i]->h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex[i]-> pixels );

                SDL_FreeSurface ( tex[i] );
        }

}

void drawPaRaCube ( int idx )
{

        glPushMatrix();

        glTranslatef ( cubeLetters[idx].x, cubeLetters[idx].y, cubeLetters[idx].z );

        glRotatef ( cubeLetters[idx].rotx, 1.0f, 0.0f, 0.0f );
        glRotatef ( cubeLetters[idx].roty, 0.0f, 1.0f, 0.0f );
        glRotatef ( cubeLetters[idx].rotz, 0.0f, 0.0f, 1.0f );

        if ( pic ) if ( cubeLetters[idx].tex[0] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[0]] );

        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[0] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[0] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( 1.0f, 1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[0] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 1.0f,-1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[0] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( -1.0f,-1.0f, 1.0f );


        glEnd();
        if ( pic ) if ( cubeLetters[idx].tex[1] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[1]] );
        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[1] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( 1.0f, 1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[1] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( 1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[1] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 1.0f,-1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[1] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( 1.0f,-1.0f, 1.0f );

        glEnd();
        if ( pic ) if ( cubeLetters[idx].tex[2] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[2]] );
        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[2] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[2] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[2] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[2] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( 1.0f, 1.0f, 1.0f );

        glEnd();
        if ( pic ) if ( cubeLetters[idx].tex[3] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[3]] );
        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[3] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[3] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[3] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( -1.0f,-1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[3] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( -1.0f,-1.0f, 1.0f );

        glEnd();
        if ( pic ) if ( cubeLetters[idx].tex[4] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[4]] );
        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[4] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[4] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( 1.0f, 1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[4] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 1.0f,-1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[4] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( -1.0f,-1.0f,-1.0f );

        glEnd();
        if ( pic ) if ( cubeLetters[idx].tex[5] != -1 )
                        glBindTexture ( GL_TEXTURE_2D, texture[cubeLetters[idx].tex[5]] );
        glBegin ( GL_QUADS );

        glColor3f ( 0.818f, .900f, 0.824f );

        if ( pic ) if ( cubeLetters[idx].tex[5] != -1 ) glTexCoord2f ( 0.0f, 1.0f );
        glVertex3f ( -1.0f,-1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[5] != -1 ) glTexCoord2f ( 1.0f, 1.0f );
        glVertex3f ( 1.0f,-1.0f, 1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[5] != -1 ) glTexCoord2f ( 1.0f, 0.0f );
        glVertex3f ( 1.0f,-1.0f,-1.0f );
        if ( pic ) if ( cubeLetters[idx].tex[5] != -1 ) glTexCoord2f ( 0.0f, 0.0f );
        glVertex3f ( -1.0f,-1.0f,-1.0f );

        glEnd();

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[0]; i++ ) {

                glVertex3f ( -1.0f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[0] ), 1.005f );
                glVertex3f ( 1.0f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[0] ), 1.005f );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[0]; i++ ) {

                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[0] ), 1.0f , 1.005f );
                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[0] ), -1.0f , 1.005f );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[0].size() /2; ++i ) {
                glBegin ( GL_QUADS );

                glColor3f ( .82f, .15f, .15f );

                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[0][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[0] ),
                             1.0f- ( cubeLetters[idx].cc[0][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[0] ), 1.002f );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[0][2*i]* ( 2.0/cubeLetters[idx].nn[0] ),
                             1.0f- ( cubeLetters[idx].cc[0][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[0] ), 1.002f );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[0][2*i]* ( 2.0/cubeLetters[idx].nn[0] ),
                             1.0f-cubeLetters[idx].cc[0][2*i+1]* ( 2.0/cubeLetters[idx].nn[0] ), 1.002f );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[0][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[0] ),
                             1.0f-cubeLetters[idx].cc[0][2*i+1]* ( 2.0/cubeLetters[idx].nn[0] ), 1.002f );

                glEnd();
        }

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[1]; i++ ) {

                glVertex3f ( 1.005f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[1] ), 1.0f );
                glVertex3f ( 1.005f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[1] ), -1.0f );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[1]; i++ ) {

                glVertex3f ( 1.005f, 1.0f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[1] ) );
                glVertex3f ( 1.005f, -1.0f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[1] ) );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[1].size() /2; ++i ) {
                glBegin ( GL_QUADS );

                glColor3f ( 0.15f, .29f, .82f );

                glVertex3f ( 1.002f, 1.0f-cubeLetters[idx].cc[1][2*i]* ( 2.0/cubeLetters[idx].nn[1] ),
                             1.0f- ( cubeLetters[idx].cc[1][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[1] ) );
                glVertex3f ( 1.002f, 1.0f-cubeLetters[idx].cc[1][2*i]* ( 2.0/cubeLetters[idx].nn[1] ),
                             1.0f-cubeLetters[idx].cc[1][2*i+1]* ( 2.0/cubeLetters[idx].nn[1] ) );
                glVertex3f ( 1.002f, 1.0f- ( cubeLetters[idx].cc[1][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[1] ),
                             1.0f-cubeLetters[idx].cc[1][2*i+1]* ( 2.0/cubeLetters[idx].nn[1] ) );
                glVertex3f ( 1.002f, 1.0f- ( cubeLetters[idx].cc[1][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[1] ),
                             1.0f- ( cubeLetters[idx].cc[1][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[1] ) );

                glEnd();
        }

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[2]; i++ ) {

                glVertex3f ( -1.0f, 1.005f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[2] ) );
                glVertex3f ( 1.0f, 1.005f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[2] ) );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[2]; i++ ) {

                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[2] ), 1.005f, -1.0f );
                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[2] ), 1.005f, 1.0f );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[2].size() /2; ++i ) {
                glBegin ( GL_QUADS );

                glColor3f ( .309f, .820f, .150f );

                glVertex3f ( 1.0f-cubeLetters[idx].cc[2][2*i]* ( 2.0/cubeLetters[idx].nn[2] ),
                             1.002f , 1.0f-cubeLetters[idx].cc[2][2*i+1]* ( 2.0/cubeLetters[idx].nn[2] ) );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[2][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[2] ),
                             1.002f , 1.0f-cubeLetters[idx].cc[2][2*i+1]* ( 2.0/cubeLetters[idx].nn[2] ) );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[2][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[2] ),
                             1.002f , 1.0f- ( cubeLetters[idx].cc[2][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[2] ) );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[2][2*i]* ( 2.0/cubeLetters[idx].nn[2] ),
                             1.002f , 1.0f- ( cubeLetters[idx].cc[2][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[2] ) );

                glEnd();
        }

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[3]; i++ ) {

                glVertex3f ( -1.005f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[3] ), 1.0f );
                glVertex3f ( -1.005f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[3] ), -1.0f );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[3]; i++ ) {

                glVertex3f ( -1.005f, 1.0f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[3] ) );
                glVertex3f ( -1.005f, -1.0f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[3] ) );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[3].size() /2; ++i ) {
                glBegin ( GL_QUADS );
                glColor3f ( .804f, .820f, .150f );

                glVertex3f ( -1.002f, 1.0f- ( cubeLetters[idx].cc[3][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[3] ),
                             1.0f-cubeLetters[idx].cc[3][2*i+1]* ( 2.0/cubeLetters[idx].nn[3] ) );
                glVertex3f ( -1.002f, 1.0f-cubeLetters[idx].cc[3][2*i]* ( 2.0/cubeLetters[idx].nn[3] ),
                             1.0f-cubeLetters[idx].cc[3][2*i+1]* ( 2.0/cubeLetters[idx].nn[3] ) );
                glVertex3f ( -1.002f, 1.0f-cubeLetters[idx].cc[3][2*i]* ( 2.0/cubeLetters[idx].nn[3] ),
                             1.0f- ( cubeLetters[idx].cc[3][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[3] ) );
                glVertex3f ( -1.002f, 1.0f- ( cubeLetters[idx].cc[3][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[3] ),
                             1.0f- ( cubeLetters[idx].cc[3][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[3] ) );

                glEnd();
        }

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[4]; i++ ) {

                glVertex3f ( -1.0f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[4] ), -1.005f );
                glVertex3f ( 1.0f, 1.0f-i* ( 2.0/cubeLetters[idx].nn[4] ), -1.005f );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[4]; i++ ) {

                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[4] ), 1.0f , -1.005f );
                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[4] ), -1.0f , -1.005f );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[4].size() /2; ++i ) {
                glBegin ( GL_QUADS );
                glColor3f ( .614f, 0.150f, 0.820f );

                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[4][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[4] ),
                             1.0f-cubeLetters[idx].cc[4][2*i+1]* ( 2.0/cubeLetters[idx].nn[4] ), -1.002f );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[4][2*i]* ( 2.0/cubeLetters[idx].nn[4] ),
                             1.0f-cubeLetters[idx].cc[4][2*i+1]* ( 2.0/cubeLetters[idx].nn[4] ), -1.002f );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[4][2*i]* ( 2.0/cubeLetters[idx].nn[4] ),
                             1.0f- ( cubeLetters[idx].cc[4][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[4] ), -1.002f );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[4][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[4] ),
                             1.0f- ( cubeLetters[idx].cc[4][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[4] ), -1.002f );

                glEnd();
        }

        glBegin ( GL_LINES );
        glColor3f ( .188f, 0.209f, 0.190f );

        for ( int i=0; i<=cubeLetters[idx].nn[5]; i++ ) {

                glVertex3f ( -1.0f, -1.005f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[5] ) );
                glVertex3f ( 1.0f, -1.005f , 1.0f-i* ( 2.0/cubeLetters[idx].nn[5] ) );
        }
        for ( int i=0; i<=cubeLetters[idx].nn[5]; i++ ) {

                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[5] ), -1.005f , 1.0f );
                glVertex3f ( 1.0f-i* ( 2.0/cubeLetters[idx].nn[5] ), -1.005f , -1.0f );

        }
        glEnd();

        for ( int i {0}; i<cubeLetters[idx].cc[5].size() /2; ++i ) {
                glBegin ( GL_QUADS );
                glColor3f ( .114f, .108f, .156f );

                glVertex3f ( 1.0f-cubeLetters[idx].cc[5][2*i]* ( 2.0/cubeLetters[idx].nn[5] ),
                             -1.002f , 1.0f-cubeLetters[idx].cc[5][2*i+1]* ( 2.0/cubeLetters[idx].nn[5] ) );
                glVertex3f ( 1.0f-cubeLetters[idx].cc[5][2*i]* ( 2.0/cubeLetters[idx].nn[5] ),
                             -1.002f , 1.0f- ( cubeLetters[idx].cc[5][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[5] ) );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[5][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[5] ),
                             -1.002f , 1.0f- ( cubeLetters[idx].cc[5][2*i+1]+1 ) * ( 2.0/cubeLetters[idx].nn[5] ) );
                glVertex3f ( 1.0f- ( cubeLetters[idx].cc[5][2*i]+1 ) * ( 2.0/cubeLetters[idx].nn[5] ),
                             -1.002f , 1.0f-cubeLetters[idx].cc[5][2*i+1]* ( 2.0/cubeLetters[idx].nn[5] ) );

                glEnd();
        }

        glPopMatrix();

}

void draw ( void )
{
        glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );

        if ( transp )
                glDisable ( GL_DEPTH_TEST );
        else
                glEnable ( GL_DEPTH_TEST );

        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glMatrixMode ( GL_MODELVIEW );
        glLoadIdentity();

        gluLookAt ( x + ( 2.0*cos ( a*Pi/180.0 ) ),
                    yy,
                    z - ( 2.0*sin ( ( a ) *Pi/180.0 ) ),
                    x + ( 8.0*cos ( a*Pi/180.0 ) ),
                    y,
                    z - ( 8.0*sin ( ( a ) *Pi/180.0 ) ),
                    0.0f, 1.0f, 0.0f );

        glPushMatrix();

        glColor3f ( .9,.9,.4 );
        glBegin ( GL_QUADS );

        glVertex3f ( -101,-1-0.002, -101 );
        glVertex3f ( -101,-1-0.002,101 );
        glVertex3f ( 101,-1-0.002,101 );
        glVertex3f ( 101,-1-0.002, -101 );

        glEnd();

        for ( int f=0; f<1; f+=2 )
                for ( int i=-101; i<=101; i+=2 )
                        for ( int j=-101; j<=101; j+=2 ) {
                                if ( ( i/2+j/2 ) %2 ) {
                                        glColor3f ( .7,.8,.3 );
                                } else {
                                        glColor3f ( .7, .5,.3 );
                                };

                                glBegin ( GL_QUADS );

                                glVertex3f ( i,-1+f,j );
                                glVertex3f ( i+1.5,-1+f,j );
                                glVertex3f ( i+1.5,-1+f,j+1.5 );
                                glVertex3f ( i,-1+f,j+1.5 );

                                glEnd();

                        };

        glBegin ( GL_LINES );

        for ( int f=-1; f<10; f+=2 )
                for ( int i=-101; i<=101; i+=2 )
                        for ( int j=-101; j<=101; j+=2 ) {
                                glColor3f ( .3, .3,.2+f*.1 );

                                glVertex3f ( i,-1+f,-101 );
                                glVertex3f ( i,-1+f,101 );

                                glVertex3f ( -101,-1+f,i );
                                glVertex3f ( 101,-1+f,i );

                        };

        glEnd();

        glPopMatrix();

        for ( int i {0}; i<cubeLetters.size(); ++i )
                if ( i == selectedCube ) {
                        drawPaRaCube ( i );
                } else {
                        drawPaRaCube ( i );
                }

        glutSwapBuffers();

}

void sel()
{

        float s=10000.0;

        for ( auto & letter : cubeLetters ) {

                float cx = x + ( 3.0*cos ( a*Pi/180.0 ) );
                float cy = y;
                float cz = z - ( 3.0*sin ( ( a ) *Pi/180.0 ) );

                float d = ( letter.x-cx ) * ( letter.x-cx )+
                          ( letter.y-cy ) * ( letter.y-cy )+
                          ( letter.z-cz ) * ( letter.z-cz );

                if ( d < s ) {
                        s = d;
                        selectedCube = &letter - &cubeLetters[0];
                }

        }

}

void w()
{
        x+= ( .3*cos ( a * Pi/180.0 ) );
        z-= ( .3*sin ( a * Pi/180.0 ) );

        if ( selectc )
                sel();
}

void s()
{
        x-= ( .3*cos ( a * Pi/180.0 ) );
        z+= ( .3*sin ( a * Pi/180.0 ) );

        if ( selectc )
                sel();
}

void keyboard ( unsigned char key, int keyx, int keyy )
{
        if ( key == '0' ) {
                selectedCube=0;
        } else if ( key == '1' ) {
                selectedCube=1;
        } else if ( key == '2' ) {
                selectedCube=2;
        } else if ( key == '3' ) {
                selectedCube=3;
        } else if ( key == '4' ) {
                selectedCube=4;
        } else if ( key == '5' ) {
                selectedCube=5;
        } else if ( key == '6' ) {
                selectedCube=6;
        } else if ( key == 't' ) {
                transp = !transp;
        } else if ( key == 'p' ) {
                pic = !pic;
        } else if ( key == 'm' ) {
                mousec = !mousec;
        } else if ( key == 'o' ) {
                mousefc = !mousefc;
        } else if ( key == 'f' ) {
                fullscr = !fullscr;
                if ( fullscr )
                        glutFullScreen();
                else {
                        glutReshapeWindow ( width, height );
                        glutPositionWindow ( 0,0 );
                }
        } else if ( key == 'w' ) {
                w();
        } else if ( key == 's' ) {
                s();
        } else if ( key == 'a' ) {
                a+=2.0f;
        } else if ( key == 'd' ) {
                a-=2.0f;
        } else if ( key == 'q' ) {
                yy-=1.0f;
                y-=1.0f;
        } else if ( key == 'e' ) {
                yy+=1.0f;
                y+=1.0f;
        } else if ( key == 'r' ) {

                start();

                glMatrixMode ( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective ( fovy, ( float ) width / ( float ) height, .1f, 1000.0f );
                glMatrixMode ( GL_MODELVIEW );

        } else if ( key == '-' ) {
                ++fovy;

                glMatrixMode ( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective ( fovy, ( float ) width / ( float ) height, .1f, 1000.0f );
                glMatrixMode ( GL_MODELVIEW );

        } else if ( key == '+' ) {
                --fovy;

                glMatrixMode ( GL_PROJECTION );
                glLoadIdentity();
                gluPerspective ( fovy, ( float ) width / ( float ) height, .1f, 1000.0f );
                glMatrixMode ( GL_MODELVIEW );

        } else if ( key == 27 ) {

                glutDestroyWindow ( wid );

        }

        if ( glutGetWindow() )
                glutPostRedisplay();

}

void skeyboard ( int key, int keyx, int keyy )
{
        if ( key == GLUT_KEY_UP ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        //w();
                        y += .5f;
                else
                        cubeLetters[selectedCube].rotx += 5.0;
        } else if ( key == GLUT_KEY_DOWN ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        //s();
                        y -= .5f;
                else
                        cubeLetters[selectedCube].rotx -= 5.0;
        } else if ( key == GLUT_KEY_RIGHT ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        a-=2.0f;
                else
                        cubeLetters[selectedCube].roty -= 5.0;
        } else if ( key == GLUT_KEY_LEFT ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        a+=2.0f;
                else
                        cubeLetters[selectedCube].roty += 5.0;
        } else if ( key == GLUT_KEY_PAGE_UP ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        y += .5f;
                else
                        cubeLetters[selectedCube].rotz += 5.0;
        } else if ( key == GLUT_KEY_PAGE_DOWN ) {
                if ( glutGetModifiers() ==  GLUT_ACTIVE_SHIFT )
                        y -= .5f;
                else
                        cubeLetters[selectedCube].rotz -= 5.0;
        }

        glutPostRedisplay();
}

void mouse ( int keyx, int keyy )
{

        if ( !mousec )
                return;

        if ( keyx > oldmx )
                a-=2.0f;
        else if ( keyx < oldmx )
                a+=2.0f;

        if ( mousefc ) {
                if ( keyy > oldmy )
                        s();
                else if ( keyy < oldmy )
                        w();
        }

        oldmx = keyx;
        oldmy = keyy;

        glutPostRedisplay();

}


void click ( int button, int action, int keyx, int keyy )
{

        if ( button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
                mousec = !mousec;
        }

        glutPostRedisplay();

}

void reshape ( int w, int h )
{
        width = w;
        height = h;

        glMatrixMode ( GL_PROJECTION );
        glLoadIdentity();
        gluPerspective ( fovy, ( float ) w / ( float ) h, .1f, 1000.0f );
        glViewport ( 0, 0, w, h );
        glMatrixMode ( GL_MODELVIEW );
}

int
main ( int argc, char *argv[] )
{

        for ( int i {1}; i<argc; ++i ) {
                std::string s ( argv[i] );
                std::vector<int> nums;
                boost::char_separator<char> separator ( ":" );
                boost::tokenizer<boost::char_separator<char>> items ( s, separator );

                for ( const auto& token : items )
                        nums.push_back ( atoi ( token.c_str() ) );

                int ii=0;
                for ( int cui {0}; cui<nums[0]; ++cui ) {
                        PaRaCube prc;
                        for ( int s {0}; s<6; ++s ) {
                                ++ii;
                                prc.nn[s]=nums[ii];
                                ++ii;
                                int noc = nums[ii];
                                for ( int coi {0}; coi<noc; ++coi ) {
                                        ++ii;
                                        prc.cc[s].push_back ( nums[ii] );
                                        ++ii;
                                        prc.cc[s].push_back ( nums[ii] );
                                }
                        }

                        cubeLetters.push_back ( prc );

                }

        }


        cubeLetters[0].tex[0] = 3;
        cubeLetters[0].tex[1] = 4;
        cubeLetters[0].tex[2] = 5;
        cubeLetters[1].tex[0] = 1;
        cubeLetters[1].tex[1] = 0;
        cubeLetters[1].tex[4] = 2;
        cubeLetters[1].tex[5] = 1;
        cubeLetters[2].tex[1] = 2;
        cubeLetters[2].tex[2] = 5;


        int x=0, y=0, z=0, c=0;
        for ( auto & letter : cubeLetters ) {

                letter.x = 3.0f*x;
                letter.y = 3.0f*y;
                letter.z = 3.0f*z;

                if ( c%3==0 )
                        x = ( x+1 ) %3;
                else if ( c%3==1 )
                        y = ( y+1 ) %3;
                else if ( c%3==2 )
                        z = ( z+1 ) %3;
                ++c;
        }

        std::cout << std::endl;

        std::cout << "Esport Language (Pasigraphy Rhapsody, Paszigráfia Rapszódia, PaRa)" << std::endl
                  << "Copyright (C) 2019 Norbert Bátfai" << std::endl
                  << "License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>" << std::endl
                  << "This is free software: you are free to change and redistribute it." << std::endl
                  << "There is NO WARRANTY, to the extent permitted by law." << std::endl;

        std::cout << std::endl;

        std::cout << "Cursor(<-,up, down,->),PgUp,Dn rotate the selected cube letter." << std::endl
                  << "W,A,S,D - move the observer, Q,E step between floors." << std::endl
                  << "Shift+Cursor(<-,->) turn the observer like A and D." << std::endl
                  << "Shift+(Cursor(up,down),PgUp,Dn) turn the head of the observer up and down." << std::endl
                  << "Mouse(<-,->) turn the observer like A and D." << std::endl
                  << "+,- zoom in/out" << std::endl
                  << "f switches on/off full screen mode" << std::endl
                  << "o switches on/off Mouse(up,down)" << std::endl
                  << "m or Mouse(left click) switch on/off mouse ctrl" << std::endl
                  << "ESC exits" << std::endl;

        std::cout << std::endl;

        glutInit ( &argc, argv );
        glutInitWindowSize ( width, height );
        glutInitWindowPosition (
                ( glutGet ( GLUT_SCREEN_WIDTH )-width ) /2,
                ( glutGet ( GLUT_SCREEN_HEIGHT )-height ) /2 );
        glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
        wid = glutCreateWindow ( "Pasigraphy Rhapsody, para12, exp4" );

        glClearColor ( 0.0f,0.0f,0.0f,0.5f );
        glClearDepth ( 1.0f );
        glEnable ( GL_DEPTH_TEST );
        glDepthFunc ( GL_LEQUAL );
        glHint ( GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST );
        glEnable ( GL_TEXTURE_2D );
        glEnable ( GL_DEPTH_TEST );
        glShadeModel ( GL_SMOOTH );
        glShadeModel ( GL_FLAT );

        texs ( 6, argv+2 );

        glutReshapeFunc ( reshape );
        glutDisplayFunc ( draw );
        glutKeyboardFunc ( keyboard );
        glutSpecialFunc ( skeyboard );
        glutPassiveMotionFunc ( mouse );
        glutMouseFunc ( click );

        glutMainLoop();
        return 0;
}

