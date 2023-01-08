#include "tetromino_factory.hpp"

tetromino & tetromino_factory::getCurrentTetromino() {
    return *(this->currentTetromino);
}

void tetromino_factory::generateNewTetromino(const int block_symbol_number, const std::pair<int, int> start_point, const int start_rotation, int shape_id) {
    if(currentTetromino != nullptr) delete currentTetromino;
    this->currentTetromino = new tetromino(game_constants::tetromino_blocks[block_symbol_number], start_point, start_rotation, shape_id);
}

void tetromino_factory::generateNewRandomTetromino() {
    if(currentTetromino != nullptr) delete currentTetromino;
    int block_symbol_number = getRandNumber(4);
    int start_rotation = getRandNumber(3);
    int shape_id = getRandNumber(4);

    this->currentTetromino = new tetromino(game_constants::tetromino_blocks[block_symbol_number], std::pair<int, int>(game_constants::board_width / 2, 0), start_rotation, shape_id);
}

tetromino_factory::tetromino_factory(char (&factoryBoard)[game_constants::board_width][game_constants::board_height]) : factoryBoard(factoryBoard) {

}

tetromino_factory::~tetromino_factory() {
    if(currentTetromino != nullptr) delete currentTetromino;
}

void tetromino_factory::draw() {
    this->getCurrentTetromino().drawTetromino(this->factoryBoard);
}