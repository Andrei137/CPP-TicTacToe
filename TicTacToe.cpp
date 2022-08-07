#include <iostream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <conio.h>
#include <windows.h>

#define MAX 100
#define DELAY 100
#define elif else if
#define CTRL(c) ((c) & 037)

struct TicTacToe
{
    char value, freePosition;
    bool occupied;
} square[9];

int playerStart, nrX, nrO, nrDraws, firstCorner, secondCorner, edge;
char player[MAX], playerX[MAX], playerO[MAX];
bool playerFirstTurn;

void resetValues()
{
    for (int i = 0; i < 9; ++i)
    {
        square[i].freePosition = (char)(i + 49);
        square[i].value = ' ';
        square[i].occupied = false;
    }
}

void readDecision(char &decision)
{
    if (decision == '-')
    {
        decision = getch();
        Sleep(DELAY);
    }
}

void loadingEffect(int delay)
{
    for (int i = 0; i < 3; ++i)
    {
        Sleep(delay);
        std::cout << '.';
        Sleep(4 * delay);
    }
}

void displayMainScreen()
{
    std::cout << "< Tic Tac Toe >\n\n";
    std::cout << "1. Player vs Computer\n";
    std::cout << "2. Player vs Player\n\n";
    std::cout << "-> Choose your game (1 / 2) : ";
}

void displayDifficulty()
{
    std::cout << "1. Normal difficulty\n";
    std::cout << "2. Impossible difficulty\n\n";
    std::cout << "-> Difficulty (1 / 2) : ";
}

void waitingMessage()
{
    std::cout << "\n\n-> Please wait";
    loadingEffect(DELAY);
    Sleep(DELAY);
}

void preparingTheBoard(bool endl)
{
    std::cout << "-> Preparing the board";
    loadingEffect(DELAY);
}

void chooseTurnMessage()
{
    std::cout << "-> Choosing your turn";
    loadingEffect(DELAY);
    Sleep(DELAY);
    std::cout << '\n';
    preparingTheBoard(0);
}

void displayBoard(char winner)
{
    if (winner == '-')
    {
        std::cout << "(X) " << playerX << " : " << nrX << " - " << "(O) " << playerO << " : " << nrO << " [Draws : " << nrDraws << "]\n\n";
        std::cout << "     |     |     ";
        std::cout << "          |     |     ";
        std::cout << "\n  " << square[0].freePosition << "  |  " << square[1].freePosition << "  |  " << square[2].freePosition;
        std::cout << "         " << square[0].value << "  |  " << square[1].value << "  |  " << square[2].value;
        std::cout << "\n_____|_____|_____";
        std::cout << "     _____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "          |     |     ";
        std::cout << "\n  " << square[3].freePosition << "  |  " << square[4].freePosition << "  |  " << square[5].freePosition;
        std::cout << "         " << square[3].value << "  |  " << square[4].value << "  |  " << square[5].value;
        std::cout << "\n_____|_____|_____";
        std::cout << "     _____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "          |     |     ";
        std::cout << "\n  " << square[6].freePosition << "  |  " << square[7].freePosition << "  |  " << square[8].freePosition;
        std::cout << "         " << square[6].value << "  |  " << square[7].value << "  |  " << square[8].value;
        std::cout << "\n     |     |     ";
        std::cout << "          |     |     \n\n";
    }
    else
    {
        std::cout << "(X) " << playerX << " : " << nrX << " - " << "(O) " << playerO << " : " << nrO << " [Draws : " << nrDraws << "]\n\n"; 
        std::cout << "     |     |     ";
        std::cout << "\n  " << square[0].value << "  |  " << square[1].value << "  |  " << square[2].value;
        std::cout << "\n_____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "\n  " << square[3].value << "  |  " << square[4].value << "  |  " << square[5].value;
        std::cout << "\n_____|_____|_____";
        std::cout << "\n     |     |     ";
        std::cout << "\n  " << square[6].value << "  |  " << square[7].value << "  |  " << square[8].value;
        std::cout << "\n     |     |     \n\n";
    }
}

void displayWinner(int turn, char winner, bool increase)
{
    Sleep(DELAY);
    if (turn == 10 && winner == '-')
    {
        displayBoard(' ');
        if (increase) 
            ++nrDraws;
        std::cout << "-> Draw";
    }
    else
    {
        displayBoard(winner);
        std::cout << "-> The winner is ";
        if (winner == 'X')
        {
            if (increase)
                ++nrX;
            std::cout << "(X) " << playerX;
        }
        else
        {
            if (increase)
                ++nrO;
            std::cout << "(O) " << playerO;
        }
    }
}

