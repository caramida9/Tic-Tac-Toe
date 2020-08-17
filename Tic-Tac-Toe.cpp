#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
using namespace std;

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ENTER 13
#define ESCAPE 27

char board[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };

///////////////GAMEPLAY VARIABLES///////////////////////
int row, column;
char turn = 'X';
char player_item = 'X';
char ai_item = 'O';
bool draw = false;
int gameDifficulty;

/////////////UI NAVIGATION VARIABLES/////////////////////
int menu_pos = 1;
bool startGame = false;
bool exitGame = false;
bool pauseGame = false;
int navigation;

//////////////COLOR VARIABLES//////////////
int textColor;
int XColor;
int OColor;

////////////////FILES/////////////////////
fstream optionFile;
fstream saveFile;

void reset_board()
{
    //reseting game board and turn
    board[0][0] = '1';
    board[0][1] = '2';
    board[0][2] = '3';
    board[1][0] = '4';
    board[1][1] = '5';
    board[1][2] = '6';
    board[2][0] = '7';
    board[2][1] = '8';
    board[2][2] = '9';
    turn = 'X';
    draw = false;
}

void save_to_file()
{
    saveFile.open("save.txt", ios::out | ios::trunc);
    saveFile << turn;
    saveFile << player_item;
    saveFile << ai_item;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            saveFile << board[i][j];
        }
    }
    saveFile.close();
}

int load_from_file()
{
    saveFile.open("save.txt");
    if (!saveFile.is_open())
    {
        return 0;
    }
    if (saveFile.peek() == fstream::traits_type::eof())
    {
        return 0;
    }
    saveFile >> turn;
    saveFile >> player_item;
    saveFile >> ai_item;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            saveFile >> board[i][j];
        }
    }
    saveFile.close();
    return 1;
}

void display_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
    system("cls");
    cout << "\t\tT I C K -- T A C -- T O E -- G A M E\t\t";
    cout << "\n\t\t\tFOR 2 PLAYERS\n\t\t";
    cout << "\n\t\t\t -- MAIN MENU --\n\t\t";
    if (menu_pos == 1)
    {
        cout << "\n\t\t >New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 2)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t\t >Start first [X] \t\t";
        cout << "\n\t\t\t Start second [O] \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 3)
    {

        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t\t Start first [X] \t\t";
        cout << "\n\t\t\t >Start second [O] \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 4)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t >Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 5)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t >Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 6)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t >Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 7)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        if (gameDifficulty == 1)
        {
            cout << "\n\t\t\t >Difficulty : Easy";
        }
        else
        {
            cout << "\n\t\t\t >Difficulty : Hard";
        }
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if(menu_pos == 8)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty";
        cout << "\n\t\t\t >Colors \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 9)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty \t\t";
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t\t\t >Menu Text Color \t\t";
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 10)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty \t\t";
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t\t\t Menu Text Color \t\t";
        cout << "\n\t\t\t\t >Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 11)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty";
        cout << "\n\t\t\t Colors";
        cout << "\n\t\t\t\t Menu Text Color \t\t";
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t >Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit Game \t\t";
    }
    else if (menu_pos == 12)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t >Exit Game \t\t";
    }
    else if (menu_pos == 13)
    {
        cout << "\n\t\t -- HOW TO PLAY -- \t\t";
        cout << "\n This is a generic Tic-Tac-Toe console game. You can use the arrow keys, enter and escape to navigate the menu.";
        cout << "\n You can change the difficulty and color of the game from the options. When starting a new game you can go first ";
        cout << "\n by picking the X, or you can go second and play with O. In-game you will have a 3x3 board numbered from 1 to 9.";
        cout << "\n Pick the position of your move using the numbers 1-9. In order to win you must have 3 Xs(or Os) in a row, colomn";
        cout << "\n or diagonal. You can pause the game with escape and change different options or save in order to keep playing later.";
        cout << "\n\n\t\t >Return to menu";
    }
    else if (menu_pos == 14)
    {
        cout << "\n\t\t New Game \t\t";
        cout << "\n\t\t >No Saved Game Exists \t\t";
        cout << "\n\t\t Instructions \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit Game \t\t";
    }
}

