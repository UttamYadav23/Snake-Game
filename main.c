#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#define HEIGHT 20
#define WIDTH  40

/* Snake */
int x, y;
int tailX[100], tailY[100];
int tailLength = 0;

/* Fruit */
int fruitX, fruitY;

/* Game control */
int direction = 0;   // 1=Up 2=Down 3=Left 4=Right
int score = 0;
int gameOver = 0;

/* Cursor positioning */
void gotoxy(int r, int c)
{
    COORD coord;
    coord.X = c;
    coord.Y = r;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* Hide cursor */
void hideCursor()
{
    CONSOLE_CURSOR_INFO cursor;
    cursor.dwSize = 1;
    cursor.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

/* Draw border ONCE */
void drawBorder()
{
    gotoxy(0, 0);
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1)
                printf("*");
            else
                printf(" ");
        }
        printf("\n");
    }
}

/* Clear only inside area */
void clearInside()
{
    for (int i = 1; i < HEIGHT - 1; i++)
    {
        for (int j = 1; j < WIDTH - 1; j++)
        {
            gotoxy(i, j);
            printf(" ");
        }
    }
}

/* Draw snake, fruit, score */
void drawObjects()
{
    gotoxy(fruitX, fruitY);
    printf("@");

    gotoxy(x, y);
    printf("O");

    for (int i = 0; i < tailLength; i++)
    {
        gotoxy(tailX[i], tailY[i]);
        printf("o");
    }

    gotoxy(HEIGHT, 0);
    printf("Score: %d   W A S D Move | X Exit", score);
}

/* Setup */
void setup()
{
    x = HEIGHT / 2;
    y = WIDTH / 2;

    srand(time(0));
    fruitX = rand() % (HEIGHT - 2) + 1;
    fruitY = rand() % (WIDTH - 2) + 1;
}

/* Input */
void input()
{
    if (kbhit())
    {
        char ch = getch();
        if (ch == 'w' && direction != 2) direction = 1;
        else if (ch == 's' && direction != 1) direction = 2;
        else if (ch == 'a' && direction != 4) direction = 3;
        else if (ch == 'd' && direction != 3) direction = 4;
        else if (ch == 'x') gameOver = 1;
    }
}

/* Game logic */
void logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (direction)
    {
        case 1: x--; break;
        case 2: x++; break;
        case 3: y--; break;
        case 4: y++; break;
    }

    if (x <= 0 || x >= HEIGHT - 1 || y <= 0 || y >= WIDTH - 1)
        gameOver = 1;

    for (int i = 0; i < tailLength; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = 1;

    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % (HEIGHT - 2) + 1;
        fruitY = rand() % (WIDTH - 2) + 1;
        tailLength++;
    }
}

/* Main */
int main()
{
    setvbuf(stdout, NULL, _IONBF, 0); // 🔥 disable buffering
    hideCursor();
    setup();
    drawBorder();

    while (!gameOver)
    {
        gotoxy(0, 0);     // 🔥 prevents flicker
        input();
        logic();
        clearInside();
        drawObjects();
        Sleep(60);
    }

    gotoxy(HEIGHT + 2, 0);
    printf("GAME OVER | Final Score: %d\n", score);
    return 0;
}
