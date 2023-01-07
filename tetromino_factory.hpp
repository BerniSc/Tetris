#ifndef TETROMINO_FACTORY_HPP
#define TETROMINO_FACTORY_HPP

#include "tetromino.hpp"
#include "game_constants.hpp"

struct tetromino;

struct tetromino_factory {
    public :
        tetromino *currentTetromino;
        char (&factoryBoard)[game_constants::board_width][game_constants::board_height];

        tetromino_factory(char (&factoryBoard)[game_constants::board_width][game_constants::board_height]);        

        virtual ~tetromino_factory();

        void generateNewTetromino(const int block_symbol_number, const std::pair<int, int> start_point, const int start_rotation, int shape_id);


        tetromino & getCurrentTetromino(); 

        void moveDown() {
            getCurrentTetromino().moveDown(factoryBoard);
        }
};

#endif