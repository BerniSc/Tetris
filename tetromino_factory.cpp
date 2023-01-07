#include "tetromino_factory.hpp"

tetromino & tetromino_factory::getCurrentTetromino() {
    return *(this->currentTetromino);
}

void tetromino_factory::generateNewTetromino(const int block_symbol_number, const std::pair<int, int> start_point, const int start_rotation, int shape_id) {
    if(currentTetromino != nullptr) delete currentTetromino;
    this->currentTetromino = new tetromino(game_constants::tetromino_blocks[block_symbol_number], start_point, start_rotation, shape_id);
}

tetromino_factory::tetromino_factory(char (&factoryBoard)[game_constants::board_width][game_constants::board_height]) : factoryBoard(factoryBoard) {

}

tetromino_factory::~tetromino_factory() {
    if(currentTetromino != nullptr) delete currentTetromino;
}