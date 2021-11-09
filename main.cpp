#include <GL/freeglut.h>

using namespace std;

int windowWidth  = 800;
int windowHeight = 600;
int mouseXPos = -1;

void *defaultFont = GLUT_BITMAP_TIMES_ROMAN_10;

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
            glVertex2f(0, 0.9);
            glVertex2f(1.0, 0.9);
		glEnd();
    }
};

UI ui;

void DisplayScene() {
    glClear(GL_COLOR_BUFFER_BIT);
    // glRotatef(1, 0.0f, 1.0f, 0.0f);

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
   ui.drawHUD();

    // Смена буферов для отрисовки анимации
    glutSwapBuffers();
}

// Настройка матрицы проекции перед отображением окна (Оптимизация под работу с 2D)
void WindowResize(GLsizei  w, GLsizei  h) { // GLsizei - non-negative integer
    if (h == 0)                  // To prevent divide by 0
        h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);      // Set the viewport to cover the window

    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix

    if (w >= h) {
        // If larger width
        glOrtho(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0, -1.0, 1.0);
    } else {
        // If larger height
        glOrtho(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio, -1.0, 1.0);
    }
}

void DisplayText(GLfloat x, GLfloat y, void *font, const char *str) {
    // Отключим тест Z-буффера, т.к. текст не рисуется, если его что-то заграждает
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0, 0.0, 1.0);
    glRasterPos2f(x, y);
    glutBitmapString(font, (const unsigned char *)str);
    // glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char *)str);
// }
}

void ProcessKeyPress(unsigned char key, int x, int y) {
    switch (key)
    {
    // Esc
    case 27:
        // TODO: "Are you sure you want to exit" func
        exit(EXIT_SUCCESS);
        break;
    // Spacebar
    case 32:
        // TODO: Space key for clicking
        DisplayText(0.3f, -0.4f, defaultFont, "You did it!");
        break;
    }
}

void ProcessMousePress(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        glRotatef(10, 0.0f, 1.0f, 0.0f);
        DisplayText(0.3f, -0.4f, defaultFont, "You did it!");
        // // TODO: add Y position
        // // Reset mouse coords when LMB is released
        // if (state == GLUT_UP)
        //     mouseXPos = -1;
        // else mouseXPos = x;
    }
}

int main(int argc, char **argv) {
    // Инициализация GLUT
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Создание окна
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Test Window");
    // glutFullScreen();

    // Отображение
    glutDisplayFunc(DisplayScene);
    // Изменение размера окна
    glutReshapeFunc(WindowResize);
    // Программа в режиме ожидания
    glutIdleFunc(DisplayScene);

    // Обработка нажатия клавиш
    glutKeyboardFunc(ProcessKeyPress);
    // Обработка мыши
    glutMouseFunc(ProcessMousePress);

    // Основной цикл GLUT
    glutMainLoop();

    return 1;
}