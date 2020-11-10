#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "GL\glut.h"

using namespace std;

struct Point {
	float x;
	float y;
	float z;
};

vector <Point> points;
vector <int> code;
Point currentPoint;

void reshape(int w, int h);
void display();
void readFromFile(string fileName);
void draw(string fileName);

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

	if (f.is_open()) 
	{
		if (points.empty()) 
		{
			Point p;
			int pointNumber;
			f >> pointNumber;
			for (int i = 0; i < pointNumber; i++)
			{
				f >> p.x >> p.y >> p.z;
				points.push_back(p);
			}

			int move, amountOfMoves;
			f >> amountOfMoves;
			for (int i = 0; i < amountOfMoves; i++)
			{
				f >> move;
				code.push_back(move);
			}
		}
		else 
		{
			int shiftForDots = points.size();
			int pointNumber;
			Point p;
			f >> pointNumber;
			for (int i = 0; i < pointNumber; i++)
			{
				f >> p.x >> p.y >> p.z;
				points.push_back(p);
			}

			int movesNumber, m;
			f >> movesNumber;
			for (int i = 0; i < movesNumber; i++)
			{
				f >> m;
				if (m < 0)
				{
					m -= shiftForDots;
				}
				else
				{
					m += shiftForDots;
				}
				code.push_back(m);
			}
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

// B-Spline
void lineTo(int pos) {
	Point p = points[pos - 1];
	glColor3d(0, 0, 0);
	// I 12
	if (pos <= 12) {
		float arr[4][3];
		arr[0][0] = currentPoint.x;
		arr[0][1] = currentPoint.y;
		arr[0][2] = currentPoint.z;
		arr[2][0] = p.x;
		arr[2][1] = p.y;
		arr[2][2] = p.z;

		if (currentPoint.x == p.x && pos != 1 && pos != 6)
		{
			arr[1][0] = p.x + 3;
		}
		else
		{
			arr[1][0] = ((currentPoint.x + p.x) / 2) - 2;
		}

		if (currentPoint.y == p.y && p.y > 1)
		{
			arr[1][1] = p.y + 3;
		}
		else
		{
			arr[1][1] = ((currentPoint.y + p.y) / 2) - 3;
		}

		arr[1][2] = 0;
		arr[2][2] = 0;

		GLfloat node[6] = { 0, 0, 0, 1, 1, 1 };
		GLUnurbs* nurbs = gluNewNurbsRenderer();
		gluBeginCurve(nurbs);
		gluNurbsCurve(nurbs, 6, node, 3, &arr[0][0], 3, GL_MAP1_VERTEX_3);
		gluEndCurve(nurbs);
	}
	// L 8
	if (pos > 12) {
		float arr[4][3];
		arr[0][0] = currentPoint.x;
		arr[0][1] = currentPoint.y;
		arr[0][2] = currentPoint.z;
		arr[2][0] = p.x;
		arr[2][1] = p.y;
		arr[2][2] = p.z;

		if (currentPoint.x == p.x)
		{
			arr[1][0] = p.x + 3;
		}
		else
		{
			arr[1][0] = ((currentPoint.x + p.x) / 2) - 2;
		}

		if (currentPoint.y == p.y && p.y > 1)
		{
			arr[1][1] = p.y + 3;
		}
		else
		{
			arr[1][1] = ((currentPoint.y + p.y) / 2) - 3;
		}

		arr[1][2] = 0;
		arr[2][2] = 0;

		GLfloat node[6] = { 0, 0, 0, 1, 1, 1 };
		GLUnurbs* nurbs = gluNewNurbsRenderer();
		gluBeginCurve(nurbs);
		gluNurbsCurve(nurbs, 6, node, 3, &arr[0][0], 3, GL_MAP1_VERTEX_3);
		gluEndCurve(nurbs);
	}

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

	draw("pointsI.txt");
	draw("pointsL.txt");

	glutSwapBuffers();
}