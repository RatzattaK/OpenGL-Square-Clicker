#include <GL/freeglut.h>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

int windowWidth  = 600;
int windowHeight = 600;

void *defaultFont = GLUT_BITMAP_HELVETICA_18;

GLfloat clrCream[3] = {0.99, 0.964, 0.929};
GLfloat clrAqua[3] = {0.407, 0.53, 0.53};
GLfloat clrWhite[3] = {1.0, 1.0, 1.0};
GLfloat clrBlack[3] = {0.0, 0.0, 0.0};
GLfloat clrGreen[3] = {0.713, 0.843, 0.658};

class Clicks {
public:
    float amount = 0;
    float perSec = 0;
};
Clicks clicks;

const char *ConvertToChar(int val) {
        stringstream sstream;
        sstream << val;
        string str = sstream.str();
        return str.c_str();
}

const char *ConvertToChar(float val) {
        stringstream sstream;
        sstream.precision(2);
        sstream << fixed << val;
        string str = sstream.str();
        return str.c_str();
}

void DisplayText(float _x, float _y, const GLfloat *v, void *font, const char *_str) {
    glColor3fv(v);
    glRasterPos2f(_x, _y);
    int len, i;
    len = (int)strlen(_str);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(font, _str[i]);
}

class UpgradeButton {
public:
    int baseCost;
    float multiplier = 1.07;
    int owned = 0;
    float price;

    float x;
    float y;
    float w;
    float h;
    GLfloat color[3];

    void Draw() {
        glColor3fv(clrCream);
        glBegin(GL_QUADS);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y + h);
            glVertex2f(x, y + h);
            glVertex2f(x, y);
        glColor3fv(clrGreen);
            glVertex2f(x + w + 10, y);
            glVertex2f(x + w + 10, y + h);
            glVertex2f(x + w, y + h);
            glVertex2f(x + w, y);
        glEnd();
        DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Auto Click");
        DisplayText(x + w - 10, y + 5, clrBlack, defaultFont, ConvertToChar((int)price));
        DisplayText(x + w + 2, y + 5, clrCream, defaultFont, ConvertToChar(owned));
    }

    void OnClick() {
        if (price <= clicks.amount) {
            clicks.amount -= price;
            clicks.perSec += 0.2;
            owned++;
            price = baseCost * powf(multiplier, owned);
        }
    }

    UpgradeButton(int upgradeCost, float _x, float _y, float width, float height) {
        baseCost = upgradeCost;
        price = baseCost * powf(multiplier, owned);
        x = _x;
        y = _y;
        w = width;
        h = height;
    }
};
UpgradeButton btnAutoClicks(10, 50, 20, 35, 8);

class UI {
public:
    // const char *numericChar;

    // void DisplayText(float _x, float _y, const GLfloat *v, void *font, const char *_str) {
    //     glColor3fv(v);
    //     glRasterPos2f(_x, _y);
    //     int len, i;
    //     len = (int)strlen(_str);
    //     for (i = 0; i < len; i++)
    //         glutBitmapCharacter(font, _str[i]);
    // }

    void DrawHUD() {
        // Lines
        glPushMatrix();
        glColor3fv(clrCream);
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
        glPopMatrix();
        // drawLevel();
        btnAutoClicks.Draw();
        DisplayClickCount();
    }

    // void drawLevel() // отрисовка номера уровня
    // {
    //     stringstream temp_str;
    //     temp_str << (stage);
    //     string str = temp_str.str();
    //     numericChar = str.c_str();
    //     DisplayText(5, 7, 1.0, 1.0, 1.0, GLUT_BITMAP_TIMES_ROMAN_24, "CURRENT LEVEL:");
    //     DisplayText(32, 7, 1.0, 0.0, 0.0, GLUT_BITMAP_TIMES_ROMAN_24, numericChar);
    // }

    void drawDarkOverlay() {
        glColor4f(0.0, 0.0, 0.0, 0.4);
        glBegin(GL_QUADS);
            glVertex2i(0, 0);
            glVertex2i(0, 100);
            glVertex2i(100, 100);
            glVertex2i(100, 0);
        glEnd();
    }

    void DisplayClickCount() {
        DisplayText(70, 7, clrWhite, defaultFont, "CLICKS:");
        DisplayText(85, 7, clrGreen, defaultFont, ConvertToChar(clicks.amount));
    }

    // TODO: Меню при входе в игру (вы заработали...)
    void drawIntro() {
        DisplayText(33, 50, clrBlack, GLUT_BITMAP_TIMES_ROMAN_24, "PRESS ENTER TO START");
        DisplayText(10, 80, clrWhite, GLUT_BITMAP_HELVETICA_12, "Made by Alexander Tatchin");
        DisplayText(10, 85, clrWhite, GLUT_BITMAP_HELVETICA_12, "Implemented via Visual C++ / Freeglut OPEN_GL");
        DisplayText(10, 90, clrWhite, GLUT_BITMAP_HELVETICA_12, "Feb 2015");
    }

