#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <mutex>

#include "tetromino.hpp"
#include "tetromino_controller.hpp"
#include "game_constants.hpp"
#include "utility_tetris.hpp"
#include "tetris_exception.hpp"

using namespace std;

char gameBoard[game_constants::board_width][game_constants::board_height];

static mutex inputMutex;
static char input = ' ';

static mutex stopMutex;
static bool stop;

//Sort Of Beautified Version of the Output
void print_board(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //clear terminal
    cout << "\033[2J\033[1;1H";
    cout << "\t\t\t  +";
    for(int i = 0; i < game_constants::board_width; i++) cout << "=";
    cout << "+" << endl;
    for(int y = 0; y < game_constants::board_height; y++) {
        cout << "\t\t\t = ";
        for(int x = 0; x < game_constants::board_width; x++) {
            cout << board[x][y];
        }
        cout << " = " << endl;
    }
    cout << "\t\t\t  +";
    for(int i = 0; i < game_constants::board_width; i++) cout << "=";
    cout << "+" << endl;
}

//Barebone print of the GameBoard
void print_board_2(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //clear terminal
    cout << "\033[2J\033[1;1H";
    for(int y = 0; y < game_constants::board_height; y++) {
        for(int x = 0; x < game_constants::board_width; x++) {
            cout << board[x][y];
        }
        cout << endl;
    }
}

//For Solution with thread -> needs while Loop 
void getCharWithoutEnterVoid() {
    while(!stop) {
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
        inputMutex.lock();
        input = buffer;
        inputMutex.unlock();
    }
}

void waitThreadCallback(const std::chrono::milliseconds &waitTime) {
    this_thread::sleep_for(waitTime);
}

int main() {
    initialize_board(gameBoard);

    unique_ptr<tetromino_controller> controller(new tetromino_controller(gameBoard));
    
    //controller->generateNewTetromino(1, pair<int, int>(3, 2), 0, 1);
    controller->generateNewRandomTetromino();
    controller->getCurrentTetromino().drawTetromino(gameBoard);
    print_board(gameBoard);

    //starting thread for Inputs;
    thread inputThread(getCharWithoutEnterVoid);

    int dropdownCounter = 0;

    while(!stop) {
        thread waitThread(waitThreadCallback, game_constants::wait_time);

        //Ensuring Thread/Variable Integrety through Mutex -> new Variable required
        inputMutex.lock();
        char inputDummy = input;
        inputMutex.unlock();

        switch(inputDummy) {
            case 'a' :
                controller->getCurrentTetromino().moveLeft(gameBoard);
                controller->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 'd' :
                controller->getCurrentTetromino().moveRight(gameBoard);
                controller->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 's' :
                try {
                    controller->getCurrentTetromino().moveDown(gameBoard);
                    controller->getCurrentTetromino().drawTetromino(gameBoard);
                    print_board(gameBoard);
                    input = ' ';
                    break;
                } catch(const Tetromino_Stuck &tetromino_stuck_exp) {
                    //controller->generateNewTetromino(0, pair<int, int>(0,2), 0, 0);
                    removeCompletedRows(gameBoard);
                    controller->generateNewRandomTetromino();
                    controller->getCurrentTetromino().drawTetromino(gameBoard);
                    print_board(gameBoard);
                    break;
                }
            case 'w' :
                controller->getCurrentTetromino().moveUpDebug(gameBoard);
                controller->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 'r' :
                try {
                    controller->getCurrentTetromino().rotateChecked(gameBoard);
                    controller->getCurrentTetromino().drawTetromino(gameBoard);
                    print_board(gameBoard);
                    input = ' ';
                    break;
                } catch(Tetris_Bounds &rotation_exp) {
                    cout << rotation_exp.print_what() << endl;
                    this_thread::sleep_for(5s);
                }
                break;
            case 'q' :
                print_board(gameBoard);
                cout << "Quitting..." << endl;
                stop = 1;
                break;
            //Normal input if nothing pressed
            case ' ' :
                break;
            default :
                cout << "Wrong Input" << endl;
                input = ' ';
                break;
        }
        waitThread.join();
        dropdownCounter++;
        try {
            if(dropdownCounter == game_constants::falltime_factor) {
                dropdownCounter = 0;
                controller->getCurrentTetromino().moveDown(gameBoard);
                controller->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
            }
        } catch(const Tetromino_Stuck &tetromino_stuck_exp) {
            //controller->generateNewTetromino(0, pair<int, int>(0,2), 0, 0);
            //ADD TRY FOR GAME OVER TODO
            removeCompletedRows(gameBoard);
            controller->generateNewRandomTetromino();
            controller->getCurrentTetromino().drawTetromino(gameBoard);
            print_board(gameBoard);
            //cout << tetromino_stuck_exp.print_what();
            //this_thread::sleep_for(2s);
        }
    }

    inputThread.join();

    return 0;
}