#include <iostream>
#include <GL/glut.h>
using namespace std;

void display()
{
	glutSwapBuffers();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}