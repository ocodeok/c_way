#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#define width 65     // Ширина игрового поля
#define height 25    // Высота игрового поля

typedef struct {
    int x, y;   // Положение ракетки на игровом поле
    int w;      // Ширина ракетки
} TRacket;

typedef struct {
    float x, y;
    int ix, iy;
    float alfa;
    float speed;
} TBall;

char mas[height][width + 1]; // Игровое поле, представляющее массив строк
TRacket racket;              // Переменная для хранения состояния ракетки
TBall ball;                  // Переменная для хранения состояния шарика
int hitCnt = 0;
int maxHitCnt = 0;

// Инициализация начального положения и размера ракетки
void initRacket() {
    racket.w = 7;                        // Устанавливаем ширину ракетки
    racket.x = (width - racket.w) / 2;   // Центрируем ракетку по горизонтали
    racket.y = height - 1;               // Устанавливаем ракетку в нижнюю часть поля
}

// Отображение ракетки на игровом поле
void putRacket() {
    for (int i = racket.x; i < racket.x + racket.w; i++)
        mas[racket.y][i] = '@';          // Заполняем игровое поле символами '@' в позиции ракетки
}

// Перемещение ракетки влево или вправо
void moveRacket(int x) {
    racket.x = x;                        // Устанавливаем новое положение ракетки
    if (racket.x < 1)                    // Проверяем границу слева
        racket.x = 1;
    if (racket.x + racket.w >= width)    // Проверяем границу справа
        racket.x = width - 1 - racket.w;
}
// Перемещение шарика на новые координаты
void moveBall(float x, float y) {
    ball.x = x;
    ball.y = y;
    ball.ix = (int)round(ball.x);
    ball.iy = (int)round(ball.y);
}

void initBall() {
    moveBall(2, 2);
    ball.alfa = -1;
    ball.speed = 0.5;
}

// Отображение шарика на игровом поле
void putBall() {
    mas[ball.iy][ball.ix] = '*';
}

// Автоматическое движение шарика
void autoMoveBall() {
    if (ball.alfa < 0) ball.alfa += M_PI * 2;
    if (ball.alfa > M_PI * 2)  ball.alfa -= M_PI * 2;

    TBall b1 = ball;
    moveBall(ball.x + cos(ball.alfa) * ball.speed,
             ball.y + sin(ball.alfa) * ball.speed);

    if ((mas[ball.iy][ball.ix] == '#') || (mas[ball.iy][ball.ix] == '@')) {
        if (mas[ball.iy][ball.ix] == '@')
            hitCnt++;
        if ((ball.ix != b1.ix) && (ball.iy != b1.iy)) {
                if (mas[b1.iy][ball.ix] == mas[ball.iy][b1.ix])
                    b1.alfa = b1.alfa + M_PI;
                else {
                    if (mas[b1.iy][ball.ix] == '#')
                         b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
                    else
                        b1.alfa = (2 * M_PI - b1.alfa);
                }
        } else if (ball.iy == b1.iy) {
            b1.alfa = (2 * M_PI - b1.alfa) + M_PI;
        } else {
            b1.alfa = (2 * M_PI - b1.alfa);
        }
        ball = b1;
        autoMoveBall();
    }
}


// Установка позиции курсора в консоли
void setcur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);  // Перемещаем курсор в заданную позицию
}

// Инициализация игрового поля
void init() {
    // Инициализация первой строки (верхняя граница) и добавление нулевого символа
    for (int i = 0; i < width; i++)
        mas[0][i] = '#';                // Заполняем первую строку символами '#'
    mas[0][width] = '\0';               // Добавляем нулевой символ в конец строки

    // Создание шаблона для внутренних строк
    strncpy(mas[1], mas[0], width + 1); // Копируем первую строку как шаблон
    for (int i = 1; i < width - 1; i++)
        mas[1][i] = ' ';                // Заменяем внутренние символы на пробелы

    // Копирование внутреннего шаблона в остальные строки
    for (int i = 2; i < height; i++)
        strncpy(mas[i], mas[1], width + 1);


    for (int i = 20; i < 50; i++)
        mas[10][i] = '#';
}

// Отображение игрового поля в консоли
void show() {
    for (int i = 0; i < height; i++) {
         printf("%s", mas[i]);          // Печатаем каждую строку массива
         if (i == 3)
            printf("   hit %i", hitCnt);
         if (i == 4)
            printf("   max %i", maxHitCnt);
         if (i < height - 1)
            printf("\n");               // Печатаем новую строку, кроме последней
    }
}

int main(){
    BOOL run = FALSE;
    initRacket();                       // Инициализируем ракетку
    initBall();                         // Инициализируем шарика


    do {
        setcur(0, 0);                   // Сбрасываем курсор в начальную позицию

        if (run)
            autoMoveBall();
        if (ball.iy > height - 2) {
            run = FALSE;
            if (hitCnt > maxHitCnt)
                maxHitCnt = hitCnt;
            hitCnt = 0;
            initBall();                 // Возвращаем мяч на ракетку после падения
        }


        init();                         // Инициализируем игровое поле
        putRacket();                    // Отображаем ракетку
        putBall();                      // Отображаем мачек

        show();                         // Показываем игровое поле в консоли

        if (GetKeyState('A') < 0) moveRacket(racket.x - 1);  // Двигаем ракетку влево
        if (GetKeyState('D') < 0) moveRacket(racket.x + 1);  // Двигаем ракетку вправо
        if (GetKeyState('W') < 0) run = TRUE;
        if (!run)
             moveBall(racket.x + racket.w / 2, racket.y - 1);
        Sleep(10);                                           // Задержка для обновления экрана
    } while(GetKeyState(VK_ESCAPE) >= 0);                    // Продолжаем, пока не нажата клавиша ESC

    return 0;
}
