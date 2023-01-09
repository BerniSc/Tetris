#include "tetris_exception.hpp"

int Tetris_Exception::exceptionID = 0;
int Tetromino_Stuck::placed_tetrominos = 0;

Tetris_Exception::Tetris_Exception(std::string msg) : message(msg) {
    Tetris_Exception::exceptionID++;
}

std::string const Tetris_Exception::print_what() const {
    std::string msg = message + "   ID: " + std::to_string(Tetris_Exception::exceptionID);
    return msg;
}

Tetromino_Stuck::Tetromino_Stuck() : Tetris_Exception("Tetromino Stuck Exception has been called!") {

}

Tetromino_Stuck::Tetromino_Stuck(std::string msg) : Tetris_Exception(msg) {

}

int const Tetromino_Stuck::getPlacedTetrominos() {
    return Tetromino_Stuck::placed_tetrominos;
}

Game_Over::Game_Over() : Tetris_Exception("Game Over Exception has been called!") {

}

Game_Over::Game_Over(std::string msg) : Tetris_Exception(msg) {
    
}

Tetris_Rotation_Bounds::Tetris_Rotation_Bounds() : Tetris_Exception("A OutOfBounds has been called in the Rotation function!!") {

}

Tetris_Rotation_Bounds::Tetris_Rotation_Bounds(std::string msg) : Tetris_Exception(msg) {
    
}