#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <mutex>

//For input without enter
#include <unistd.h>
#include <termios.h>

#include "tetromino.hpp"
#include "tetromino_factory.hpp"
#include "game_constants.hpp"

using namespace std;

char gameBoard[game_constants::board_width][game_constants::board_height];

mutex inputMutex;
char input;


void initialize_board(char (&board)[game_constants::board_width][game_constants::board_height]) {
    for(int y = 0; y < game_constants::board_height; y++) {
        for(int x = 0; x < game_constants::board_width; x++) {
            board[x][y] = game_constants::empty_boardblock;
        }
    }
    board[4][1] = 'a';
    board[4][3] = 'a';
}

void print_board(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //clear terminal
    //cout << "\033[2J\033[1;1H";
    for(int y = 0; y < game_constants::board_height; y++) {
        for(int x = 0; x < game_constants::board_width; x++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}

void waitThreadCallback(const std::chrono::milliseconds &waitTime) {
    this_thread::sleep_for(waitTime);
    cout << "ended here" << endl;
}

//Get input without enter
char getCharWithoutEnter() {
    char buffer = 0;
    struct termios old = {0};
    if(tcgetattr(0, &old) < 0) perror("tcsetattr()");
    //Disable canonical Mode
    //Supress Echo
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANONO");
    //Read Char
    if(read(0, &buffer, 1) < 0) perror("read()");
    //Reset Changes
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    //return Char
    return buffer;
}

int main() {
    initialize_board(gameBoard);
    //thread waitThread(waitThreadCallback, 1000ms);
    print_board(gameBoard);
    //waitThread.join();

    unique_ptr<tetromino_factory> factory(new tetromino_factory(gameBoard));
    factory->generateNewTetromino(1, pair<int, int>(3, 2), 0, 4);
    //tetromino t1 = factory->getCurrentTetromino();
    factory->getCurrentTetromino().drawTetromino(gameBoard);

    //tetromino t1(game_constants::tetromino_blocks[1], pair<int, int>(5, 2), 3, 1);
    //t1.drawTetromino(gameBoard);
    print_board(gameBoard);
    
    this_thread::sleep_for(1000ms);

    //Game Loop
    bool quitGame = false;

    while(!quitGame) {
        cout << "HIIII" << endl;
        thread waitThread(waitThreadCallback, 100ms);
        char input = getCharWithoutEnter();
        switch(input) {
            case 'a' :
                factory->getCurrentTetromino().moveLeft(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                break;
            case 'd' :
                factory->getCurrentTetromino().moveRight(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                break;
            case 's' :
                factory->getCurrentTetromino().moveDown(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                break;
            case 'w' :
                factory->getCurrentTetromino().moveUpDebug(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                break;
            case 'r' :
                factory->getCurrentTetromino().rotateChecked(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                break;
            case 'q' :
                print_board(gameBoard);
                cout << "Quitting..." << endl;
                quitGame = 1;
                break;
            case 'n' :
                factory->generateNewTetromino(0, pair<int, int>(6,6), 0, 0);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                break;
            default :
                cout << "Wrong Input" << endl;
                break;
        }
        waitThread.join();
    }

    return 0;
}