bool checkBoard(char &c)
{
    if 
    (
        square[0].value != ' ' &&
        (
            (square[0].value == square[1].value && square[0].value == square[2].value) || 
            (square[0].value == square[3].value && square[0].value == square[6].value) || 
            (square[0].value == square[4].value && square[0].value == square[8].value)
        )
    )
    {
        c = square[0].value;
        return true;
    }
    if 
    (
        square[4].value != ' ' &&
        (
            (square[4].value == square[3].value && square[4].value == square[5].value) || 
            (square[4].value == square[1].value && square[4].value == square[7].value) || 
            (square[4].value == square[2].value && square[4].value == square[6].value)
        )
    )
    {
        c = square[4].value;
        return true;
    }
    if 
    (
        square[8].value != ' ' &&
        (
            (square[8].value == square[6].value && square[8].value == square[7].value) || 
            (square[8].value == square[2].value && square[8].value == square[5].value)
        )
    )
    {
        c = square[8].value;
        return true;
    }
    return false;
}

bool closeToWin(int &squareToFill, char chComputer)
{
    squareToFill = 9;
    if (!square[0].occupied)
    {
        if 
        (
            (square[1].value != ' ' && square[1].value == square[2].value && (squareToFill == 9 || square[1].value == chComputer)) || 
            (square[3].value != ' ' && square[3].value == square[6].value && (squareToFill == 9 || square[3].value == chComputer)) ||
            (square[4].value != ' ' && square[4].value == square[8].value && (squareToFill == 9 || square[4].value == chComputer))
        )
            squareToFill = 0;
    }
    if (!square[1].occupied)
    {
        if 
        (
            (square[0].value != ' ' && square[0].value == square[2].value && (squareToFill == 9 || square[0].value == chComputer)) || 
            (square[4].value != ' ' && square[4].value == square[7].value && (squareToFill == 9 || square[4].value == chComputer))
        )
            squareToFill = 1;
    }
    if (!square[2].occupied)
    {
        if 
        (
            (square[0].value != ' ' && square[0].value == square[1].value && (squareToFill == 9 || square[0].value == chComputer)) || 
            (square[5].value != ' ' && square[5].value == square[8].value && (squareToFill == 9 || square[5].value == chComputer)) ||
            (square[4].value == square[6].value && (squareToFill == 9 || square[4].value == chComputer))
        )
            squareToFill = 2;
    }
    if (!square[3].occupied)
    {
        if 
        (
            (square[4].value != ' ' && square[4].value == square[5].value && (squareToFill == 9 || square[4].value == chComputer)) || 
            (square[0].value != ' ' && square[0].value == square[6].value && (squareToFill == 9 || square[0].value == chComputer))
        )
            squareToFill = 3;
    }
    if (!square[4].occupied)
    {
        if 
        (
            (square[3].value != ' ' && square[3].value == square[5].value && (squareToFill == 9 || square[3].value == chComputer)) || 
            (square[1].value != ' ' && square[1].value == square[7].value && (squareToFill == 9 || square[1].value == chComputer)) ||
            (square[0].value != ' ' && square[0].value == square[8].value && (squareToFill == 9 || square[0].value == chComputer)) ||
            (square[2].value != ' ' && square[2].value == square[6].value && (squareToFill == 9 || square[2].value == chComputer))
        )
            squareToFill = 4;
    }
    if (!square[5].occupied)
    {
        if 
        (
            (square[3].value != ' ' && square[3].value == square[4].value && (squareToFill == 9 || square[3].value == chComputer)) || 
            (square[2].value != ' ' && square[2].value == square[8].value && (squareToFill == 9 || square[2].value == chComputer))
        )
            squareToFill = 5;
    }
    if (!square[6].occupied)
    {
        if 
        (
            (square[7].value != ' ' && square[7].value == square[8].value && (squareToFill == 9 || square[7].value == chComputer)) || 
            (square[0].value != ' ' && square[0].value == square[3].value && (squareToFill == 9 || square[0].value == chComputer)) ||
            (square[2].value != ' ' && square[2].value == square[4].value && (squareToFill == 9 || square[2].value == chComputer))
        )
            squareToFill = 6;
    }
    if (!square[7].occupied)
    {
        if 
        (
            (square[6].value != ' ' && square[6].value == square[8].value && (squareToFill == 9 || square[6].value == chComputer)) || 
            (square[1].value != ' ' && square[1].value == square[4].value && (squareToFill == 9 || square[1].value == chComputer))
        )
            squareToFill = 7;
    }
    if (!square[8].occupied)
    {
        if 
        (
            (square[6].value != ' ' && square[6].value == square[7].value && (squareToFill == 9 || square[6].value == chComputer)) || 
            (square[2].value != ' ' && square[2].value == square[5].value && (squareToFill == 9 || square[2].value == chComputer)) ||
            (square[0].value != ' ' && square[0].value == square[4].value && (squareToFill == 9 || square[0].value == chComputer))
        )
            squareToFill = 8;
    }
    return squareToFill != 9;
}

