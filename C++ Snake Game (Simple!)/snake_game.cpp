/**
* @file snake_game.cpp
*/

#include <iostream>
#include <conio.h>

using namespace std;

bool gameOver;

/*������ ����*/
const int width = 20;

/*������ ����*/
const int height = 17;

/*���� �Ӹ� x, y ��ǥ ��ġ*/
int x, y;

/*������ x, y ��ǥ ��ġ*/
int fruitX, fruitY;

/*���� ���� x, y ��ǥ ��ġ �迭*/
int tailX[100], tailY[100];

/*���� ���� ����*/
int nTail;

/*����*/
int score;

/*Controls*/
/*
 STOP = 0
 LEFT = 1
 RIGHT = 2
 UP = 3
 DOWN = 4
*/
/*enum == unsigned const int ����*/
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
 * @brief �� ���� �ʱ�ȭ �Լ�
 * 
 */
void Setup() {
    gameOver = false;
    direction = STOP;
    x = width / 2;
    y = height / 2;

    /*������ ���� x, y ��ǥ�� ǥ��*/
    fruitX = rand() % width;
    fruitY = rand() % height;

    /*������ 0���� �ʱ�ȭ*/
    score = 0;
}

/**
 * @fn    void Draw()
 * @brief �� ���� ���� ��� �Լ�
 */
void Draw() {
    /*�ܼ� ȭ�� ����*/
    system("cls");

    /*������ �� ���ʿ� '#'(��) ǥ��*/
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            /*������ �� ���ʿ� '#'(��) ǥ��*/
            if (j == 0)
                cout << "#";

            /*������ ��(i)�� ���� �Ӹ� y ��ǥ ��ġ�� ����*/
            /*������ ��(j)�� ���� �Ӹ� x ��ǥ ��ġ�� ������*/
            /* '*'(���� �Ӹ�) ǥ�� */
            if (i == y && j == x)
                cout << "*";
            /*������ ��(i)�� ������ y ��ǥ ��ġ�� ����*/
            /*������ ��(j)�� ������ x ��ǥ ��ġ�� ������*/
            /* '%'(����) ǥ�� */
            else if (i == fruitY && j == fruitX)
                cout << "%";
            /*������ ��, ���� ���� �Ӹ�, ������ ǥ���� �ʿ䰡 ���� ��ǥ ��ġ�� ���*/
            else {
                /*������ ��, �� ��ǥ ��ġ�� ���� ������ ǥ���ؾ� �ϴ��� üũ�ϴ� �ο�*/
                bool print = false;
                /*���� ���� ������ŭ �ݺ�*/
                for (int k = 0; k < nTail; k++) {
                    /*������ ��(j)�� ���� ���� k��°�� x ��ǥ ��ġ�� ����*/
                    /*������ ��(i)�� ���� ���� k��°�� y ��ǥ ��ġ�� ������*/
                    /* '$'(���� ����) ǥ�� */
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "$";

                        /*������ �ش� ��, �� ��ǥ ��ġ�� ���� ������ ǥ��*/
                        print = true;
                    }
                }

                /*������ �ش� ��, �� ��ǥ ��ġ�� ���� ������ ǥ������ �ʴ� ���*/
                if (!print)
                    cout << " ";
            }

            /*������ �� �����ʿ� '#'(��) ǥ��*/
            if (j == width - 1)
                cout << "#";
        }

        cout << endl;
    }

    /*������ �� �Ʒ��ʿ� '#'(��) ǥ��*/
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    cout << "Score:" << score << endl;
}

/**
 * @fn    void Input()
 * @brief Ű���� �Է��� �޴� �Լ�
 */
void Input() {
    /*Ű���� �Է��� ���� ���*/
    if ( _kbhit() ) {
        /*Ű���� �Է��� ���� ���ڿ� ���� ����ġ ��*/
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
 * @brief �� ���� �˰��� �Լ�
 */
void Algorithm() {
    /*ù ��° ���� ���� x ��ǥ ��ġ ����*/
    int prevX = tailX[0];
    
    /*ù ��° ���� ���� y ��ǥ ��ġ ����*/
    int prevY = tailY[0];

    int prev2X, prev2Y;

    /*ù ��° ���� ���� x ��ǥ ��ġ�� ���� �Ӹ� x ��ǥ ��ġ ����*/
    tailX[0] = x;

    /*ù ��° ���� ���� y ��ǥ ��ġ�� ���� �Ӹ� y ��ǥ ��ġ ����*/
    tailY[0] = y;

    /*�� ��° ���� �������� �� ��° ���� �������� �ݺ�*/
    for (int i = 1; i < nTail; i++) {
        /* (n+1 ��° ���� ���� x, y ��ǥ ��ġ) = (n ��° ���� ���� x, y ��ǥ ��ġ) */

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

    /*���� �Ӹ� �̵� ���⿡ ���� ����ġ ��*/
    switch (direction)
    {
    case LEFT:
        /*���� �Ӹ� ���� x ��ǥ ��ġ - 1*/
        x--;
        break;
    case RIGHT:
        /*���� �Ӹ� ���� x ��ǥ ��ġ + 1*/
        x++;
        break;
    case UP:
        /*���� �Ӹ� ���� y ��ǥ ��ġ - 1*/
        y--;
        break;
    case DOWN:
        /*���� �Ӹ� ���� y ��ǥ ��ġ + 1*/
        y++;
        break;
    default:
        break;
    }

    /*���� �Ӹ� ���� x ��ǥ ��ġ�� ���� �� �����ʿ� ��ų� ���� ���*/
    if (x >= width)
        x = 0;
    /*���� �Ӹ� ���� x ��ǥ ��ġ�� ���� �� ���ʿ� ��ų� ���� ���*/
    else if (x < 0)
        x = width - 1;
    /*���� �Ӹ� ���� y ��ǥ ��ġ�� ���� �� ���� ��ų� ���� ���*/
    if (y >= height)
        y = 0;
    /*���� �Ӹ� ���� y ��ǥ ��ġ�� ���� �� �Ʒ��� ��ų� ���� ���*/
    else if (y < 0)
        y = height - 1;

    /*���� ���� ���� ��ŭ �ݺ�*/
    for (int i = 0; i < nTail; i++)
        /*n��° ���� ������ x ��ǥ ��ġ�� ���� �Ӹ��� x ��ǥ ��ġ�� ����*/
        /*n��° ���� ������ y ��ǥ ��ġ�� ���� �Ӹ��� y ��ǥ ��ġ�� ���� ���*/
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    /*���� �Ӹ��� x ��ǥ ��ġ�� ������ x ��ǥ ��ġ�� ����*/
    /*���� �Ӹ��� y ��ǥ ��ġ�� ������ y ��ǥ ��ġ�� ���� ���*/
    if (x == fruitX && y == fruitY) {
        score += 10;

        /*������ ���� x, y ��ǥ ��ġ�� ���� ����*/
        fruitX = rand() % width;
        fruitY = rand() % height;

        /*���� ���� ���� 1�� ����*/
        nTail++;
    }
}

int main()
{
    /*�� ���� �ʱ�ȭ �Լ�*/
    Setup();

    while (!gameOver) {
        /*�� ���� ���� ��� �Լ�*/
        Draw();

        /*Ű���� �Է��� �޴� �Լ�*/
        Input();

        /*�� ���� �˰��� �Լ�*/
        Algorithm();
    }

    return 0;
}
