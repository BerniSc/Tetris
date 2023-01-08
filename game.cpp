#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include <mutex>

#include "tetromino.hpp"
#include "tetromino_factory.hpp"
#include "game_constants.hpp"
#include "utility_tetris.hpp"
#include "tetris_exception.hpp"

using namespace std;

char gameBoard[game_constants::board_width][game_constants::board_height];

static mutex inputMutex;
static char input = ' ';

static mutex stopMutex;
static bool stop;

void print_board(const char (&board)[game_constants::board_width][game_constants::board_height]) {
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

    unique_ptr<tetromino_factory> factory(new tetromino_factory(gameBoard));
    
    factory->generateNewTetromino(1, pair<int, int>(3, 2), 0, 4);
    factory->getCurrentTetromino().drawTetromino(gameBoard);
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
                factory->getCurrentTetromino().moveLeft(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 'd' :
                factory->getCurrentTetromino().moveRight(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 's' :
                try {
                    factory->getCurrentTetromino().moveDown(gameBoard);
                    factory->getCurrentTetromino().drawTetromino(gameBoard);
                    print_board(gameBoard);
                    input = ' ';
                    break;
                } catch(const Tetromino_Stuck &tetromino_stuck_exp) {
                    //factory->generateNewTetromino(0, pair<int, int>(0,2), 0, 0);
                    factory->generateNewRandomTetromino();
                    factory->getCurrentTetromino().drawTetromino(gameBoard);
                    print_board(gameBoard);
                    break;
                }
            case 'w' :
                factory->getCurrentTetromino().moveUpDebug(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 'r' :
                factory->getCurrentTetromino().rotateChecked(gameBoard);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                print_board(gameBoard);
                input = ' ';
                break;
            case 'q' :
                print_board(gameBoard);
                cout << "Quitting..." << endl;
                stop = 1;
                break;
            case 'n' :
                factory->generateNewTetromino(0, pair<int, int>(6,6), 0, 0);
                factory->getCurrentTetromino().drawTetromino(gameBoard);
                break;
            //Normal input if nothing pressed
            case ' ' :
                break;
            default :
                cout << "Wrong Input" << endl;
                break;
        }
        waitThread.join();
        dropdownCounter++;
        try {
            if(dropdownCounter == game_constants::falltime_factor) {
                dropdownCounter = 0;
                factory->getCurrentTetromino().moveDown(gameBoard);
                //factory->getCurrentTetromino().drawTetromino(gameBoard);
                //print_board(gameBoard);
            }
        } catch(const Tetromino_Stuck &tetromino_stuck_exp) {
            //factory->generateNewTetromino(0, pair<int, int>(0,2), 0, 0);
            factory->generateNewRandomTetromino();
            factory->getCurrentTetromino().drawTetromino(gameBoard);
            print_board(gameBoard);
            //cout << tetromino_stuck_exp.print_what();
            //this_thread::sleep_for(2s);
        }
    }

    inputThread.join();

    return 0;
}