#include "tetromino.hpp"

/*********************************************************************************
*   @brief Constructor for Tetromino
*   @param[in] block_symbol int saying which in which symbol the Tetromino will be drawn -> possibilities int game_constants -> input not checked
*   @param[in] start_point start point of the Tetromino with first value x and second value y
*   @param[in] start_rotation start rotation of the Tetromino
*   @param[in] shape_id int saying which Tetromino will be drawn
*********************************************************************************/
tetromino::tetromino(const int block_symbol, const std::pair<int, int> start_point, const int start_rotation, const int shape_id) : block_symbol(game_constants::tetromino_blocks[block_symbol]), top_point(start_point) {
    tetromino::shape = tetromino_shapes::lookup_table_shapes.at(shape_id);
    //rotating current tetromino until it has the desired rotation
    for(int i = 0; i < start_rotation; i++) this->rotate();
    //Set Bounds of the rotated Tetromino
    this->setBounds();
};

/*********************************************************************************
*   @brief checks wheter moving the Tetromino left is allowed
*   @param[in] board Current GameBoard
*   @return bool -> true means allowed, false means wrong
*********************************************************************************/
bool tetromino::checkLeft(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Return instantly if already at 0
    if((this->getX() <= 0)) return false;
    //Iterate over every element in current shape
    for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->shape[y].size(); x++) {
            //if current element is actual part of tetromino proceed
            if(this->shape[y][x]) {
                //If element left of first actual element in row is not clear return false
                // && board[this->getX() + x - 1][this->getY() + y] != this->getSymbol()
                if(board[this->getX() + x - 1][this->getY() + y] != game_constants::empty_boardblock) return false;
                //break as element is not relevant anymore
                break;
            }
        }
    }
    //return true as standard
    return true;
}

/*********************************************************************************
*   @brief Function for moving the current Tetromino left
*   @param[in] board Current GameBoard
*********************************************************************************/
void tetromino::moveLeft(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkLeft(board)) {
        //Clear current tetromino from Board
        drawTetromino(board, true);
        this->top_point.first--; 
    }
}

/*********************************************************************************
*   @brief checks wheter moving the Tetromino right is allowed
*   @param[in] board Current GameBoard
*   @return bool -> true means allowed, false means wrong
*********************************************************************************/
bool tetromino::checkRight(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Check if Bounds are reached
    if(((this->getX() + this->width) >= game_constants::board_width)) return false;
    //Start in Top Row
    for(int y = 0; y < this->height; y++) {
        //Start with far right element
        for(int x = this->shape[y].size()-1; x >= 0; x--) {
            //If Element is in fact solid check if movement allowed and break from row -> rest irrelevant
            if(this->shape[y][x]) {
                //If Element to the right of solid solid as well, then return false
                if(board[this->getX() + x + 1][this->getY() + y] != game_constants::empty_boardblock) return false;
                break;
            }
        }
    }
    //return true as standard
    return true;
}

/*********************************************************************************
*   @brief Function for moving the current Tetromino right
*   @param[in] board Current GameBoard
*********************************************************************************/
void tetromino::moveRight(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkRight(board)) {
        //Clear current tetromino from Board
        drawTetromino(board, true);
        this->top_point.first++; 
    }
}

/*********************************************************************************
*   @brief checks wheter moving the Tetromino down is allowed
*   @param[in] board Current GameBoard
*   @return bool -> true means allowed, false means wrong
*********************************************************************************/
bool tetromino::checkDown(const char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Instantly exits if already at bottom
    if(((this->getY() + this->height) >= game_constants::board_height)) return false;
    //Iterate over every element -> start with bottom as bottom's relevant for moving down
    for(int x = 0; x < this->width; x++) {
        for(int y = this->height - 1; y >= 0; y--) {
            //If Bottom Element actual element procees
            if(this->shape[y][x]) {
                //If Block below not free return false, otherwise break;
                if(board[this->getX() + x][this->getY() + y + 1] != game_constants::empty_boardblock) return false;
                break;
            }
        }
    }
    return true;
}

/*********************************************************************************
*   @brief Function for moving the current Tetromino down
*   @param[in] board Current GameBoard
*********************************************************************************/
void tetromino::moveDown(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkDown(board)) {
        //Clear current tetromino from Board
        drawTetromino(board, true);
        this->top_point.second++; 
    } else {
        //Throw TetrominoStuck Exception for signaling generation of new Tetromino to Controller
        throw Tetromino_Stuck();
    }
}

/*********************************************************************************
*   @brief Function for Debug Purposes -> completley unchecked
*   @param[in] board Current GameBoard
*********************************************************************************/
void tetromino::moveUpDebug(char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Clear current tetromino from Board
    drawTetromino(board, true);
    this->top_point.second--; 
}

/*********************************************************************************
*   @brief Function to transpose and return a two-dim vector of bool
*   @param[in] shape Shape-Vector to transpose
*   @return transposed two-dim vector
*********************************************************************************/
std::vector<std::vector<bool>> transposeVector(const std::vector<std::vector<bool>> &shape) {
    int rows = shape.size();
    int cols = shape[0].size();

    std::vector<std::vector<bool>> transposedShape(cols, std::vector<bool>(rows));

    for(int y = 0; y < rows; y++) {
        for(int x = 0; x < cols; x++) {
            transposedShape[x][y] = shape[y][x];
        }
    }

    return transposedShape;
}

