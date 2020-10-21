#include <GL/glut.h>

void reshape(int w, int h);
void display();
void processNormalKeys(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);

int windowH, windowW;

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
	windowH = h;
	windowW = w;
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	// Axes
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	// y
	glVertex2f(windowW / 2, -windowH);
	glVertex2f(windowW / 2, windowH);
	// x
	glVertex2f(-windowW, windowH / 2);
	glVertex2f(windowW, windowH / 2);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 1.0);
	glVertex2i(250, 450);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(250, 150);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(550, 150);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(550, 450);
	glEnd();
	glutSwapBuffers();
	glDisable(GL_CLIP_PLANE0);
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27) // Esc
		exit(0);
	if (key == 65) // 'A'
	{
		glMatrixMode(GL_MODELVIEW);
		glTranslated(20, 20, 0);
		display();
	}
}

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
	}

	display();
}
