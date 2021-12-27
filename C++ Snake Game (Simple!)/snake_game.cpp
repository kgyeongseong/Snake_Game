/**
* @file snake_game.cpp
*/

#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;

/*보드의 면적*/
const int width = 20;

/*보드의 높이*/
const int height = 17;

/*뱀의 머리 x, y 좌표 위치*/
int x, y;

/*과일의 x, y 좌표 위치*/
int fruitX, fruitY;

/*뱀의 꼬리 x, y 좌표 위치 배열*/
int tailX[100], tailY[100];

/*뱀의 꼬리 갯수*/
int nTail;

/*점수*/
int score;

/*Controls*/
/*
 STOP = 0
 LEFT = 1
 RIGHT = 2
 UP = 3
 DOWN = 4
*/
/*enum == unsigned const int 집합*/
enum Direction
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

Direction direction;

/**
 * @fn    void Setup()
 * @brief 뱀 게임 초기화 함수
 * 
 */
void Setup() {
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;

    /*과일을 랜덤 x, y 좌표에 표시*/
    fruitX = rand() % width;
    fruitY = rand() % height;

    /*점수를 0으로 초기화*/
    score = 0;
}

/**
 * @fn    void Draw()
 * @brief 뱀 게임 보드 출력 함수
 */
void Draw() {
    /*콘솔 화면 정리*/
    system("cls");

    /*보드의 맨 위쪽에 '#'(벽) 표시*/
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            /*보드의 맨 왼쪽에 '#'(벽) 표시*/
            if (j == 0)
                cout << "#";

            /*보드의 행(i)가 뱀의 머리 y 좌표 위치와 같고*/
            /*보드의 열(j)가 뱀의 머리 x 좌표 위치와 같으면*/
            /* '*'(뱀의 머리) 표시 */
            if (i == y && j == x)
                cout << "*";
            /*보드의 행(i)가 과일의 y 좌표 위치와 같고*/
            /*보드의 열(j)가 과일의 x 좌표 위치와 같으면*/
            /* '%'(과일) 표시 */
            else if (i == fruitY && j == fruitX)
                cout << "%";
            /*보드의 행, 열에 뱀의 머리, 과일을 표시할 필요가 없는 좌표 위치인 경우*/
            else {
                /*보드의 행, 열 좌표 위치에 뱀의 꼬리를 표시해야 하는지 체크하는 부울*/
                bool print = false;
                /*뱀의 꼬리 갯수만큼 반복*/
                for (int k = 0; k < nTail; k++) {
                    /*보드의 열(j)가 뱀의 꼬리 k번째의 x 좌표 위치와 같고*/
                    /*보드의 행(i)가 뱀의 꼬리 k번째의 y 좌표 위치와 같으면*/
                    /* '$'(뱀의 꼬리) 표시 */
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "$";

                        /*보드의 해당 행, 열 좌표 위치에 뱀의 꼬리를 표시*/
                        print = true;
                    }
                }

                /*보드의 해당 행, 열 좌표 위치에 뱀의 꼬리를 표시하지 않는 경우*/
                if (!print)
                    cout << " ";
            }

            /*보드의 맨 오른쪽에 '#'(벽) 표시*/
            if (j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    /*보드의 맨 아래쪽에 '#'(벽) 표시*/
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score:" << score << endl;
}

/**
 * @fn    void Input()
 * @brief 키보드 입력을 받는 함수
 */
void Input() {
    /*키보드 입력을 받은 경우*/
    if ( _kbhit() ) {
        /*키보드 입력을 받은 문자에 따른 스위치 문*/
        switch ( _getch() )
        {
        case 'a':
            direction = LEFT;
            break;
        case 'd':
            direction = RIGHT;
            break;
        case 'w':
            direction = UP;
            break;
        case 's':
            direction = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        default:
            break;
        }
    }
}

/**
 * @fn    void Algorithm()
 * @brief 뱀 게임 알고리즘 함수
 */
