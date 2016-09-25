#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int year = 0, day = 0, moonRotation = 0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();

		// Sun
		glColor3f(1.0, 1.0, 0.0);	// yellow
		glutSolidCube(2.0);

		// Earth
		glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
		glTranslatef(2.0, 0.0, 0.0);
		glRotatef((GLfloat)day, 0.0, 1.0, 0.0);

		glPushMatrix();
			glColor3f(0.0, 0.0, 1.0); // blue
			glutWireCube(0.4);
			
			//Moon

			glTranslatef(0.5, 0.0, 0.0);
			glRotatef((GLfloat)moonRotation, 0.0, 1.0, 0.0);
			glColor3f(0.5, 0.5, 0.5);
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
	default:;
	}
	glutPostRedisplay();
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
	glEnable(GL_DEPTH_TEST);        /* Enable hidden-surface removal */

	glutMainLoop();
}