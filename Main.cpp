#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

using namespace std;

const GLdouble pi = 3.1415926535897;

static GLint year = 0, day = 0, moonRotation = 0, sunRotation = 0, zRotation = 0;
static GLfloat radians = 0, degrees = 0;
static GLint vp[4];


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	glPushMatrix();

		// Sun
		glPushMatrix();
			glRotatef((GLfloat)sunRotation, 0.0, 1.0, 0.0);
			glColor3f(1.0, 1.0, 0.0);	// yellow
			glutWireCube(2.0);
		glPopMatrix();

		// Earth
		glRotatef((GLfloat)zRotation, 0.0, 0.0, 1.0);
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);

		glTranslatef(2.0, 0.0, 0.0);
		
		
		glPushMatrix();
			glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
			glColor3f(0.0, 0.0, 1.0); // blue
			glutSolidCube(0.4);
			
			//Moon
			glTranslatef(0.5, 0.0, 0.0);
			glRotatef((GLfloat)moonRotation, 0.0, 1.0, 0.0);
			glColor3f(0.5, 0.5, 0.5); // gray
			glutWireCube(0.1);

		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-4.0, 4.0, -4.0 * (GLfloat)h / (GLfloat)w,
			4.0 * (GLfloat)h / (GLfloat)w, -10.0, 10.0);
	else
		glOrtho(-4.0 * (GLfloat)w / (GLfloat)h,
			4.0 * (GLfloat)w / (GLfloat)h, -4.0, 4.0, -10.0, 10.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd': day = (day + 10) % 360;
		break;
	case 'D': day = (day - 10) % 360;
		break;
	case 'y': year = (year + 5) % 360;
		break;
	case 'Y': year = (year - 5) % 360;
		break;
	case 'm': moonRotation = (moonRotation + 5) % 360;
		break;
	case 'z': zRotation = (zRotation + 5) % 360;
	default:;
	}
	//glutPostRedisplay();
}

void mouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON & state == GLUT_UP) {
		
		glGetIntegerv(GL_VIEWPORT, vp);

		x = x - vp[2]/2;
		y = vp[3] - y - vp[3]/2;
		
		//cout << vp[2] << '\n';
		//cout << vp[3] << '\n';
		//cout << "x is: " << x << " and y is " << y << "\n";
		radians = atan2(y, x);
		//cout << "radians are: " << radians << "\n";
		degrees = radians * (180 / pi);
		//cout << "degrees are: " << degrees << "\n";
		zRotation = degrees;
	}
}

void timer(int n) {
	
	sunRotation = (sunRotation - 2) % 360;
	day = (day + 2) % 360;
	year = (year + 1) % 360;
	moonRotation = (moonRotation + 1) % 360;

	glutPostRedisplay();
	glutTimerFunc(20, timer, 0);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("HW4-2");
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glutDisplayFunc(display);

	glMatrixMode(GL_PROJECTION);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);

	glEnable(GL_DEPTH_TEST);        /* Enable hidden-surface removal */

	glutTimerFunc(100, timer, 0);

	glutMainLoop();
}