#ifndef TETROMINO_CONTROLLER_HPP
#define TETROMINO_CONTROLLER_HPP

#include "tetromino.hpp"
#include "game_constants.hpp"
#include "tetris_exception.hpp"
#include "utility_tetris.hpp"

struct tetromino;

struct tetromino_controller {
    public :
        tetromino *currentTetromino;
        char (&factoryBoard)[game_constants::board_width][game_constants::board_height];

        tetromino_controller(char (&factoryBoard)[game_constants::board_width][game_constants::board_height]);        

        virtual ~tetromino_controller();

        void generateNewTetromino(const int block_symbol_number, const std::pair<int, int> start_point, const int start_rotation, int shape_id);

        void generateNewRandomTetromino();

        tetromino & getCurrentTetromino(); 

        void draw();
};

#endif