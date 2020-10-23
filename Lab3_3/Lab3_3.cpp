#include <Windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glut.h>

using namespace std;

struct Point
{
	int x, y;
};

vector <Point> points;
Point currentPoint;
vector <int> code;

void lineTo(int pos);
void moveTo(int pos);
void draw(string fileName);
void readFromFile(string path);
void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void rotate(bool direction);
void display();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lesson 5");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(processNormalKeys);
	glutSpecialFunc(processSpecialKeys);
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

void processNormalKeys(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);

	if (key == 27) exit(0); // Esc
	if (key == 65) glTranslated(20, 20, 0); // 'A'
	if (key == 45) glScalef(0.8, 0.8, 0.0); // '-'
	if (key == 43) glScalef(1.2, 1.2, 0.0); // '+'

	display();
}

// small workaround for easier rotation
float angle = 0.0f;

void processSpecialKeys(int key, int x, int y) {
	glMatrixMode(GL_MODELVIEW);

	switch (key) {
	case GLUT_KEY_UP:
		glTranslated(0, 20, 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslated(0, -20, 0);
		break;
	case GLUT_KEY_LEFT:
		glTranslated(-20, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		glTranslated(20, 0, 0);
		break;

	case GLUT_KEY_HOME:
		glRotatef(1, 0.0, 0.0, 1.0);
		break;
	case GLUT_KEY_END:
		glRotatef(-1, 0.0, 0.0, 1.0);
		break;

	case GLUT_KEY_PAGE_DOWN:
		rotate(false);
		break;
	case GLUT_KEY_PAGE_UP:
		rotate(true);
		break;
	}

	display();
}

void rotate(bool direction) {
	direction ? angle-- : angle++;
}

void display() {
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	glPushMatrix(); //------------ Encapsulate Rotation BEGIN -----------
	glRotatef(angle * -1, 0.0, 0.0, 1.0);
	draw("pointsI.txt");
	glPopMatrix(); //------------ Encapsulate Rotation END ----------

	glPushMatrix(); //------------ Encapsulate Rotation BEGIN ----------	
	glRotatef(angle, 0.0, 0.0, 1.0);
	draw("pointsL.txt");
	glPopMatrix(); //------------ Encapsulate Rotation END ----------

	glutSwapBuffers();
}

void draw(string fileName)
{
	readFromFile(fileName);

	for (int i = 0; i != code.size(); i++) {
		if ((code[i]) < 0) moveTo((code[i]));
		else lineTo((code[i]));
	}

	points.clear();
	code.clear();
}

void readFromFile(string path)
{
	fstream f(path, ios::in);
	int pointNumber;
	int x, y; Point p;
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
