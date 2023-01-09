#include "tetromino_controller.hpp"

tetromino & tetromino_controller::getCurrentTetromino() {
    return *(this->currentTetromino);
}

void tetromino_controller::generateNewTetromino(const int block_symbol_number, const std::pair<int, int> start_point, const int start_rotation, int shape_id) {
    if(currentTetromino != nullptr) delete currentTetromino;
    this->currentTetromino = new tetromino(block_symbol_number, start_point, start_rotation, shape_id);
}

void tetromino_controller::generateNewRandomTetromino() {
    if(currentTetromino != nullptr) delete currentTetromino;
    int block_symbol_number = getRandNumber(4);
    int start_rotation = getRandNumber(3);
    int shape_id = getRandNumber(4);
    
    this->currentTetromino = new tetromino(block_symbol_number, std::pair<int, int>(game_constants::board_width / 2, 0), start_rotation, shape_id);
    
    for(int y = 0; y < this->getCurrentTetromino().getHeight(); y++) {
        for(int x = 0; x < this->getCurrentTetromino().getSingleLineWidth(y); x++) {
            if(this->factoryBoard[game_constants::board_width / 2 + x][y] != game_constants::empty_boardblock && getCurrentTetromino().checkShape(x, y)) throw(Game_Over("Game Over in Random Placement!!"));
        }
    }
}

tetromino_controller::tetromino_controller(char (&factoryBoard)[game_constants::board_width][game_constants::board_height]) : factoryBoard(factoryBoard) {

}

tetromino_controller::~tetromino_controller() {
    if(currentTetromino != nullptr) delete currentTetromino;
}

void tetromino_controller::draw() {
    this->getCurrentTetromino().drawTetromino(this->factoryBoard);
}