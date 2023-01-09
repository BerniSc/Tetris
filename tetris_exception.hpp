#ifndef TETRIS_EXCEPTION_HPP
#define TETRIS_EXCEPTION_HPP

#include <exception>
#include <string>

class Tetris_Exception {
    protected:
        static int exceptionID;
        const std::string message;
    public:
        Tetris_Exception(std::string msg);

        std::string const print_what() const;
};

class Tetromino_Stuck : public Tetris_Exception {
    protected:
        static int placed_tetrominos;
    public:
        int const getPlacedTetrominos();

        Tetromino_Stuck();
        Tetromino_Stuck(std::string msg);
};

class Game_Over : public Tetris_Exception {
    public:
        Game_Over();
        Game_Over(std::string msg);
};

class Tetris_Rotation_Bounds : public Tetris_Exception {
    public :
        Tetris_Rotation_Bounds();
        Tetris_Rotation_Bounds(std::string msg);
};

#endif