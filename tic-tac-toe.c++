#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

// TIC_TAC_TOE CLASS (BASE CLASS)

class tic_tac_toe
{
protected:
    // evaluation factors
    static int diag1, diag2, col[3], row[3], x, y;
    // matrix
    static char arr[3][3];

public:
    static int turn;
    void print_matrix()
    {
        cout << "\n";
        cout << " " << arr[0][0] << "  |  " << arr[0][1] << "  | " << arr[0][2] << endl;
        cout << "___ | "
             << "___ | "
             << "___ \n\n";
        cout << " " << arr[1][0] << "  |  " << arr[1][1] << "  | " << arr[1][2] << endl;
        cout << "___ | "
             << "___ | "
             << "___ \n\n";
        cout << " " << arr[2][0] << "  |  " << arr[2][1] << "  | " << arr[2][2] << endl;
        cout << "    | "
             << "    | "
             << "    \n\n";
    }

    int computer_choice()
    {
        static vector<int> moves = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        int val;

        for (int k = 0; k < 2; k++)
        {
            (k == 0) ? (val = -2) : (val = 2);
            // checks wheter there is any 2 or -2 in row
            for (int i = 0; i < 3; i++)
            {
                if (row[i] == val)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (arr[i][j] == ' ')
                        {
                            return 3 * i + (j + 1);
                        }
                    }
                }
            }

            // checks wheter there is any 2 or -2 in col
            for (int i = 0; i < 3; i++)
            {
                if (col[i] == val)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (arr[j][i] == ' ')
                        {
                            return 3 * j + (i + 1);
                        }
                    }
                }
            }

            // checks wheter there is any 2 or -2 in diag1
            if (diag1 == val)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (arr[i][i] == ' ')
                    {
                        return 3 * i + i + 1;
                    }
                }
            }

            // checks wheter there is any 2 or -2 in diag2
            if (diag2 == val)
            {
                for (int i = 0; i < 3; i++)
                {
                    if (arr[i][2 - i] == ' ')
                    {
                        return 3 * i + (2 - i) + 1;
                    }
                }
            }
        }
        // if there is no 2 or -2 we choose any random element fron the moves vector
        srand(time(0));

        int random = rand() % moves.size();
        val = moves[random];
        moves.erase(moves.begin() + random);

        return val;
    }
};

int tic_tac_toe::diag1, tic_tac_toe::diag2, tic_tac_toe::col[3] = {};
int tic_tac_toe::row[3] = {}, tic_tac_toe::x, tic_tac_toe::y, tic_tac_toe::turn;
char tic_tac_toe::arr[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

// EVALUATION CLASS

class evaluation : private tic_tac_toe
{
public:
    bool evaluate(int mode)
    {
        if (diag1 == 3 or diag1 == -3 or diag2 == 3 or diag2 == -3 or row[x] == 3 or row[x] == -3 or col[y] == 3 or col[y] == -3)
        {
            if (mode == 2)
                (turn % 2 == 0) ? cout << "palyer 1 won!\n\n" : cout << "player 2 won!\n\n";
            else
                (turn % 2 == 0) ? cout << "You won!\n\n" : cout << " computer won!\n\n";
            return true;
        }
        return false;
    }

    // updates the evaluation factors
    void update()
    {
        if (y == x)
        {
            (turn % 2 == 0) ? diag1++ : diag1--;
        }
        if (x + y == 2)
        {
            (turn % 2 == 0) ? diag2++ : diag2--;
        }
        (turn % 2 == 0) ? col[y]++ : col[y]--;
        (turn % 2 == 0) ? row[x]++ : row[x]--;
    }
};

// PLAYER CLASS

class player : private tic_tac_toe
{
    char symbol;

public:
    void set_symbol(char c)
    {
        symbol = c;
    }

    void make_move();
    void make_move(int mode);
};

void player::make_move()
{
start2:
    int val;
    cout << "Enter box number - ";
    cin >> val;

    x = (val - 1) / 3;
    y = (val - 1) % 3;

    if (val > 9 or arr[x][y] == 'X' or arr[x][y] == 'O')
    {
        cout << "Retry!\n";
        cout << "Either the box is filled or you entered wrong number\n";
        goto start2;
    }
    char c = symbol;

    // updating matrix
    arr[x][y] = c;
}
void player::make_move(int mode)
{
start:
    int val = computer_choice();

    x = (val - 1) / 3;
    y = (val - 1) % 3;

    if (arr[x][y] != ' ')
    {
        goto start;
    }

    char c = symbol;

    // updating matrix
    arr[x][y] = c;
}

// MAIN FUNCTION

int main()
{
    tic_tac_toe game;
    player p1, p2;
    evaluation eval;

    char choice;
    int mode;

    cout << "\n\nWelcome to the game \n\n";

    cout << "To play against computer enter 1 otherwise 2 - ";
    cin >> mode;

    if (mode != 1 and mode != 2)
    {
        mode = 2;
    }

    cout << "\n\n";

start1:
    cout << "Please choose between X and O - ";
    cin >> choice;

    if (choice == 'o' or choice == 'x')
    {
        choice -= ('a' - 'A');
    }

    if (choice != 'X' and choice != 'O')
    {
        cout << "wrong symbol, please try again\n";
        goto start1;
    }

    p1.set_symbol(choice);
    (choice == 'X') ? (p2.set_symbol('O')) : (p2.set_symbol('X'));

    cout << "\n\n";

    cout << "Boxes are numbered in the following manner \n\n";
    cout << " 1  2  3\n\n";
    cout << " 4  5  6\n\n";
    cout << " 7  8  9\n\n";

    while (game.turn < 9)
    {
        if (mode == 2)
        {
            (game.turn % 2) ? (cout << "Player 2 ") : (cout << "Player 1 ");
        }
        else
        {
            (game.turn % 2) ? (cout << "Computer's move ") : (cout << "");
        }

        if (mode == 2)
        {
            (game.turn % 2 == 0) ? (p1.make_move()) : (p2.make_move());
        }
        else
        {
            (game.turn % 2 == 0) ? (p1.make_move()) : (p2.make_move(mode));
        }

        eval.update(); // updating evaluation factors

        game.print_matrix();

        bool should_break = eval.evaluate(mode);

        if (should_break)
            break;

        game.turn++;
    }

    if (game.turn == 9)
    {
        cout << "Draw\n\n";
    }
}