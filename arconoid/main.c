#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define width 65     // Ширина игрового поля
#define height 25    // Высота игрового поля

typedef struct {
    int x, y;   // Положение ракетки на игровом поле
    int w;      // Ширина ракетки
} TRacket;

char mas[height][width + 1]; // Игровое поле, представляющее массив строк
TRacket racket;              // Переменная для хранения состояния ракетки

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
}

// Отображение игрового поля в консоли
void show() {
    for (int i = 0; i < height; i++) {
         printf("%s", mas[i]);          // Печатаем каждую строку массива
         if (i < height - 1)
            printf("\n");               // Печатаем новую строку, кроме последней
    }
}

int main(){
    char c;
    initRacket();                       // Инициализируем ракетку

    do {
        setcur(0, 0);                   // Сбрасываем курсор в начальную позицию

        init();                         // Инициализируем игровое поле
        putRacket();                    // Отображаем ракетку
        show();                         // Показываем игровое поле в консоли

        if (GetKeyState('A') < 0) moveRacket(racket.x - 1);  // Двигаем ракетку влево
        if (GetKeyState('D') < 0) moveRacket(racket.x + 1);  // Двигаем ракетку вправо
        Sleep(10);                                           // Задержка для обновления экрана
    } while(GetKeyState(VK_ESCAPE) >= 0);                    // Продолжаем, пока не нажата клавиша ESC

    return 0;
}