void insertPlayerPvE()
{
    bool noName1 = true;
    while (noName1)
    {
        system("cls");
        std::cout << "-> Insert your name : ";
        std::cin.getline(player, MAX);
        if (!(int)player[0])
            system("cls");
        else
        {
            system("cls");
            noName1 = false;
            srand(time(NULL));
            int playerTurn = 1 + rand() % 2;
            playerFirstTurn = (playerTurn == 1) ? true : false;
            chooseTurnMessage();
        }
    }
}

void playerTurnPvE(char &chPlayer, int turn)
{
    if ((playerFirstTurn && turn % 2) || (!playerFirstTurn && turn % 2 == 0))
    {
        char number;
        if (playerFirstTurn)
        {
            bool noX = true;
            while (noX)
            {
                displayBoard('-');
                std::cout << '(' << chPlayer << ") " << player << " : ";
                number = getch();
                if (number == CTRL('C'))
                {
                    std::cout << "^C";
                    chPlayer = '-';
                    return;
                }
                elif (square[(number - '0') - 1].occupied || number > '9' || number < '1')
                    system("cls");
                else
                {
                    std::cout << number;
                    Sleep(DELAY);
                    noX = false;
                    square[(number - '0') - 1].freePosition = '-';
                    square[(number - '0') - 1].value = chPlayer;
                    square[(number - '0') - 1].occupied = true;
                }
            }
        }
        else
        {
            bool noO = true;
            while (noO)
            {
                displayBoard('-');
                std::cout << '(' << chPlayer << ") " << player << " : ";
                number = getch();
                if (number == CTRL('C'))
                {
                    std::cout << "^C";
                    chPlayer = '-';
                    return;
                }
                elif (square[(number - '0') - 1].occupied || number > '9' || number < '1')
                    system("cls");
                else
                {
                    std::cout << number;
                    Sleep(DELAY);
                    noO = false;
                    square[(number - '0') - 1].freePosition = '-';
                    square[(number - '0') - 1].value = chPlayer;
                    square[(number - '0') - 1].occupied = true;
                }
            }
        }
    }
}

void placedByComputer(int squareToFill, char chComputer)
{
    square[squareToFill].freePosition = '-';
    square[squareToFill].value = chComputer;
    square[squareToFill].occupied = true;
}

void computerTurnNormalPvE(char chComputer, int turn)
{
    if ((playerFirstTurn && turn % 2 == 0) || (!playerFirstTurn && turn % 2))
    {
        system("cls");
        displayBoard('-');
        std::cout << "(" << chComputer << ") Computer is thinking";
        srand(time(NULL));
        int squareToFill;
        loadingEffect(DELAY);
        Sleep(DELAY);
        if (closeToWin(squareToFill, chComputer))
            placedByComputer(squareToFill, chComputer);
        else
        {
            srand(time(NULL));
            int random = rand() % 9;
            while (square[random].occupied)
                random = rand() % 9;
            placedByComputer(random, chComputer);
        }
    }
}

