#include <math.h>
#include "GL\glut.h"

using namespace std;

void reshape(int w, int h);
void display();

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Lab 2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();
	return 0;
}

void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLfloat arr1[4][3] = { { 50, 58, 0 }, { 60, 70, 0 }, { 70, 50, 0 }, { 50, 30, 0 } };
GLfloat arr2[4][3] = { { 50, 58, 0 }, { 40, 70, 0 }, { 30, 50, 0 }, { 50, 30, 0 } };

// Bezier
void draw() {
	glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &arr1[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 15; i++)
		glEvalCoord1f((GLfloat)i / 15);
	glEnd();

	glMap1f(GL_MAP1_VERTEX_3, 0, 1, 3, 4, &arr2[0][0]);
	glEnable(GL_MAP1_VERTEX_3);
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 15; i++)
		glEvalCoord1f((GLfloat)i / 15);
	glEnd();
}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glutSwapBuffers();
}