void display_pause_menu()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
    system("cls");
    cout << "\t\tT I C K -- T A C -- T O E -- G A M E\t\t";
    cout << "\n\t\t\tFOR 2 PLAYERS\n\t\t";
    cout << "\n\t\t\t -- PAUSE MENU --\n\t\t";
    if (menu_pos == 1)
    {
        cout << "\n\t\t >Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 2)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t\t >Start first [X] \t\t";
        cout << "\n\t\t\t Start second [O] \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 3)
    {

        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t\t Start first [X] \t\t";
        cout << "\n\t\t\t >Start second [O] \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 4)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t >Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 5)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t >Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 6)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t >Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 7)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        if (gameDifficulty == 1)
        {
            cout << "\n\t\t\t >Difficulty : Easy";
        }
        else
        {
            cout << "\n\t\t\t >Difficulty : Hard";
        }
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 8)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty";
        cout << "\n\t\t\t >Colors \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 9)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty \t\t";
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t\t\t >Menu Text Color \t\t";
        cout << "\n\t\t\t\t >Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 10)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty \t\t";
        cout << "\n\t\t\t Colors \t\t";
        cout << "\n\t\t\t\t Menu Text Color \t\t";
        cout << "\n\t\t\t\t >Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 11)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t\t Difficulty";
        cout << "\n\t\t\t Colors";
        cout << "\n\t\t\t\t Menu Text Color \t\t";
        cout << "\n\t\t\t\t Color of ";
        SetConsoleTextAttribute(hConsole, XColor);
        cout << "X";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t\t\t >Color of ";
        SetConsoleTextAttribute(hConsole, OColor);
        cout << "O";
        SetConsoleTextAttribute(hConsole, textColor);
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 12)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t Save Game \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t >Exit to Main Menu \t\t";
    }
    else if (menu_pos == 13)
    {
        cout << "\n\t\t Restart Game \t\t";
        cout << "\n\t\t >Saved! \t\t";
        cout << "\n\t\t Load Game \t\t";
        cout << "\n\t\t Options \t\t";
        cout << "\n\t\t Exit to Main Menu \t\t";
    }
    else if (menu_pos == 14)
    {
    cout << "\n\t\t Restart Game \t\t";
    cout << "\n\t\t Save Game \t\t";
    cout << "\n\t\t >No Saved Game exists \t\t";
    cout << "\n\t\t Options \t\t";
    cout << "\n\t\t Exit to Main Menu \t\t";
    }
}

void menu_navigation()
{
    navigation = _getch();
    if (navigation == ESCAPE && (menu_pos == 1 || menu_pos == 4 || menu_pos == 5 || menu_pos == 6 || menu_pos == 12))
    {
        exitGame = true;
        return;
    }

    if (menu_pos == 1)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 4;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 12;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 2;
        }
    }
    else if (menu_pos == 2)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 3;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            startGame = true;
            player_item = 'X';
            ai_item = 'O';
            menu_pos = 1;
        }
    }
    else if (menu_pos == 3)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 2;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 2;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            startGame = true;
            player_item = 'O';
            ai_item = 'X';
            menu_pos = 1;
        }
    }
    else if (menu_pos == 4)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            int fail;
            fail = load_from_file();//checking if a saved game exists
            if (fail == 0)
            {
                menu_pos = 14;
            }
            else
            {
                startGame = true;
            }
        }
    }
    else if (menu_pos == 5)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 4;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 13;
        }
    }
    else if (menu_pos == 6)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 12;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 7;
        }
    }
    else if (menu_pos == 7)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            if (gameDifficulty == 1) gameDifficulty = 2;
            else gameDifficulty = 1;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 8;
        }
    }
    else if (menu_pos == 8)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 9;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 7;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 7;
        }
    }
    else if (menu_pos == 9)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            textColor = 1 + (textColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 11;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 10;
        }
    }
    else if (menu_pos == 10)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            XColor = 4 + (XColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 9;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 11;
        }
    }
    else if (menu_pos == 11)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            OColor = 7 + (OColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 10;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 9;
        }
    }
    else if (menu_pos == 12)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 6;
        }
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            exitGame = true;
            return;
        }
    }
    else if (menu_pos == 13)
    {
        if (navigation == KEY_LEFT || navigation == KEY_RIGHT || navigation == ENTER || navigation == ESCAPE)
        {
            menu_pos = 5;
        }
    }
    else if (menu_pos == 14)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 1;
        }
    }
    else
    {
        return;
    }

}