void Algorithm() {
    /*첫 번째 뱀의 꼬리 x 좌표 위치 저장*/
    int prevX = tailX[0];
    
    /*첫 번째 뱀의 꼬리 y 좌표 위치 저장*/
    int prevY = tailY[0];

    int prev2X, prev2Y;

    /*첫 번째 뱀의 꼬리 x 좌표 위치에 뱀의 머리 x 좌표 위치 저장*/
    tailX[0] = x;

    /*첫 번째 뱀의 꼬리 y 좌표 위치에 뱀의 머리 y 좌표 위치 저장*/
    tailY[0] = y;

    /*두 번째 뱀의 꼬리부터 끝 번째 뱀의 꼬리까지 반복*/
    for (int i = 1; i < nTail; i++) {
        /* (n+1 번째 뱀의 꼬리 x, y 좌표 위치) = (n 번째 뱀의 꼬리 x, y 좌표 위치) */

        /* ex1) prev2X = tailX[1], prev2Y = tailY[1] */
        /* ex2) prev2X = tailX[2], prev2Y = tailY[2] */
        prev2X = tailX[i];
        prev2Y = tailY[i];

        /* ex1) tailX[1] = tailX[0], tailY[1] = tailY[0] */
        /* ex2) tailX[2] = tailX[1], tailY[2] = tailY[1] */
        tailX[i] = prevX;
        tailY[i] = prevY;

        /* ex1) prevX = tailX[1], prevY = tailY[1] */
        /* ... */
        prevX = prev2X;
        prevY = prev2Y;
    }

    /*뱀의 머리 이동 방향에 따른 스위치 문*/
    switch (direction)
    {
    case LEFT:
        /*뱀의 머리 셀의 x 좌표 위치 - 1*/
        x--;
        break;
    case RIGHT:
        /*뱀의 머리 셀의 x 좌표 위치 + 1*/
        x++;
        break;
    case UP:
        /*뱀의 머리 셀의 y 좌표 위치 - 1*/
        y--;
        break;
    case DOWN:
        /*뱀의 머리 셀의 y 좌표 위치 + 1*/
        y++;
        break;
    default:
        break;
    }

    /*뱀의 머리 셀의 x 좌표 위치가 벽의 맨 오른쪽에 닿거나 넘은 경우*/
    if (x >= width)
        x = 0;
    /*뱀의 머리 셀의 x 좌표 위치가 벽의 맨 왼쪽에 닿거나 넘은 경우*/
    else if (x < 0)
        x = width - 1;
    /*뱀의 머리 셀의 y 좌표 위치가 벽의 맨 위에 닿거나 넘은 경우*/
    if (y >= height)
        y = 0;
    /*뱀의 머리 셀의 y 좌표 위치가 벽의 맨 아레에 닿거나 넘은 경우*/
    else if (y < 0)
        y = height - 1;

    /*뱀의 꼬리 갯수 만큼 반복*/
    for (int i = 0; i < nTail; i++)
        /*n번째 뱀의 꼬리의 x 좌표 위치가 뱀의 머리의 x 좌표 위치와 같고*/
        /*n번째 뱀의 꼬리의 y 좌표 위치가 뱀의 머리의 y 좌표 위치와 같은 경우*/
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    /*뱀의 머리의 x 좌표 위치가 과일의 x 좌표 위치와 같고*/
    /*뱀의 머리의 y 좌표 위치가 과일의 y 좌표 위치와 같은 경우*/
    if (x == fruitX && y == fruitY) {
        score += 10;

        /*보드의 랜덤 x, y 좌표 위치에 과일 저장*/
        fruitX = rand() % width;
        fruitY = rand() % height;

        /*뱀의 꼬리 갯수 1개 증가*/
        nTail++;
    }
}

int main()
{
    /*뱀 게임 초기화 함수*/
    Setup();

    while (!gameOver) {
        /*뱀 게임 보드 출력 함수*/
        Draw();

        /*키보드 입력을 받는 함수*/
        Input();

        /*뱀 게임 알고리즘 함수*/
        Algorithm();
    }

    return 0;
}
