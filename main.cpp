#include <iostream>
#include <GL/glut.h>
#include "builder-modeler.h"

extern int cx, cy, cz, ci;
extern struct Wall W[1000];

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 600) / 2);
	glutCreateWindow("Building Modeler");

	glutDisplayFunc(display_callback);
	glutKeyboardFunc(keyboard_callback);
	glutSpecialFunc(special_keyboard_callback);

	init();
	glutMainLoop();
	return 0;
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(35, 1.0f, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void display_callback()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(-10, 0, -55);
	glRotatef(22, 2000, 1, 0); // x=2000 to align grid

	create_background();
	create_grid();
	create_walls();
	create_cursor();
	create_markers();
  
	// display cords
	char outText[15];
	outText[0] = 'X'; outText[1] = ':'; outText[3] = (cx / 10) + 0x30; outText[4] = (cx % 10) + 0x30;
	outText[5] = ' ';
	outText[6] = 'Z'; outText[7] = ':'; outText[8] = (cz / 10) + 0x30; outText[9] = (cz % 10) + 0x30;
	outText[10] = ' ';
	outText[11] = 'Y'; outText[12] = ':'; outText[13] = (cy / 10) + 0x30; outText[14] = (cy % 10) + 0x30;
	display_cord(20, 15, 0, 0, 0, GLUT_BITMAP_HELVETICA_12, outText, 15);
	glutSwapBuffers();
}

/* Handles arrow and page keys */
void special_keyboard_callback(int key, int, int)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			if (cz > 0)
				cz --;
			std::cout << "KEY_UP" << std::endl;
			break;
		case GLUT_KEY_DOWN:
			if (cz < 20)
				cz ++;
			std::cout << "KEY_DOWN" << std::endl;
			break;
		case GLUT_KEY_LEFT:
			if (cx > 0)
				cx --;
			std::cout << "KEY_LEFT" << std::endl;
			break;
		case GLUT_KEY_RIGHT:
			if (cx < 20)
				cx ++;
			std::cout << "KEY_RIGHT" << std::endl;
			break;
		case GLUT_KEY_PAGE_UP:
			if (cy < 10)
				cy ++;
			std::cout << "PAGE_UP" << std::endl;
			break;
		case GLUT_KEY_PAGE_DOWN:
			if (cy > 0)
				cy --;
			std::cout << "PAGE_DOWN" << std::endl;
			break;
	}
	glutPostRedisplay();
}

/* Handles ESC and SPACE keys and RGB */
void keyboard_callback(unsigned char key, int, int)
{
	switch (key)
	{
		// functionality
		case 27:  /* ESC   - exit */
			std::cout << "ESC" << std::endl;
			exit(0);
		case 32:  /* SPACE - set marker */
			add_wall();
			std::cout << "SPACE" << std::endl;
			break;
		case 117: /* u     - undo wall */
			undo_last_wall(ci);
			std::cout << "U" << std::endl;
			break;

		// colors
		case 119: /* w - WHITE */
			W[ci].r = 1; W[ci].g = 1, W[ci].b = 1;
			std::cout << "w" << std::endl;
			break;
		case 114: /* r - RED */
			W[ci].r = 1; W[ci].g = 0, W[ci].b = 0;
			std::cout << "r" << std::endl;
			break;
		case 111: /* o - ORANGE */
			W[ci].r = 1; W[ci].g = 0.6, W[ci].b = 0;
			std::cout << "o" << std::endl;
			break;
		case 121: /* y - YELLOW */
			W[ci].r = 1; W[ci].g = 1, W[ci].b = 0;
			std::cout << "y" << std::endl;
			break;
		case 103: /* g - GREEN */
			W[ci].r = 0; W[ci].g = 1, W[ci].b = 0;
			std::cout << "g" << std::endl;
			break;
		case 98:  /* b - BLUE */
			W[ci].r = 0; W[ci].g = 0, W[ci].b = 1;
			std::cout << "b" << std::endl;
			break;
		case 105: /* i - INDIGO */
			W[ci].r = 0.29; W[ci].g = 0, W[ci].b = 0.51;
			std::cout << "i" << std::endl;
			break;
		case 118: /* v - VIOLET */
			W[ci].r = 0.5; W[ci].g = 0, W[ci].b = 1;
			std::cout << "v" << std::endl;
			break;
		default: /*      BLACK */
			W[ci].r = 0; W[ci].g = 0, W[ci].b = 0;
			std::cout << "BLACK" << std::endl;
	}
	glutPostRedisplay();
}
