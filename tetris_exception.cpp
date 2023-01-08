#include "tetris_exception.hpp"

int Tetris_Exception::exceptionID = 0;

Tetris_Exception::Tetris_Exception(std::string msg) : message(msg) {
    Tetris_Exception::exceptionID++;
}

std::string const Tetromino_Stuck::print_what() const {
    std::string msg = message + "   ID: " + std::to_string(Tetris_Exception::exceptionID);
    return msg;
}

Tetromino_Stuck::Tetromino_Stuck() : Tetris_Exception("Tetromino Stuck Exception has been called!") {

}

Tetromino_Stuck::Tetromino_Stuck(std::string msg) : Tetris_Exception(msg) {

}