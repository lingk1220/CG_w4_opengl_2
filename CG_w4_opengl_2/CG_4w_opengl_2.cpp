#include <iostream>
#include <gl/glew.h> 
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

GLfloat quadrant_x[4] = { 0.0f, -1.0f, -1.0f, 0.0f };
GLfloat quadrant_y[4] = { 0.0f, 0.0f, -1.0f, -1.0f };

GLclampf colors[4][4] = { {0.1f, 0.2f, 0.3f, 0.0f} , 
						  {0.4f, 0.5f, 0.6f, 0.0f} ,
						  {0.7f, 0.8f, 0.9f, 0.0f} ,
						  {0.4f, 0.6f, 0.8f, 0.0f} };


GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
void Mouse(int button, int state, int x, int y);
void main_init();
void draw_background();
void color_init();
void clamp_pos(GLfloat* input_pos);
int check_quadrant(GLfloat* pos);
int check_inout(int quad, GLfloat* pos);
void draw_rect();
void mouse_functions(int button, int quadrant, int inout);
void rect_change_color(int quadrant, int inout);
void rect_change_size(int quadrant, int inout);

GLfloat colors_background[4][4] = { 0, };
GLfloat colors_rect[4][4] = { 0, };
float size_rect[4] = { 0.5f, 0.5f, 0.5f, 0.5f };

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
	draw_rect();
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
	GLfloat input_pos[2] = { x, y };
	clamp_pos(input_pos);
	if (state == GLUT_DOWN) {
		int quadrant = check_quadrant(input_pos);
		int inout = check_inout(quadrant, input_pos);
		std::cout << quadrant << " " << inout << std::endl;
		mouse_functions(button, quadrant, inout);
		glutPostRedisplay();
	}

}	

void color_init() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			colors_background[i][j] = colors[i][j];
			colors_rect[i][j] = colors[i][j] + 0.1f;
		}
	}

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

void draw_rect() {
	for (int i = 0; i < 4; i++) {
		glColor3f(colors_rect[i][0], colors_rect[i][1], colors_rect[i][2]);
		glRectf(quadrant_x[i] + 0.5f - size_rect[i]/2, quadrant_y[i] + 0.5f - size_rect[i]/2, quadrant_x[i] + 0.5f + size_rect[i]/2, quadrant_y[i] + 0.5f + size_rect[i]/2);
	}
}

void clamp_pos(GLfloat * input_pos) {
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	int viewport_width = viewport[2];
	int viewport_height = viewport[3];
	input_pos[0] = (input_pos[0] / viewport_width) * 2 - 1.0f;
	input_pos[1] = -1*((input_pos[1] / viewport_height) * 2 - 1.0f);
}

int check_quadrant(GLfloat* pos) {
	if (pos[0] < 0) {
		if (pos[1] < 0) return 2;
		return 1;
	}
	else
	{
		if (pos[1] < 0) return 3;
		return 0;
	}
}

int check_inout(int quad, GLfloat*pos) {
	if (quadrant_x[quad] + 0.5f - size_rect[quad]/2 < pos[0] && pos[0] < quadrant_x[quad] + 0.5f + size_rect[quad]/2) {
		if (quadrant_y[quad] + 0.5f - size_rect[quad]/2 < pos[1] && pos[1] < quadrant_y[quad] + 0.5f + size_rect[quad]/2) {
			return 1;
		}
	}
	return 0;
}

void mouse_functions(int button, int quadrant, int inout) {

	switch (button) {
	case GLUT_LEFT_BUTTON:
		rect_change_color(quadrant, inout);
		break;

	case GLUT_RIGHT_BUTTON:
		rect_change_size(quadrant, inout);
		break;
	}
}

void rect_change_color(int quadrant, int inout) {
	if (inout == 1) {
		for (int i = 0; i < 3; i++) {
			colors_rect[quadrant][i] = (GLfloat)(rand() % 256) / 256;
		}
		return;
	}
	else {
		for (int i = 0; i < 3; i++) {
			colors_background[quadrant][i] = (GLfloat)(rand() % 256) / 256;
		}
		return;
	}
}

void rect_change_size(int quadrant, int inout) {
	if (inout == 1) {
		if (size_rect[quadrant] > 0.11f) {
			size_rect[quadrant] -= 0.1f;
		}
		return;
	}
	else {
		//if (size_rect[quadrant] < 1.0f) {
			size_rect[quadrant] += 0.1f;
		//}
		return;
	}
}