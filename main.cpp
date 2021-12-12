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
    int power = 1;
    int powerMultiplier = 1;
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
    float multiplier = 1.15;
    int owned = 0;
    float price;
    bool maxed = false;

    float x;
    float y;
    float w;
    float h;

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
        DisplayText(x + w - 10, y + 5, clrBlack, defaultFont, ConvertToChar((int)price));
        DisplayText(x + w + 2, y + 5, clrCream, defaultFont, ConvertToChar(owned));
    }

    void DrawMaxed() {
        glColor3fv(clrGreen);
        glBegin(GL_QUADS);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y + h);
            glVertex2f(x, y + h);
            glVertex2f(x, y);
        glColor3fv(clrBlack);
            glVertex2f(x + w + 10, y);
            glVertex2f(x + w + 10, y + h);
            glVertex2f(x + w, y + h);
            glVertex2f(x + w, y);
        glEnd();
        DisplayText(x + w + 1.5, y + 5, clrCream, defaultFont, "MAX");
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

class AutoClicksButton : public UpgradeButton {
public:
    void Display() {
        if (!maxed) {
            this->Draw();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Autoclick");
        } else {
            this->DrawMaxed();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Autoclick");
        }
    }

    void OnClick() {
        if (price <= clicks.amount && !maxed) {
            clicks.amount -= price;
            clicks.perSec += 3;
            owned++;
            if (owned == 50)
                maxed = true;
            price = baseCost * powf(multiplier, owned);
        }
    }

    AutoClicksButton(int upgradeCost, float _x, float _y, float width, float height)
        : UpgradeButton(upgradeCost, _x, _y, width, height) {};
};
AutoClicksButton btnAutoClicks(40, 50, 20, 35, 8);

class ClickPowerButton : public UpgradeButton {
public:
    float multiplier = 1.3;
    void Display() {
        if (!maxed) {
            this->Draw();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Click Power");
        } else {
            this->DrawMaxed();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Click Power");
        }
    }

    void OnClick() {
        if (price <= clicks.amount && !maxed) {
            clicks.amount -= price;
            clicks.power += 1;
            owned++;
            if (owned == 29)
                maxed = true;
            price = baseCost * powf(multiplier, owned);
        }
    }

    ClickPowerButton(int upgradeCost, float _x, float _y, float width, float height)
        : UpgradeButton(upgradeCost, _x, _y, width, height) {};
};
ClickPowerButton btnClickPower(100, 50, 33, 35, 8);

class PowerMultiplierButton : public UpgradeButton {
public:
    float multiplier = 3;

    void Display() {
        if (!maxed) {
            this->Draw();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Power Multiplier");
        } else {
            this->DrawMaxed();
            DisplayText(x + 2, y + 5, clrBlack, defaultFont, "Power Multiplier");
        }
    }

    void OnClick() {
        if (price <= clicks.amount && !maxed) {
            clicks.amount -= price;
            clicks.powerMultiplier += 1;
            owned++;
            if (owned == 2)
                maxed = true;
            price = baseCost * powf(multiplier, owned);
        }
    }

    PowerMultiplierButton(int upgradeCost, float _x, float _y, float width, float height)
        : UpgradeButton(upgradeCost, _x, _y, width, height) {};
};
PowerMultiplierButton btnPowerMultiplier(1000, 50, 46, 35, 8);

class UI {
public:
    void DisplayClicksPerSec() {
        DisplayText(3, 7, clrWhite, defaultFont, "PER SEC:");
        DisplayText(20, 7, clrGreen, defaultFont, ConvertToChar(clicks.perSec));
    }

    void DisplayClickPower() {
        DisplayText(36, 7, clrWhite, defaultFont, "CLICK POWER:");
        DisplayText(61, 7, clrGreen, defaultFont, ConvertToChar(clicks.power));
    }