void pause_menu_navigation()
{
    navigation = _getch();
    if (navigation == ESCAPE && (menu_pos == 1 || menu_pos == 4 || menu_pos == 5 || menu_pos == 6 || menu_pos == 12))
    {
        pauseGame = false;
        return;
    }

    if (menu_pos == 1)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 4;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 12;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 2;
        }
    }
    else if (menu_pos == 2)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 3;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            reset_board();

            player_item = 'X';
            ai_item = 'O';
            menu_pos = 1;

            startGame = true;
            pauseGame = false;
            
        }
    }
    else if (menu_pos == 3)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 2;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 2;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            reset_board();

            player_item = 'O';
            ai_item = 'X';
            menu_pos = 1;

            startGame = true;
            pauseGame = false;
            
        }
    }
    else if (menu_pos == 4)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            save_to_file();
            menu_pos = 13;
        }
    }
    else if (menu_pos == 5)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 4;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            int fail;
            fail = load_from_file();
            if (fail == 0)
            {
                menu_pos = 14;
            }
            else
            {
                pauseGame = false;
            }
        }
    }
    else if (menu_pos == 6)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 12;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 7;
        }
    }
    else if (menu_pos == 7)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            if (gameDifficulty == 1) gameDifficulty = 2;
            else gameDifficulty = 1;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 8;
        }
    }
    else if (menu_pos == 8)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            menu_pos = 9;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 7;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 7;
        }
    }
    else if (menu_pos == 9)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            textColor = 1 + (textColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 11;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 10;
        }
    }
    else if (menu_pos == 10)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            XColor = 4 + (XColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 9;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 11;
        }
    }
    else if (menu_pos == 11)
    {
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            OColor = 7 + (OColor + 1) % 3;
        }
        else if (navigation == KEY_LEFT || navigation == ESCAPE)
        {
            menu_pos = 8;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 10;
        }
        else if (navigation == KEY_DOWN)
        {
            menu_pos = 9;
        }
    }
    else if (menu_pos == 12)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 1;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 6;
        }
        if (navigation == KEY_RIGHT || navigation == ENTER)
        {
            reset_board();
            startGame = false;
            pauseGame = false;
            return;
        }
    }
    else if (menu_pos == 13)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 5;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 1;
        }
    }
    else if (menu_pos == 14)
    {
        if (navigation == KEY_DOWN)
        {
            menu_pos = 6;
        }
        else if (navigation == KEY_UP)
        {
            menu_pos = 4;
        }
    }
    else
    {
        return;
    }

}

void display_board() {

    //Rander Game Board LAYOUT
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    cout << "\t\t\t     |     |     \n";
    for (int i = 0; i < 3; i++)
    {
        cout << "\t\t\t  ";
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == 'X')
            {
                SetConsoleTextAttribute(hConsole, XColor);
                cout << board[i][j];
            }
            else if (board[i][j] == 'O')
            {
                SetConsoleTextAttribute(hConsole, OColor);
                cout << board[i][j];
            }
            else
            {
                SetConsoleTextAttribute(hConsole, textColor);
                cout << board[i][j];
            }

            SetConsoleTextAttribute(hConsole, textColor);
            if (j < 2)
            {
                cout << "  |  ";
            }
        }
        if (i < 2)
        {
            cout << " \n";
            cout << "\t\t\t_____|_____|_____\n";
            cout << "\t\t\t     |     |     \n";
        }
        else 
        {
            cout << " \n";
            cout << "\t\t\t     |     |     \n";
        }
    }
}