void computerTurnImpossiblePvE(char chComputer, int turn)
{
    if ((playerFirstTurn && turn % 2 == 0) || (!playerFirstTurn && turn % 2))
    {
        system("cls");
        displayBoard('-');
        std::cout << "(" << chComputer << ") Computer is thinking";
        srand(time(NULL));
        int squareToFill, random;
        loadingEffect(DELAY);
        Sleep(DELAY);
        if (playerFirstTurn)
        {
            switch (turn)
            {
                case 2 :
                    if (playerStart == 1)
                    {
                        srand(time(NULL));
                        random = 1 + rand() % 4;
                        switch (random)
                        {
                            case 1 :
                                placedByComputer(firstCorner = 0, chComputer);
                                break;
                            case 2 :
                                placedByComputer(firstCorner = 2, chComputer);
                                break;
                            case 3 :
                                placedByComputer(firstCorner = 6, chComputer);
                                break;
                            default :
                                placedByComputer(firstCorner = 8, chComputer);
                        }
                    }
                    else
                        placedByComputer(4, chComputer);
                    break;
                case 4 :
                    if (closeToWin(squareToFill, chComputer))
                        placedByComputer(squareToFill, chComputer);
                    else
                    {
                        if (playerStart == 1)
                        {
                            switch (firstCorner)
                            {
                                case 0 :
                                    placedByComputer(2, chComputer);
                                    break;
                                case 2 :
                                    placedByComputer(8, chComputer);
                                    break;
                                case 6 :
                                    placedByComputer(0, chComputer);
                                    break;
                                default :
                                    placedByComputer(6, chComputer);
                            }
                        }
                        elif (playerStart == 2)
                        {
                            if (square[0].occupied)
                            {
                                if (!square[7].occupied)
                                    placedByComputer(7, chComputer);
                                else
                                    placedByComputer(5, chComputer);
                            }
                            elif (square[2].occupied)
                            {
                                if (!square[7].occupied)
                                    placedByComputer(7, chComputer);
                                else
                                    placedByComputer(3, chComputer);
                            }
                            elif (square[6].occupied)
                            {
                                if (!square[1].occupied)
                                    placedByComputer(1, chComputer);
                                else
                                    placedByComputer(5, chComputer);
                            }
                            elif (square[8].occupied)
                            {
                                if (!square[1].occupied)
                                    placedByComputer(1, chComputer);
                                else
                                    placedByComputer(3, chComputer);
                            }
                        }
                        else
                        {
                            if ((square[1].occupied && square[7].occupied) || (square[3].occupied && square[5].occupied))
                                placedByComputer(0, chComputer);
                            elif (square[1].occupied && square[3].occupied)
                                placedByComputer(2, chComputer);
                            elif (square[1].occupied && square[5].occupied)
                                placedByComputer(0, chComputer);
                            elif (square[7].occupied && square[3].occupied)
                                placedByComputer(8, chComputer);
                            elif (square[7].occupied && square[5].occupied)
                                placedByComputer(6, chComputer);
                            elif ((square[1].occupied && square[6].occupied) || (square[0].occupied && square[7].occupied))
                                placedByComputer(5, chComputer);
                            elif ((square[1].occupied && square[8].occupied) || (square[2].occupied && square[7].occupied))
                                placedByComputer(3, chComputer);
                            elif ((square[0].occupied && square[5].occupied) || (square[2].occupied && square[3].occupied))
                                placedByComputer(7, chComputer);
                            elif ((square[3].occupied && square[8].occupied) || (square[5].occupied && square[6].occupied))
                                placedByComputer(1, chComputer);
                        }
                    }
                    break;  
                case 6 :
                    if (closeToWin(squareToFill, chComputer))
                        placedByComputer(squareToFill, chComputer);
                    else
                    {
                        if (playerStart == 1)
                        {
                            switch (firstCorner)
                            {
                                case 0 :
                                    if (square[1].occupied)
                                        placedByComputer(6, chComputer);
                                    else
                                        placedByComputer(2, chComputer);
                                    break;
                                case 2 :
                                    if (square[1].occupied)
                                        placedByComputer(8, chComputer);
                                    else
                                        placedByComputer(0, chComputer);
                                    break;
                                case 6 :
                                    if (square[3].occupied)
                                        placedByComputer(8, chComputer);
                                    else
                                        placedByComputer(0, chComputer);
                                    break;
                                default :
                                    if (square[5].occupied)
                                        placedByComputer(6, chComputer);
                                    else
                                        placedByComputer(2, chComputer);
                            }
                        }
                        elif (playerStart == 2)
                        {
                            {
                                if (square[1].occupied)
                                    placedByComputer(3, chComputer);
                                else
                                    placedByComputer(1, chComputer);
                            }
                        }
                    }
                    break;
                default :
                    if (closeToWin(squareToFill, chComputer))
                        placedByComputer(squareToFill, chComputer);
                    else
                    {
                        srand(time(NULL));
                        random = rand() % 9;
                        while (square[random].occupied)
                            random = rand() % 9;
                        placedByComputer(random, chComputer);
                    }
            }
        }
        else
        {
            switch (turn)
            {
                case 1 :
                    srand(time(NULL));
                    random = 1 + rand() % 4;
                    switch (random)
                    {
                        case 1 :
                            placedByComputer(firstCorner = 0, chComputer);
                            break;
                        case 2 :
                            placedByComputer(firstCorner = 2, chComputer);
                            break;
                        case 3 :
                            placedByComputer(firstCorner = 6, chComputer);
                            break;
                        default :
                            placedByComputer(firstCorner = 8, chComputer);
                    }
                    break;
                case 3 :
                    if (square[4].occupied)
                    {
                        srand(time(NULL));
                        int randomDecision1, randomDecision2;
                        randomDecision1 = randomDecision2 = 1 + rand() % 2;
                        switch (firstCorner)
                        {
                            case 0 :
                                if (randomDecision1 == 1)
                                    placedByComputer(8, chComputer);
                                else
                                {
                                    if (randomDecision2 == 1)
                                        placedByComputer(edge = 5, chComputer);
                                    else
                                        placedByComputer(edge = 7, chComputer);
                                }
                                break;
                            case 2 :
                                if (randomDecision1 == 1)
                                    placedByComputer(6, chComputer);
                                else
                                {
                                    if (randomDecision2 == 1)
                                        placedByComputer(edge = 3, chComputer);
                                    else
                                        placedByComputer(edge = 7, chComputer);
                                }
                                break;
                            case 6 :
                                if (randomDecision1 == 1)
                                    placedByComputer(2, chComputer);
                                else
                                {
                                    if (randomDecision2 == 1)
                                        placedByComputer(edge = 1, chComputer);
                                    else
                                        placedByComputer(edge = 5, chComputer);
                                }
                                break;
                            default :
                                if (randomDecision1 == 1)
                                    placedByComputer(0, chComputer);
                                else
                                {
                                    if (randomDecision2 == 1)
                                        placedByComputer(edge = 1, chComputer);
                                    else
                                        placedByComputer(edge = 3, chComputer);
                                }
                        }
                    }
                    else
                    {
                        switch (firstCorner)
                        {
                            case 0 :
                                if (square[1].occupied || square[2].occupied)
                                    placedByComputer(secondCorner = 6, chComputer);
                                else
                                    placedByComputer(secondCorner = 2, chComputer);
                                break;
                            case 2 :
                                if (square[0].occupied || square[1].occupied)
                                    placedByComputer(secondCorner = 8, chComputer);
                                else
                                    placedByComputer(secondCorner = 0, chComputer);
                                break;
                            case 6 :
                                if (square[0].occupied || square[3].occupied)
                                    placedByComputer(secondCorner = 8, chComputer);
                                else 
                                    placedByComputer(secondCorner = 0, chComputer);
                                break;
                            default :
                                if (square[2].occupied || square[5].occupied)
                                    placedByComputer(secondCorner = 6, chComputer);
                                else
                                    placedByComputer(secondCorner = 2, chComputer);
                        }
                    }
                    break;
                case 5 :
                    if (closeToWin(squareToFill, chComputer))
                        placedByComputer(squareToFill, chComputer);
                    elif (square[4].occupied)
                    {
                        if ((firstCorner == 0 && edge == -1) || (firstCorner == 8 && edge == -1))
                        {
                            if (square[2].occupied)
                                placedByComputer(6, chComputer);
                            else
                                placedByComputer(2, chComputer);
                        }
                        elif ((firstCorner == 2 && edge == -1) ||  (firstCorner == 6 && edge == -1))
                        {
                            if (square[0].occupied)
                                placedByComputer(8, chComputer);
                            else
                                placedByComputer(0, chComputer);
                        }
                        else
                        {
                            switch (edge)
                            {
                                case 1 :
                                    if (firstCorner == 6)
                                        placedByComputer(0, chComputer);
                                    else
                                        placedByComputer(2, chComputer);
                                    break;
                                case 3 :
                                    if (firstCorner == 2)
                                        placedByComputer(0, chComputer);
                                    else
                                        placedByComputer(6, chComputer);
                                    break;
                                case 5 :
                                    if (firstCorner == 0)
                                        placedByComputer(2, chComputer);
                                    else
                                        placedByComputer(8, chComputer);
                                    break;
                                default :
                                    if (firstCorner == 0)
                                        placedByComputer(6, chComputer);
                                    else
                                        placedByComputer(8, chComputer);

                            }
                        }
                    }
                    else
                    {
                        if ((firstCorner == 0 && secondCorner == 2) || (firstCorner == 2 && secondCorner == 0))
                        {
                            if (square[3].occupied || square[6].occupied)
                                placedByComputer(8, chComputer);
                            else
                                placedByComputer(6, chComputer);
                        }
                        elif ((firstCorner == 0 && secondCorner == 6) || (firstCorner == 6 && secondCorner == 0))
                        {
                            if (square[1].occupied || square[2].occupied)
                                placedByComputer(8, chComputer);
                            else
                                placedByComputer(2, chComputer);
                        }
                        elif ((firstCorner == 2 && secondCorner == 8) || (firstCorner == 8 && secondCorner == 2))
                        {
                            if (square[0].occupied || square[1].occupied)
                                placedByComputer(6, chComputer);
                            else
                                placedByComputer(0, chComputer);
                        }
                        else
                        {
                            if (square[0].occupied || square[3].occupied)
                                placedByComputer(2, chComputer);
                            else
                                placedByComputer(0, chComputer);
                        }
                     }
                    break;
                default :
                    if (closeToWin(squareToFill, chComputer))
                        placedByComputer(squareToFill, chComputer);
                    else
                    {
                        srand(time(NULL));
                        random = rand() % 9;
                        while (square[random].occupied)
                            random = rand() % 9;
                        placedByComputer(random, chComputer);
                    }
            }
        }
    }
}

