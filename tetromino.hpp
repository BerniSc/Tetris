#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

#include "game_constants.hpp"
#include "tetris_exception.hpp"

class tetromino {
    private:
        const char block_symbol;
        int width = 0, height = 0;
        std::pair<int, int> top_point;

        std::vector<std::vector<bool>> shape;

    public:
        explicit tetromino(const int block_symbol, const std::pair<int, int> start_point, const int start_rotation, const int shape_id);

        bool checkLeft(const char (&board)[game_constants::board_width][game_constants::board_height]);
        bool checkRight(const char (&board)[game_constants::board_width][game_constants::board_height]);
        bool checkDown(const char (&board)[game_constants::board_width][game_constants::board_height]);

        void moveLeft(char (&board)[game_constants::board_width][game_constants::board_height]);
        void moveRight(char (&board)[game_constants::board_width][game_constants::board_height]);
        void moveDown(char (&board)[game_constants::board_width][game_constants::board_height]);

        void moveUpDebug(char (&board)[game_constants::board_width][game_constants::board_height]);

        void rotate();

        bool checkRotation(char (&board)[game_constants::board_width][game_constants::board_height]);
        void rotateChecked(char (&board)[game_constants::board_width][game_constants::board_height]);


        char getSymbol() const;
        
        int getX() const;
        int getY() const;

        int getHeight() const;
        int getWidth() const;
        int getSingleLineWidth(int line) const;

        bool checkShape(int x, int y) const;

        void drawTetromino(char (&board)[game_constants::board_width][game_constants::board_height], bool clear = false);

        void setBounds() {
            tetromino::width = 0;
            tetromino::height = shape.size();
            for(int i = 0; i < tetromino::shape.size(); i++) {
                if(tetromino::shape[i].size() > tetromino::width) width = tetromino::shape[i].size();
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const tetromino& t);
};

#endif