void display_ingame_UI()
{
    cout << "\t\tT I C K -- T A C -- T O E -- G A M E\t\t";
    cout << "\n\t\t\tFOR 2 PLAYERS\n\t\t";
    cout << "\n\t\t Press ESC to pause. Press a number to place your move\n\t\t";
    cout << "PLAYER - [" << player_item << "]\t AI - [" << ai_item <<"]\n\n";
}

bool check_valid_move(int move)
{
    //checking if a move is inside the board
    switch (move) {
    case 1: row = 0; column = 0; break;
    case 2: row = 0; column = 1; break;
    case 3: row = 0; column = 2; break;
    case 4: row = 1; column = 0; break;
    case 5: row = 1; column = 1; break;
    case 6: row = 1; column = 2; break;
    case 7: row = 2; column = 0; break;
    case 8: row = 2; column = 1; break;
    case 9: row = 2; column = 2; break;
    default:
        return false;
    }

    if (turn == 'X' && board[row][column] != 'X' && board[row][column] != 'O')
    {
        //updating the position for 'X' symbol if
        //it is not already occupied
        board[row][column] = 'X';
        turn = 'O';
        return true;
    }
    else if (turn == 'O' && board[row][column] != 'X' && board[row][column] != 'O')
    {
        //updating the position for 'O' symbol if
        //it is not already occupied
        board[row][column] = 'O';
        turn = 'X';
        return true;
    }
    else
    {
        //if input position already filled
        return false;
    }
}

int ai_to_move(char item)
{
    //checking if the ai can place an item somewhere in order to win or block the player from winning
    int ai_choice = -1;
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == item && board[i][1] == item && board[i][2] != ai_item && board[i][2] != player_item)
        {
            ai_choice = (i+1) * 3;
            break;
        }
        if (board[i][0] == item && board[i][2] == item && board[i][1] != ai_item && board[i][1] != player_item)
        {                                                                        
            ai_choice = i * 3 + 2;                                               
            break;                                                               
        }                                                                        
        if (board[i][1] == item && board[i][2] == item && board[i][0] != ai_item && board[i][0] != player_item)
        {                                                                        
            ai_choice = i * 3 + 1;                                               
            break;                                                               
        }                                                                        
        if (board[0][i] == item && board[1][i] == item && board[2][i] != ai_item && board[2][i] != player_item)
        {                                                                        
            ai_choice = 7 + i;                                                   
            break;                                                               
        }                                                                        
        if (board[0][i] == item && board[2][i] == item && board[1][i] != ai_item && board[1][i] != player_item)
        {                                                                        
            ai_choice = 4 + i;                                                   
            break;                                                               
        }                                                                        
        if (board[1][i] == item && board[2][i] == item && board[0][i] != ai_item && board[0][i] != player_item)
        {
            ai_choice = 1 + i;
            break;
        }
    }
    if (ai_choice == -1)
    {
        if (board[0][0] == item && board[1][1] == item)
        {
            ai_choice = 9;
        }
        else if (board[0][0] == item && board[2][2] == item)
        {
            ai_choice = 5;
        }
        else if (board[1][1] == item && board[2][2] == item)
        {
            ai_choice = 1;
        }
        else if (board[0][2] == item && board[1][1] == item)
        {
            ai_choice = 7;
        }
        else if (board[0][2] == item && board[2][0] == item)
        {
            ai_choice = 5;
        }
        else if (board[1][1] == item && board[2][0] == item)
        {
            ai_choice = 3;
        }
    }
    return ai_choice;
}