void insertPlayerPvP(char c)
{
    system("cls");
    bool noName2 = true;
    while (noName2)
    {
        if (c == 'X')
        {
            std::cout << "-> (X) Player one : ";
            std::cin.getline(playerX, MAX);
            if (!(int)playerX[0])
                system("cls");
            else
                noName2 = false;
        }
        else
        {
            std::cout << "-> (X) Player one : " << playerX << '\n';
            std::cout << "-> (O) Player two : ";
            std::cin.getline(playerO, MAX);
            if (!(int)playerO[0])
                system("cls");
            else
                noName2 = false;
        }
    }
}

void playerTurnPvP(int &turn)
{
    char number;
    if (turn % 2)
    {
        bool noX = true;
        while (noX)
        {
            displayBoard('-');
            std::cout << "(X) " << playerX << " : ";
            number = getch();
            if (number == CTRL('C'))
            {
                turn = -1;
                return;
            }
            elif (square[(number - '0') - 1].occupied || number > '9' || number < '1')
                system("cls");
            else
            {
                std::cout << number;
                Sleep(DELAY);
                noX = false;
                square[(number - '0') - 1].freePosition = '-';
                square[(number - '0') - 1].value = 'X';
                square[(number - '0') - 1].occupied = true;
            }
        }
    }
    else
    {
        bool noO = true;
        while (noO)
        {
            displayBoard('-');
            std::cout << "(O) " << playerO << " : ";
            number = getch();
            if (number == CTRL('C'))
            {
                turn = -1;
                return;
            }
            elif (square[(number - '0') - 1].occupied || number > '9' || number < '1')
                system("cls");
            else
            {
                std::cout << number;
                Sleep(DELAY);
                noO = false;
                square[(number - '0') - 1].freePosition = '-';
                square[(number - '0') - 1].value = 'O';
                square[(number - '0') - 1].occupied = true;
            }
        }
    }
}

