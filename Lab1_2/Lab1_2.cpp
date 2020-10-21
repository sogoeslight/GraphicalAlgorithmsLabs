#include <Windows.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glut.h>

using namespace std;

struct Point
{
	int x, y;
};

vector <Point> points;

void display();
void readFromFile(string path);
void reshape(int w, int h);
void lineTo(int pos);
void moveTo(int pos);
void draw(string fileName);

vector <Point> pointVector2;
Point currentPoint;
vector <int> code;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE - bit mask to select a single buffered window
	glutInitWindowSize(800, 600);

	glutCreateWindow("Task 2");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutMainLoop();

	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 100, 0, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	draw("umbrella.txt");
	draw("i.txt");
	draw("l.txt");

	glutSwapBuffers();
}

void draw(string fileName)
{
	readFromFile(fileName);

	for (int i = 0; i != code.size(); i++) {
		code[i] < 0 ? moveTo((code[i])) : lineTo((code[i]));
	}

	pointVector2.clear();
	code.clear();
}

void readFromFile(string path)
{
	fstream f(path, ios::in);
	int pointNumber;
	int x, y; Point p;
	f >> pointNumber; // amount of points
	for (int i = 0; i < pointNumber; i++) // read all points
	{
		f >> p.x >> p.y;
		pointVector2.push_back(p);
	}
	int movesNumber, m;
	f >> movesNumber; // amount of moves
	for (int i = 0; i < movesNumber; i++) // read all moves (0 - move, 1 - draw)
	{
		f >> m; code.push_back(m);
	}
	f.close();
}

void moveTo(int pos)
{
	pos = abs(pos) - 1;

	currentPoint.x = pointVector2[pos].x;
	currentPoint.y = pointVector2[pos].y;
}

void lineTo(int pos)
{
	pos = abs(pos) - 1;

	Point p = pointVector2[pos];

	glBegin(GL_LINES);
	glColor3d(0, 0, 0);
	glVertex2i(currentPoint.x, currentPoint.y);
	glVertex2i(p.x, p.y);
	glEnd();

	currentPoint.x = p.x;
	currentPoint.y = p.y;
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