void get_ai_choice(int difficulty)
{
    //getting the ai position choice based on the difficulty
    int ai_choice;
    if (difficulty == 1)
    {
        //on low difficulty he will move randomly
        bool valid = false;
        srand(time(NULL));
        while (!valid)
        {
            ai_choice = rand() % 10 + 1;
            valid = check_valid_move(ai_choice);
        }
        
    }
    else if (difficulty == 2)
    {
        //on difficulty number 2 he will try to win
        bool valid = false;
        ai_choice = ai_to_move(ai_item);
        valid = check_valid_move(ai_choice);
        if (!valid)
        {
            ai_choice = ai_to_move(player_item);//or block the player
            valid = check_valid_move(ai_choice);
            if (!valid)
            {
                valid = check_valid_move(5); // we will prioritize the center
                for (int i = 1; i <= 9 && valid != true ; i++)
                {
                    valid = check_valid_move(i);
                }
            }
        }
    }
}

void game_turn() 
{
    if (turn == player_item) 
    {
        //getting the move from the player
        int choice;
        cout << "\n\t\tPlayer turn : ";
        choice = _getch();

        if (choice == ESCAPE)
        {
            pauseGame = true;
            return;
        }
        else if (choice > 48 && choice < 58)
        {
            //converting from ascii to int
            choice = choice - 48;
        }

        while (!check_valid_move(choice))
        {
            cout << "Invalid Move!";
            cout << "\n\t\tPlayer turn : ";
            choice = _getch();

            if (choice == ESCAPE)
            {
                pauseGame = true;
                return;
            }
            else if (choice > 48 && choice < 58)
            {
                //converting from ascii to int
                choice = choice - 48;
            }
        }

    }
    else if (turn == ai_item) 
    {
        get_ai_choice(gameDifficulty);
    }
}

bool gameover() {
    //checking the win for Simple Rows and Simple Column
    for (int i = 0; i < 3; i++)
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2] || board[0][i] == board[1][i] && board[0][i] == board[2][i])
            return false;

    //checking the win for both diagonal

    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] || board[0][2] == board[1][1] && board[0][2] == board[2][0])
        return false;

    //Checking the game is in continue mode or not
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return true;

    //Checking the if game already draw
    draw = true;
    return false;
}

void display_victory_message()
{
    if (draw == false && turn != player_item) {
        cout << "\n\nCongratulations!You've won\n\n";
    }
    else if (draw == false && turn == player_item) {
        cout << "\n\nOh No! You've lost\n\n";
    }
    else
        cout << "\n\nGAME DRAW!!!\n\n";
    cout << "Press Enter to play again. Press ESC to return to menu.";
}

int main()
{
    optionFile.open("option.txt", ios::in);

    if (optionFile.is_open() && optionFile.peek() != fstream::traits_type::eof())
    {
        //reading options from file(if it exists)
        optionFile >> gameDifficulty >> textColor >> XColor >> OColor;
    }
    else
    {
        gameDifficulty = 1;
        textColor = 1;
        XColor = 4;
        OColor = 7;
    }
    optionFile.close();
    optionFile.open("option.txt", ios::out | ios::trunc);
    

    while (!exitGame)
    {
        if(!startGame)
        {
            //Main Menu
            display_menu();
            menu_navigation();
        }

        if (startGame && !pauseGame && gameover())
        {
            //Main Game
            system("cls");
            display_ingame_UI();
            display_board();
            game_turn();
            
        }
        if (startGame && !pauseGame && !gameover())
        {
            //Victory screen
            system("cls");
            display_ingame_UI();
            display_board();
            display_victory_message();

            navigation = _getch();
            if (navigation == ENTER)
            {
                reset_board();
            }
            else if (navigation == ESCAPE)
            {
                startGame = false;
                reset_board();
            }

        }

        if (pauseGame)
        {
            //Pause Menu
            display_pause_menu();
            pause_menu_navigation();
        }

    }

    //making settings persistent
    optionFile << gameDifficulty << "\n" << textColor << "\n" << XColor << "\n" << OColor << "\n";
    optionFile.close();

    return 0;
    
}