    void drawPause() {
        DisplayText(27, 50, clrGreen, GLUT_BITMAP_9_BY_15, "ARE YOU SURE YOU WANT TO EXIT?");
    }
};
UI ui;

class ObjMouse {
public:
    float x = 15;
    float y = 40;
    float size = 20;
    void Draw() {
        glBegin(GL_QUADS);
        glColor3fv(clrGreen);
            glVertex2f(x + size, y       );
            glVertex2f(x + size, y + size);
            glVertex2f(x       , y + size);
            glVertex2f(x       , y       );
        glEnd();
    }
    void Animate() {
        glClear(GL_COLOR_BUFFER_BIT);

        glPushMatrix();
        ui.DrawHUD();
        glTranslatef(0.0, 0.02, 0.0);
        this->Draw();
        glPopMatrix();
        glutSwapBuffers();
    }
};

ObjMouse MouseObj;

class GameDirector {
public:
    int gameState = 1;

    void StartScreen() {
        ui.drawIntro();
    }

    void GameProcess() {
        ui.DrawHUD();
        MouseObj.Draw();
    }

    void GamePause() {
        ui.drawPause();
    }
};

GameDirector director;

void DisplayScene() {
    glClearColor(0.407, 0.53, 0.53, 1.0); // Основной цвет фона
    glClear(GL_COLOR_BUFFER_BIT);

    switch (director.gameState)
    {
    // Начальный экран
    case 1:
        director.StartScreen();
        break;
    // Режим игры
    case 2:
        director.GameProcess();
        break;
    // Режим паузы
    case 3:
        director.GameProcess(); // Отрисовка фона игры
        ui.drawDarkOverlay();
        director.GamePause();
        break;
    default:
        return;
    }
    // Смена буферов для отрисовки
    glutSwapBuffers();
}

// Настройка матрицы проекции перед отображением окна (Корректное соотношение сторон)
void WindowResize(GLsizei  w, GLsizei  h) { // GLsizei - non-negative integer
    if (h == 0)                  // To prevent divide by 0
        h = 1;
    GLfloat aspectRatio = (GLfloat)w / (GLfloat)h;
    glViewport(0, 0, w, h);      // Set the viewport to cover the window
    glMatrixMode(GL_PROJECTION); // To operate on the Projection matrix
    glLoadIdentity();            // Reset the projection matrix

    if (w >= h) {
        // If larger width
        glOrtho(-aspectRatio, aspectRatio, -1, 1, -1, 1);
    } else {
        // If larger height
        glOrtho(-1, 1, -1 / aspectRatio, 1 / aspectRatio, -1, 1);
    }
}

void ProcessKeyPress(unsigned char key, int x, int y) {
    switch (key)
    {
    // Esc
    case 27:
        if (director.gameState == 2) {
            director.gameState = 3;
            glutPostRedisplay();
        }
        else if (director.gameState == 3) {
            director.gameState = 2;
            glutPostRedisplay();
        }
        break;
    // Enter
    case 13:
        if (director.gameState == 1) {
            director.gameState = 2;
            glutPostRedisplay();
        }
        if (director.gameState == 3)
            exit(EXIT_SUCCESS);
        break;
    // Spacebar
    case 32:
        if (director.gameState == 2) {
            clicks.amount++;
            glutPostRedisplay();
        }
        break;
    }
}

bool IsClickedInsideObject(double winX, double winY, float objX, float objY, float objW, float objH) {
    double x = double(winX) / windowWidth * 100;
    double y = double(winY) / windowHeight * 100;
    return (x > objX && y > objY &&
            x < objX + objW && y < objY + objH);
}

void ProcessMousePress(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        switch (director.gameState)
        {
        case 1:
            director.gameState = 2;
            break;
        case 2:
            // Главный объект
            if (IsClickedInsideObject(x, y, MouseObj.x, MouseObj.y, MouseObj.size, MouseObj.size)) {
                MouseObj.Animate();
                clicks.amount++;
            }
            // BtnAutoClicks
            if (IsClickedInsideObject(x, y, btnAutoClicks.x, btnAutoClicks.y, btnAutoClicks.w, btnAutoClicks.h)) {
                btnAutoClicks.OnClick();
            }
            break;
        }
    }
}

void TimerFunc(int) {
    clicks.amount += clicks.perSec;
    glutPostRedisplay();
    glutTimerFunc(1000, TimerFunc, 1);
}

int main(int argc, char **argv) {
    // Инициализация GLUT
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    // Создание окна
	glutInitWindowPosition(400, 100);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Mouse Clicker");
    // glutFullScreen();

    glOrtho(0.0, 100, 100, 0, -1.0, 1.0);

    // Отображение
    glutDisplayFunc(DisplayScene);
    TimerFunc(0);
    // Изменение размера окна
    glutReshapeFunc(WindowResize);

    // Режим прозрачности
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Обработка нажатия клавиш
    glutKeyboardFunc(ProcessKeyPress);
    // Обработка мыши
    glutMouseFunc(ProcessMousePress);

    // Основной цикл GLUT
    glutMainLoop();

    return 1;
}