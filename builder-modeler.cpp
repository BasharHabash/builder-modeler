#include <iostream>
#include <GL/glut.h>
#include "builder-modeler.h"

int cx = 0, cy = 0, cz = 0; /* cursor x,y,z */
int ci = 0;                 /* cursor index */

Wall W[1000]; /* total drawable walls */
Marker M[3];  /* cursor coordinates */

void add_wall()
{
	W[0].pos++;
	if (W[0].pos > 4)
		W[0].pos = 1;

	switch (W[0].pos) {
		case 1:
			ci++;

			W[ci].x1 = cx;
			W[ci].y1 = cy;
			W[ci].z1 = cz;
			M[0].x = cx;
			M[0].y = cy;
			M[0].z = cz;
		case 2:
			W[ci].x2 = cx;
			W[ci].y2 = cy;
			W[ci].z2 = cz;
			M[1].x = cx;
			M[1].y = cy;
			M[1].z = cz;
		case 3:
			W[ci].x3 = cx;
			W[ci].y3 = cy;
			W[ci].z3 = cz;
			M[2].x = cx;
			M[2].y = cy;
			M[2].z = cz;
		case 4:
			W[ci].x4 = cx;
			W[ci].y4 = cy;
			W[ci].z4 = cz;
	}

	if (W[0].pos > 3)
		clear_markers();
}

void clear_markers()
{
	M[0].x = 0;
	M[0].y = 0;
	M[0].z = 0;
	M[1].x = 0;
	M[1].y = 0;
	M[1].z = 0;
	M[2].x = 0;
	M[2].y = 0;
	M[2].z = 0;
	W[0].pos = 0;
}

void undo_last_wall(int index) {
	W[index].b = 0;
	W[index].g = 0;
	W[index].r = 0;
	W[index].pos = 0;
	W[index].x1 = 0;
	W[index].x2 = 0;
	W[index].x3 = 0;
	W[index].x4 = 0;
	W[index].y1 = 0;
	W[index].y2 = 0;
	W[index].y3 = 0;
	W[index].y4 = 0;
	W[index].z1 = 0;
	W[index].z2 = 0;
	W[index].z3 = 0;
	W[index].z4 = 0;
}

void create_walls()
{
	int i = 1;
	for (; i < ci + 1; i++)
	{
		glBegin(GL_QUADS);
		glColor3f(W[i].r, W[i].g, W[i].b);
		glVertex3f(W[i].x1, W[i].y1, W[i].z1);
		glVertex3f(W[i].x2, W[i].y2, W[i].z2);
		glVertex3f(W[i].x3, W[i].y3, W[i].z3);
		glVertex3f(W[i].x4, W[i].y4, W[i].z4);
		glEnd();
	}
}

void create_background()
{
	// ground
	glClearColor(.27, .71, .37, 0.01);
	 
	// sky
	glBegin(GL_QUADS);
	glColor3f(0.5, 1, 1);
	glVertex3f(-100, 1, 0);
	glVertex3f(-100, 1, -500);
	glVertex3f(120, 1, -500);
	glVertex3f(120, 1, 0);
	glEnd();
}

void create_cursor()
{
	glPushMatrix();
	glColor3f(1, 1, 1);
	glTranslatef(cx, cy, cz);
	glutSolidCube(0.2);
	glPopMatrix();
}

void create_markers()
{
	if (W[0].pos != 0) {
		int i;
		for (i = 0; i < 3; i++) {
			glPushMatrix();
			glColor3f(1, 0, 0);
			glTranslatef(M[i].x, M[i].y, M[i].z);
			glutSolidCube(0.2);
			glPopMatrix();
		}
	}
}

void create_grid()
{
	glColor3f(0, 0, 0); /* black */
	int i;
	for (i = 0; i < 42; i++)
	{
		glPushMatrix();
		if (i < 21)
			glTranslatef(0, 0, i);
		if (i >= 21)
		{
			glTranslatef(i - 21, 0, 0);
			glRotatef(-90, 0, 1, 0);
		}

		glBegin(GL_LINES);
		glVertex3f(0, -0.1, 0);
		glVertex3f(20, -0.1, 0);
		glEnd();
		glPopMatrix();
	}
}

void display_cord(int x, int y, float r, float g, float b, void* font, char* string, int strLen)
{
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	int i;
	for (i = 0; i < strLen; i++)
		glutBitmapCharacter(font, string[i]);
}
