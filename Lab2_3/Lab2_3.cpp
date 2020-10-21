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

// B-Spline
void draw() {
	GLfloat node[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };
	GLUnurbs* nurbs = gluNewNurbsRenderer();
	gluBeginCurve(nurbs);
	gluNurbsCurve(nurbs, 8, node, 3, &arr1[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(nurbs);

	gluBeginCurve(nurbs);
	gluNurbsCurve(nurbs, 8, node, 3, &arr2[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(nurbs);
}

void display() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	draw();
	glutSwapBuffers();
}