    void DisplayClickCount() {
        DisplayText(73, 7, clrWhite, defaultFont, "CLICKS:");
        DisplayText(88, 7, clrGreen, defaultFont, ConvertToChar((int)clicks.amount));
    }

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

        btnAutoClicks.Display();
        btnClickPower.Display();
        btnPowerMultiplier.Display();
        DisplayClickCount();
        DisplayClickPower();
        DisplayClicksPerSec();
    }

    void DrawIntro() {
        DisplayText(35, 50, clrCream, GLUT_BITMAP_TIMES_ROMAN_24, "CLICK TO START");
        DisplayText(10, 85, clrWhite, GLUT_BITMAP_HELVETICA_12, "Made by Artem Maevski");
        DisplayText(10, 90, clrWhite, GLUT_BITMAP_HELVETICA_12, "Dec 2021");
    }

    void DrawDarkOverlay() {
        glColor4f(0.0, 0.0, 0.0, 0.6);
        glBegin(GL_QUADS);
            glVertex2i(0, 0);
            glVertex2i(0, 100);
            glVertex2i(100, 100);
            glVertex2i(100, 0);
        glEnd();
    }

    void DrawPause() {
        DrawDarkOverlay();
        DisplayText(23, 50, clrWhite, GLUT_BITMAP_HELVETICA_18, "ARE YOU SURE YOU WANT TO EXIT?");
    }

    void DrawEnd() {
        DrawDarkOverlay();
        DisplayText(39, 45, clrGreen, GLUT_BITMAP_9_BY_15, "CONGRATULATIONS!");
        DisplayText(32, 50, clrGreen, GLUT_BITMAP_9_BY_15, "You've reached 50k points");
    }
};
UI ui;

class ObjSquare {
public:
    float x = 15;
    float y = 40;
    float size = 20;
    void Draw() {
        glBegin(GL_QUADS);
        glColor3fv(clrGreen);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y + size);
            glVertex2f(x, y + size);
            glVertex2f(x, y);
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
ObjSquare SquareObj;

class GameDirector {
public:
    int gameState = 1;

    void StartScreen() {
        ui.DrawIntro();
    }

    void GameProcess() {
        ui.DrawHUD();
        SquareObj.Draw();
    }

    void GamePause() {
        ui.DrawPause();
    }

    void EndGame() {
        ui.DrawEnd();
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
        director.GameProcess(); // Игра продолжается на фоне
        director.GamePause();
        break;
    case 4:
        director.EndGame();
        break;
    default:
        return;
    }

    if(clicks.amount >= 50000)
        director.gameState = 4;

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

    glOrtho(-aspectRatio, aspectRatio, -1, 1, -1, 1);
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
        if (director.gameState == 3 || director.gameState == 4)
            exit(EXIT_SUCCESS);
        break;
    // Spacebar
    case 32:
        if (director.gameState == 2) {
            clicks.amount += clicks.power * clicks.powerMultiplier;
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
            if (IsClickedInsideObject(x, y, SquareObj.x, SquareObj.y, SquareObj.size, SquareObj.size)) {
                SquareObj.Animate();
                clicks.amount += clicks.power * clicks.powerMultiplier;
            }
            // Autoclicks
            if (IsClickedInsideObject(x, y, btnAutoClicks.x, btnAutoClicks.y, btnAutoClicks.w, btnAutoClicks.h)) {
                btnAutoClicks.OnClick();
            }
            // Click Power
            if (IsClickedInsideObject(x, y, btnClickPower.x, btnClickPower.y, btnClickPower.w, btnClickPower.h)) {
                btnClickPower.OnClick();
            }
            if (IsClickedInsideObject(x, y, btnPowerMultiplier.x, btnPowerMultiplier.y, btnPowerMultiplier.w, btnPowerMultiplier.h)) {
                btnPowerMultiplier.OnClick();
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
	glutCreateWindow("Square Clicker");


    // Отображение
    glutDisplayFunc(DisplayScene);
    glOrtho(0.0, 100, 100, 0, -1.0, 1.0);
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