#include <iostream>
#include <GL/glut.h>

using namespace std;

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("OpenGL lesson 6");

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
	gluPerspective(30, 1, 0, 20);
	gluLookAt(0, 0, 30, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(1, 1, 1, 0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0, 1.0, 0.0);
	glutWireCube(8);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidOctahedron();
	glColor3f(0.0, 0.0, 1.0);
	glutWireIcosahedron();
	
	// Axes
	glBegin(GL_LINES);

	glColor3f(0, 0, 0);

	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(100.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 100.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 100.0);

	glEnd();

	glutSwapBuffers();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	glMatrixMode(GL_MODELVIEW);

	if (key == 45) glScalef(0.8, 0.8, 0.0); // '-'
	if (key == 43) glScalef(1.2, 1.2, 0.0); // '+'
	if (key == 127) glRotatef(1, 0.0, 0.0, 1.0); // Del

	display();
}

void processSpecialKeys(int key, int x, int y) {
	glMatrixMode(GL_MODELVIEW);

	switch (key) {
	case GLUT_KEY_UP:
		glTranslated(0, 10, 0);
		break;
	case GLUT_KEY_DOWN:
		glTranslated(0, -10, 0);
		break;
	case GLUT_KEY_LEFT:
		glTranslated(-10, 0, 0);
		break;
	case GLUT_KEY_RIGHT:
		glTranslated(10, 0, 0);
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
