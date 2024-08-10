#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main() {
    //        X  Y
    char mas[10][21];
    int i;
    int x = 10, y = 5;
    int ox, oy;
    int ax = 5, ay = 3;
    int apples = 0;

    char key;

    srand(time(NULL));

    do {
        sprintf(mas[0], "####################");
        for (i = 1; i < 9; i++) {
             sprintf(mas[i], "#                  #");
        }
        sprintf(mas[9], "####################");

        mas[y][x] = '@';
        mas[ay][ax] = '*';

        system("cls");
        for(i = 0; i < 10; i++) {
            printf("%s\n", mas[i]);
        }
        printf("\nApples: %d", apples);

        key = getch();

        ox = x;
        oy = y;

         // Перемещение '@'
        if (key == 'w') y--;
        if (key == 's') y++;
        if (key == 'd') x++;
        if (key == 'a') x--;

        // Проверка выхода за игровое поле
        if (mas[y][x] == '#') {
            x = ox;
            y = oy;
        }

        // Проверка совпадение позиции '*' и '@'
        if ((x == ax) && (y == ay)) {
            ax = rand() * 1.0 / RAND_MAX * 18 + 1;
            ay = rand() * 1.0 / RAND_MAX * 8 + 1;

            apples++;
        }
    } while(key != 'e');

    return 0;
}
