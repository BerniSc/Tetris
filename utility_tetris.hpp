#ifndef UTILITY_TETRIS_HPP
#define UTILITY_TETRIS_HPP

//For input without enter
#include <unistd.h>
#include <termios.h>

#include <mutex>

#include "game_constants.hpp"
#include "tetromino.hpp"
#include "tetromino_factory.hpp"

void initialize_board(char (&board)[game_constants::board_width][game_constants::board_height]);

char getCharWithoutEnter();

#endif