#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

GLfloat quadrant_x[4] = { 0.0f, -1.0f, -1.0f, 0.0f };
GLfloat quadrant_y[4] = { 0.0f, 0.0f, -1.0f, -1.0f };

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void main_init();
void draw_background();
void color_init();

GLfloat colors_background[4][4] = { 0, };
void main(int argc, char** argv)
{
	main_init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOWWIDTH, WINDOWHEIGHT);
	glutCreateWindow("CG_4w_opengl_2");

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		exit(EXIT_FAILURE);
	}
	else
	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(Mouse);
	glutMainLoop();
}


GLvoid drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_background();
	
	glutSwapBuffers();
}


GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'q':
		glutLeaveMainLoop();
		break;
	}
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		glutPostRedisplay();
	}
}	

void color_init() {
	colors_background[0][0] = 0.1f;
	colors_background[0][1] = 0.2f;
	colors_background[0][2] = 0.3f;
	colors_background[0][3] = 0.0f;

	colors_background[1][0] = 0.4f;
	colors_background[1][1] = 0.5f;
	colors_background[1][2] = 0.6f;
	colors_background[1][3] = 0.0f;

	colors_background[2][0] = 0.7f;
	colors_background[2][1] = 0.8f;
	colors_background[2][2] = 0.9f;
	colors_background[2][3] = 0.0f;

	colors_background[3][0] = 0.4f;
	colors_background[3][1] = 0.6f;
	colors_background[3][2] = 0.8f;
	colors_background[3][3] = 0.0f;

}
void main_init() {

	color_init();
}

void draw_background() {
	for (int i = 0; i < 4; i++) {
			glColor3f(colors_background[i][0], colors_background[i][1], colors_background[i][2]);
			glRectf(quadrant_x[i], quadrant_y[i], quadrant_x[i] + 1.0f, quadrant_y[i] + 1.0f);
	}
}