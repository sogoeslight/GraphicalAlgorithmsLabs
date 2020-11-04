#include <Windows.h>
#include <GL/glut.h> 
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Point
{
	float x, y, z;
};

vector<Point> v;
vector<vector<int>> faces;
int point_count, face_count;

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
void readFromFile(string fileName);
void draw(string fileName);
void rotate(bool direction);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lesson 7");

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

	gluPerspective(100, 1, 0, 20);
	gluLookAt(50, 50, 90, 50, 50, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);

	if (key == 45) glScalef(0.8, 0.8, 0.8); // '-'
	if (key == 43) glScalef(1.2, 1.2, 1.2); // '+'
	if (key == 127) glRotatef(1, 0.0, 0.0, 1.0); // Del

	display();
}

void processSpecialKeys(int key, int x, int y) {
	glMatrixMode(GL_MODELVIEW);

	switch (key) {
	case GLUT_KEY_UP:
		glTranslated(0, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslated(0, -1, 0);
		break;
	case GLUT_KEY_LEFT:
		glTranslated(-1, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		glTranslated(1, 0, 0);
		break;

	case GLUT_KEY_HOME:
		glRotatef(1, 1.0, 0.0, 0.0);
		break;
	case GLUT_KEY_END:
		glRotatef(1, 0.0, 1.0, 0.0);
		break;

	case GLUT_KEY_PAGE_DOWN:
		glRotatef(-1, 1.0, 1.0, 1.0);
		break;
	case GLUT_KEY_PAGE_UP:
		glRotatef(1, 1.0, 1.0, 1.0);
		break;
	}

	display();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	draw("pointsI.txt");
	draw("pointsL.txt");

	glutSwapBuffers();
}

void draw(string fileName)
{
	readFromFile(fileName);

	for (int i = 0; i < face_count; i++)
	{
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < faces[i].size(); j++)
		{
			glVertex3f(v[faces[i][j]].x, v[faces[i][j]].y, v[faces[i][j]].z);
		}
		glEnd();
	}
	
	v.clear();
	faces.clear();
}

void readFromFile(string fileName)
{
	float x, y, z;
	Point p;
	ifstream f(fileName, ios::in);
	f >> point_count >> face_count;
	for (int i = 0; i < point_count; i++)
	{
		f >> p.x >> p.y >> p.z;
		v.push_back(p);
	}
	faces.resize(face_count);
	for (int i = 0; i < face_count; i++)
	{
		int n;
		f >> n;
		for (int j = 0; j < n; j++)
		{
			int p;
			f >> p;
			faces[i].push_back(p);
		}
	}
	f.close();
}