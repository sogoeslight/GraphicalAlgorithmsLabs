#include <Windows.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glut.h>

using namespace std;

void reshape(int w, int h);
void display();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE - bit mask to select a single buffered window
	glutInitWindowSize(800, 600);

	glutCreateWindow("Task 1");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); // Applies subsequent matrix operations to the projection matrix stack.
	glLoadIdentity(); // Replaces the current matrix with the identity matrix
	gluOrtho2D(-100, 100, -50, 50);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT); // GL_COLOR_BUFFER_BIT indicates the buffers currently enabled for color writing.

	float left = -100, right = 100, bottom = -50, top = 50;

	// Axes
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	// y
	glVertex2f(0, bottom);
	glVertex2f(0, top);
	// x
	glVertex2f(left, 0);
	glVertex2f(right, 0);
	glEnd();

	// Graph
	glColor3d(0, 0, 1);
	glBegin(GL_LINE_STRIP);
	for (float x = -100; x < 100; x += 0.5) {
		glVertex2f(x, fabs(0.25 * x + 3 * cos(100 * x) * sin(x)));
	}
	glEnd();

	glutSwapBuffers(); // Swaps the buffers of the current window if double buffered
}

#pragma region Coordinates storing methods:
/*
Non-economic    Economic
	5	          4
	50 35         25 40
	50 55         25 60
	40 45      	  15 50
	60 45      	  35 50
	50 55      	  5
	5	       	  -1
	0	       	  2
	1	       	  3
	1	       	  4
	1	       	  2
	1
*/
#pragma endregion

#pragma region Coordinates
/* Umbrella
4
15 10
15 30
5 20
25 20
5
-1
2
3
4
2
*/
#pragma endregion