int main()
{
    resetValues();
    system("cls");
    char gamemode;
    bool noGameplay = true;
    while (noGameplay)
    {
        resetValues();
        displayMainScreen();
        gamemode = getch();
        if (gamemode == '1')
        {
            std::cout << gamemode;
            Sleep(DELAY);
            noGameplay = false;
            bool retryPvE = true;
            while (retryPvE)
            {
                system("cls");
                char difficulty;
                bool noDifficulty = true;
                while (noDifficulty)
                {
                    displayDifficulty();
                    difficulty = getch();
                    if (difficulty == '1' || difficulty == '2')
                    {
                        std::cout << difficulty;
                        Sleep(DELAY);
                        bool retryDifficulty = true;
                        while (retryDifficulty)
                        {
                            system("cls");
                            noDifficulty = false;
                            insertPlayerPvE();
                            Sleep(DELAY);
                            system("cls");
                            if (playerFirstTurn)
                            {
                                strcpy(playerX, player);
                                strcpy(playerO, "Computer");
                            }
                            else
                            {
                                strcpy(playerX, "Computer");
                                strcpy(playerO, player);
                            }
                            nrX = nrO = nrDraws = 0;
                            char chPlayer = playerFirstTurn ? 'X' : 'O', chComputer = playerFirstTurn ? 'O' : 'X';
                            bool retryMatchPvE = true;
                            while (retryMatchPvE)
                            {
                                playerStart = 0;
                                int turn = 1;
                                char winner = '-';
                                while (winner == '-' && turn <= 9)
                                {
                                    playerTurnPvE(chPlayer, turn);
                                    if (chPlayer == '-')
                                        return 0;
                                    elif (turn == 1 && playerFirstTurn)
                                    {
                                        if (square[4].occupied)
                                            playerStart = 1;
                                        elif (square[0].occupied || square[2].occupied || square[6].occupied || square[8].occupied)
                                            playerStart = 2;
                                    }
                                    if (difficulty == '1')
                                        computerTurnNormalPvE(chComputer, turn);
                                    else
                                        computerTurnImpossiblePvE(chComputer, turn);
                                    if (checkBoard(winner));
                                    ++turn;
                                    system("cls");
                                }
                                char decisionPvE = '-', decisionRematch = '-', decisionDifficulty = '-', decisionGameplay = '-';
                                bool validPvE = false, validRematch = false, validDifficulty = false, validGameplay = false, loaded = false, increase = true;
                                while (!validPvE || !validRematch || !validDifficulty || !validGameplay)
                                {
                                    displayWinner(turn, winner, increase);
                                    increase = false;
                                    if (!loaded)
                                    {
                                        loaded = true;
                                        waitingMessage();
                                        system("cls");
                                        displayWinner(turn, winner, increase);
                                    }
                                    std::cout << "\n\n-> Rematch? (y / n) : ";
                                    readDecision(decisionRematch);
                                    if (decisionRematch == 'y')
                                    {
                                        validRematch = validPvE =  validDifficulty = validGameplay = true;
                                        bool auxPlayerTurn = playerFirstTurn;
                                        srand(time(NULL));
                                        int playerTurn = 1 + rand() % 2;
                                        playerFirstTurn = (playerTurn == 1) ? true : false;
                                        resetValues();
                                        if (auxPlayerTurn != playerFirstTurn)
                                        {
                                            int nrAux = nrX;
                                            nrX = nrO;
                                            nrO = nrAux;
                                            char playerAux[MAX], chAux = chPlayer;
                                            chPlayer = chComputer;
                                            chComputer = chAux;
                                            strcpy(playerAux, playerX);
                                            strcpy(playerX, playerO);
                                            strcpy(playerO, playerAux);
                                        }
                                        Sleep(DELAY);
                                        system("cls");
                                        chooseTurnMessage();
                                        system("cls");
                                        Sleep(DELAY);
                                    }
                                    elif (decisionRematch == 'n')
                                    {
                                        validRematch = true;
                                        retryMatchPvE = false;
                                        std::cout << "n\n\n-> Change the player? (y / n) : ";
                                        readDecision(decisionPvE);
                                        if (decisionPvE == 'y')
                                        {
                                            validPvE = validDifficulty = validGameplay = true;
                                            system("cls");
                                            resetValues();
                                        }
                                        elif (decisionPvE == 'n')
                                        {
                                            validPvE = true;
                                            retryDifficulty = false;
                                            std::cout << "n\n\n-> Change the difficulty? (y / n) : ";
                                            readDecision(decisionDifficulty);
                                            if (decisionDifficulty == 'y')
                                            {
                                                validDifficulty = validGameplay = true;
                                                system("cls");
                                                resetValues();
                                            }
                                            elif (decisionDifficulty == 'n')
                                            {
                                                validDifficulty = true;
                                                retryPvE = false;
                                                std::cout << "n\n\n-> Change the game mode? (y / n) : ";
                                                readDecision(decisionGameplay);
                                                if (decisionGameplay == 'y')
                                                {
                                                    validGameplay = true;
                                                    system("cls");
                                                    noGameplay = true;
                                                }
                                                elif (decisionGameplay == 'n' || decisionGameplay == CTRL('C'))
                                                {
                                                    std::cout << "^C";
                                                    return 0;
                                                }
                                                else
                                                {
                                                    decisionGameplay = '-';
                                                    system("cls");
                                                }
                                            }
                                            elif (decisionDifficulty == CTRL('C'))
                                            {
                                                std::cout << "^C";
                                                return 0;
                                            }
                                            else
                                            {
                                                decisionDifficulty = '-';
                                                system("cls");
                                            }
                                        }
                                        elif (decisionPvE == CTRL('C'))
                                        {
                                            std::cout << "^C";
                                            return 0;
                                        }
                                        else
                                        {
                                            decisionPvE = '-';
                                            system("cls");
                                        }
                                    }
                                    elif (decisionRematch == CTRL('C'))
                                    {
                                        std::cout << "^C";
                                        return 0;
                                    }
                                    else
                                    {
                                        decisionRematch = '-';
                                        system("cls");
                                    }
                                }
                            }
                        }
                    }
                    elif (difficulty == CTRL('C'))
                    {
                        std::cout << "^C";
                        return 0;
                    }
                    else
                        system("cls");
                }
             }
        }
        elif (gamemode == '2')
        {
            noGameplay = false;
            bool retryPvP = true;
            while (retryPvP)
            {
                Sleep(DELAY);
                insertPlayerPvP('X');
                insertPlayerPvP('O');
                system("cls");
                preparingTheBoard(1);
                system("cls");
                nrX = nrO = nrDraws = 0;
                bool retryMatchPvP = true;
                while (retryMatchPvP)
                {
                    int turn = 1;
                    char winner = '-';
                    while (winner == '-' && turn <= 9)
                    {
                        playerTurnPvP(turn);
                        if (turn == -1)
                        {
                            std::cout << "^C";
                            return 0;
                        }
                        if (checkBoard(winner));
                        ++turn;
                        system("cls");
                    }
                    char decisionPvP = '-', decisionRematch = '-', decisionSides = '-', decisionGameplay = '-';
                    bool validPvP = false, validRematch = false, validSides = false, validGameplay = false, loaded = false, increase = true;
                    while (!validPvP || !validRematch || !validSides || !validGameplay)
                    {
                        displayWinner(turn, winner, increase);
                        increase = false;
                        if (!loaded)
                        {
                            loaded = true;
                            waitingMessage();
                            system("cls");
                            displayWinner(turn, winner, increase);
                        }
                        std::cout << "\n\n-> Rematch? (y / n) : ";
                        readDecision(decisionRematch);
                        if (decisionRematch == 'y')
                        {
                            validRematch = validPvP = validGameplay = true; 
                            std::cout << "y\n\n-> Switch sides? (y / n) : ";
                            readDecision(decisionSides);
                            if (decisionSides == 'y')
                            {
                                validSides = true;
                                resetValues();
                                int nrAux = nrX;
                                nrX = nrO;
                                nrO = nrAux;
                                char playerAux[MAX];
                                strcpy(playerAux, playerX);
                                strcpy(playerX, playerO);
                                strcpy(playerO, playerAux);
                                Sleep(DELAY);
                                system("cls");
                                preparingTheBoard(1);
                                system("cls");
                            }
                            elif (decisionSides == 'n')
                            {   
                                validSides = true;
                                resetValues();
                                system("cls");
                                preparingTheBoard(1);
                                system("cls");
                            }
                            else
                            {
                                decisionSides = '-';
                                system("cls");
                            }
                        }
                        elif (decisionRematch == 'n')
                        {
                            validRematch = validSides = true;
                            retryMatchPvP = false;
                            std::cout << "n\n\n-> Change the players? (y / n) : ";
                            readDecision(decisionPvP);
                            if (decisionPvP == 'y')
                            {
                                validPvP = validGameplay = true;
                                system("cls");
                                resetValues();
                            }
                            elif (decisionPvP == 'n')
                            {
                                validPvP = true;
                                retryPvP = false;
                                std::cout << "n\n\n-> Change the game mode? (y / n) : ";
                                readDecision(decisionGameplay);
                                if (decisionGameplay == 'y')
                                {
                                    validGameplay = true;
                                    system("cls");
                                    noGameplay = true;
                                }
                                elif (decisionGameplay == 'n')
                                {
                                    system("cls");
                                    return 0;
                                }
                                elif (decisionGameplay == CTRL('C'))
                                {
                                    std::cout << "^C";
                                    return 0;
                                }
                                else
                                {
                                    decisionGameplay = '-';
                                    system("cls");
                                }
                            }
                            else
                            {
                                decisionPvP = '-';
                                system("cls");
                            }
                        }
                        elif (decisionRematch == CTRL('C'))
                        {
                            std::cout << "^C";
                            return 0;
                        }
                        else
                        {
                            decisionRematch = '-';
                            system("cls");
                        }
                    }
                }
            }
        }
        elif (gamemode == CTRL('C'))
        {
            std::cout << "^C";
            return 0;
        }
        else
            system("cls");
    }
}