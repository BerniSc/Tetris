#ifndef GAME_CONSTANTS_HPP
#define GAME_CONSTANTS_HPP

#include <vector>
#include <chrono>

namespace game_constants {
    constexpr inline int board_height = 10;
    constexpr inline int board_width = 40;

    constexpr inline char tetromino_blocks[] = {'#', 'O', '0', 'o', '@'};

    constexpr inline char empty_boardblock = '.';

    //constexpr inline char falling_tetromino_block = '@';

    //Wait TIme is number of possible inputs during one "Tick" -> one Tick is Wait Time times factor
    //Standard is 250, 10
    constexpr inline std::chrono::milliseconds wait_time = std::chrono::milliseconds(125);
    constexpr inline int falltime_factor = 20; 
}

namespace tetromino_shapes {
    //Tetromino Table angabe von unten rechts nach oben
    //Shape Table Tetromnio 1 -> Square
    const inline std::vector<std::vector<bool>> shape_1 = {{true, true}, {true, true}};        //Normal Rotation
    //Shape Table Tetromino 2 -> small Triangle Block
    const inline std::vector<std::vector<bool>> shape_2 = {{true, true}, {true, false}}; 
    //Shape Table Tetromino 3 -> Small I Block -> First orientation vertical
    const inline std::vector<std::vector<bool>> shape_3 = {{true}, {true}, {true}};
    //Shape Table Tetromino 4 -> Small L Block -> First orientation vertical
    const inline std::vector<std::vector<bool>> shape_4 = {{true, true}, {true}, {true}};
    //Shape Table Tetromino 5 -> Small T Block
    const inline std::vector<std::vector<bool>> shape_5 = {{true, true, true}, {false, true}};

    const inline std::vector<std::vector<std::vector<bool>>> lookup_table_shapes = {shape_1, shape_2, shape_3, shape_4, shape_5};
}


#endif
