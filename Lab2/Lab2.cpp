#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GL\glut.h"

using namespace std;

struct Point {
	float x;
	float y;
};

vector <Point> points;
vector <int> code;

Point currentPoint;

void readFromFile(string path);
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

void readFromFile(string path)
{
	fstream f(path, ios::in);
	if (points.empty())
	{
		int pointNumber;
		Point p;
		f >> pointNumber;
		for (int i = 0; i < pointNumber; i++)
		{
			f >> p.x >> p.y;
			points.push_back(p);
		}
		int movesNumber, m;
		f >> movesNumber;
		for (int i = 0; i < movesNumber; i++)
		{
			f >> m;
			code.push_back(m);
		}
	}

	f.close();
}

void moveTo(int pos)
{
	pos = abs(pos) - 1;

	currentPoint.x = points[pos].x;
	currentPoint.y = points[pos].y;
}

void lineTo(int pos)
{
	pos = abs(pos) - 1;

	Point p = points[pos];

	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex2i(currentPoint.x, currentPoint.y);
	glVertex2i(p.x, p.y);
	glEnd();

	currentPoint.x = p.x;
	currentPoint.y = p.y;
}

void draw(string fileName) {
	readFromFile(fileName);

	for (int i = 0; i != code.size(); i++) {
		code[i] < 0 ? moveTo((code[i])) : lineTo((code[i]));
	}

	points.clear();
	code.clear();
}

void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_CLIP_PLANE0);
	//                   x, y, z, d
	GLdouble arr[4] = { -1, 1, 0, 0 };
	glClipPlane(GL_CLIP_PLANE0, arr);
	glColor3d(0, 0, 0);


	draw("i.txt");
	draw("l.txt");

	glDisable(GL_CLIP_PLANE0);

	glutSwapBuffers();
}