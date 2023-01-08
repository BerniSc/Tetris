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
};

class Tetromino_Stuck : public Tetris_Exception {
    public:
        Tetromino_Stuck();
        Tetromino_Stuck(std::string msg);

        std::string const print_what() const;
};

#endif