/*********************************************************************************
*   @brief checks wheter rotating the tetromino is allowed
*   @param[in] board Current GameBoard
*   @return bool -> true means allowed, false means wrong
*********************************************************************************/
bool tetromino::checkRotation(char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Iterate over every field of the new rotated Tetromino -> swaped y and x (width and height)
    for(int y = 0; y < this->width; y++) {
        for(int x = 0; x < this->height; x++) {
            //If Block not empty check further
            if(board[this->getX() + x][this->getY()+y] != game_constants::empty_boardblock) {
                //If "OutOfBounds for the Check" if is exited early -> no out of Bounds because Short-Circuit Evaluation
                if(y < this->shape.size() && x < this->shape[y].size() && this->shape[y][x]) {
                    //Needed for Short-Cicuit Evaluation
                } else {
                    //Return "False" as in no rotation allowed
                    return false;
                }
            }
        }
    }
    return true;
}

/*********************************************************************************
*   @brief Rotate current tetromino without checking if rotation allowed -> needed for spawning tetromino
*********************************************************************************/
void tetromino::rotate() {
    //Trying to transpose the vector
    std::vector<std::vector<bool>> transposedShape = transposeVector(this->shape);

    for(auto &row : transposedShape) {
        //Reversing every row of transposed vector using std::reverse of algortihm
        std::reverse(row.begin(), row.end());
    }
    //Assigning rotated Shape to current Shape
    this->shape = transposedShape;
    //Call SetBounds to set new Bounds
    this->setBounds();
}

/*********************************************************************************
*   @brief Function for rotating the current tetromino, but checked wheter rotation is allowed 
*   @param[in] board Current GameBoard
*********************************************************************************/
void tetromino::rotateChecked(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkRotation(board)) {
        this->drawTetromino(board, true);
        this->rotate();
    }
}

/*********************************************************************************
*   @brief Getter Function for Symbol of current Tetromino
*   @return Symbol of Current Tetromino
*********************************************************************************/
char tetromino::getSymbol() const {
    return this->block_symbol;
}

/*********************************************************************************
*   @brief Getter Function for X Position of current Tetromino
*   @return X Position of Current Tetromino (Upper left point)
*********************************************************************************/
int tetromino::getX() const {
    return this->top_point.first;
}

/*********************************************************************************
*   @brief Getter Function for Y Position of current Tetromino
*   @return Y Position of Current Tetromino (Upper left point)
*********************************************************************************/
int tetromino::getY() const {
    return this->top_point.second;
}

/*********************************************************************************
*   @brief Getter Function for Height of current Tetromino
*   @return Height of Current Tetromino (max Height)
*********************************************************************************/
int tetromino::getHeight() const {
    return this->height;
}

/*********************************************************************************
*   @brief Getter Function for Width of current Tetromino
*   @return Width of Current Tetromino (max Width)
*********************************************************************************/
int tetromino::getWidth() const {
    return this->width;
}

/*********************************************************************************
*   @brief Getter Function for Width of current Tetromino in specific line
*   @param[in] line index of Line for which width is wanted 
*   @return Width of Current Tetromino in specific line
*********************************************************************************/
int tetromino::getSingleLineWidth(const int line) const {
    return this->shape[line].size();
}

/*********************************************************************************
*   @brief Getter Function for special Point in Shape -> throws Tetris_Bounds if error
*   @param[in] x x-coordinate of Point
*   @param[in] y y-coordinate of Point
*   @return bool of Point in Shape of current Tetromino
*********************************************************************************/
bool tetromino::checkShape(int x, int y) const {
    if(y < this->getWidth() && x < this->getSingleLineWidth(y)) {
        return shape[y][x];
    }
    throw(Tetris_Bounds)("In Check Shape a Bounds Exception has been thrown");
    return false;
}

/*********************************************************************************
*   @brief Function to draw the current Tetromino -> also clear old Tetromino
*   @param[in] board Current GameBoard
*   @param[in] clear Flag wether the function should clear old or draw new -> normaly at false
*********************************************************************************/
void tetromino::drawTetromino(char (&board)[game_constants::board_width][game_constants::board_height], bool clear) {
    for(int y = 0; y < this->shape.size(); y++) {
        for(int x = 0; x < this->shape[y].size(); x++) {
            if(shape[y][x] && clear) board[getX() + x][getY() + y] = game_constants::empty_boardblock;
            if(shape[y][x] && !clear) board[getX() + x][getY() + y] = getSymbol();
        }
    }
}

/*********************************************************************************
*   @brief Overloaded function for printing Tetromino -> prints Shape
*********************************************************************************/
std::ostream& operator<<(std::ostream& os, const tetromino& t) {
    for(auto row : t.shape) {
        for(auto symbol : row) {
            os << symbol;
        }
        os << '\n';
    }
    return os;
}