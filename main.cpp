#include <GL/freeglut.h>

using namespace std;

float windowWidth  = 800;
float windowHeight = 600;

class UI {
private:
    int score = 0;

public:
    void UpdateScore(int amount) {
        score += amount;
    }

    void drawHUD() // отрисовка HUD, контрольный параметр k
	{
		glColor3f(0.3, 0.3, 0.3);
		glLineWidth(10.0);
		glBegin(GL_LINES);
		glVertex2f(0, 90);
		glVertex2f(100, 90);	
		glEnd();
		glLineWidth(5.0);
		glBegin(GL_LINES);
		glVertex2f(0, 10);
		glVertex2f(100, 10);
		glEnd();
    }
};

void WindowDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

   glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.1f, -0.6f);
      glVertex2f(0.7f, -0.6f);
      glVertex2f(0.4f, -0.1f);
 
      glColor3f(1.0f, 0.0f, 0.0f); // Red
      glVertex2f(0.3f, -0.4f);
      glColor3f(0.0f, 1.0f, 0.0f); // Green
      glVertex2f(0.9f, -0.4f);
      glColor3f(0.0f, 0.0f, 1.0f); // Blue
      glVertex2f(0.6f, -0.9f);
   glEnd();

    glutSwapBuffers();
}

// Настройка матрицы проекции перед отображением окна (Оптимизация под работу с 2D)
void WindowResize(GLsizei  w, GLsizei  h) { // GLsizei - non-negative integer
    if (h == 0) h = 1; // To prevent divide by 0
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h); // Set the viewport to cover the window

    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix

    if (w >= h) {
        // aspect >= 1, with larger width
        // gluOrtho2D(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0);
        glOrtho(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, 0.0, 1.0);
    } else {
        // gluOrtho2D(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio);
        glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, 0.0, 1.0);
    }
/*     X: from 0 to windowWidth
       Y: from 0 to windowHeight FLIPPED
       Z: from 0 to 1 (geometry not rendered outside)
       Координаты начинаются с ЛЕВОГО ВЕРХНЕГО угла */
    // glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 1.0);
    // glMatrixMode(GL_MODELVIEW);
    // glLoadIdentity();
}

int main(int argc, char **argv) {
    // Инициализация GLUT
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Test Window");

    // Регистрация обратных вызовов
    glutDisplayFunc(WindowDisplay);
    // Изменение размера окна
    glutReshapeFunc(WindowResize);

    // Основной цикл GLUT
    glutMainLoop();

    return 1;
}