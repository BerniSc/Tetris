#include "tetromino.hpp"

using std::cout;
using std::endl;

tetromino::tetromino(const char block_symbol, const std::pair<int, int> start_point, const int start_rotation, int shape_id) : block_symbol(block_symbol), top_point(start_point) {
    tetromino::shape = tetromino_shapes::lookup_table_shapes.at(shape_id);
    for(int i = 0; i < start_rotation; i++) this->rotate();
    this->setBounds();
};

bool tetromino::checkLeft(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if((this->getX() <= 0)) return false;
    //std::cout << "Second" << std::endl;
    for(int y = 0; y < this->height; y++) {
        //std::cout << y << std::endl;
        for(int x = 0; x < this->shape[y].size(); x++) {
            //std::cout << "Breaking at" << x << "|" << y << std::endl;
            //Changed x and y
            if(this->shape[y][x]) {
            //if(this->shape[y][x]) {
                //std::cout << board[this->getX() + x - 1][this->getY() + y] << std::endl;
                //if(board[this->getX() + x - 1][this->getY() + y] != game_constants::empty_boardblock) return false;
                //cout << (board[this->getX() + x - 1][this->getY() + y] != game_constants::empty_boardblock && board[this->getX() + x - 1][this->getY() + y] != this->getSymbol()) << endl;
                if(board[this->getX() + x - 1][this->getY() + y] != game_constants::empty_boardblock && board[this->getX() + x - 1][this->getY() + y] != this->getSymbol()) {
                    cout << board[this->getX() + x - 1][this->getY() + y] << endl;
                    return false;
                }
                break;
            }
        }
    }
    return true;
}

void tetromino::moveLeft(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkLeft(board)) {
        drawTetromino(board, true);
        this->top_point.first--; 
    }
}

bool tetromino::checkRight(char (&board)[game_constants::board_width][game_constants::board_height]) {
    //Check if Bounds are reached
    if(((this->getX() + this->width) >= game_constants::board_width)) return false;
    //Start in Top Row
    for(int y = 0; y < this->height; y++) {
        //Start with far right element
        for(int x = this->shape[y].size()-1; x >= 0; x--) {
            //If Element is in fact solid check if movement allowed and break from row -> rest irrelevant
            //if(this->shape[y][x]) {
            //Changed x and y
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

void tetromino::moveRight(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkRight(board)) {
        drawTetromino(board, true);
        this->top_point.first++; 
    }
}

bool tetromino::checkDown(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(((this->getY() + this->height) >= game_constants::board_height)) return false;
    //std::cout << "Second" << std::endl;
    /*for(int y = this->height - 1; y >= 0; y--) {
        //std::cout << y << std::endl;
        for(int x = 0; x < this->shape[y].size(); x++) {
            if(this->shape[y][x] && ((this->getY() + this->height) < game_constants::board_height)) {
                std::cout << (board[this->getX() + x][this->getY() + y + 1] != game_constants::empty_boardblock)  << board[this->getX() + x][this->getY() + y + 1] << std::endl;
                if(board[this->getX() + x][this->getY() + y + 1] != game_constants::empty_boardblock) return false;
                break;
            }
        }
    }*/
    /*
    for(int x = 0; x < this->shape[this->height - 1].size(); x++) {
        if(shape[this->height - 1][x] && ((this->getY() + this->height) < game_constants::board_height)) {
            if(board[this->getX() + x][this->getY() + this->height] != game_constants::empty_boardblock) return false;
        }
    }
    */
   //cout << *this << endl;
    for(int y = this->height - 1; y >= 0; y--) {
        for(int x = 0; x < this->shape[y].size(); x++) {
            //cout << "X=" << x << "|" << this->shape[y].size() << "  " << "Y=" << y << endl;
            //changed x and y
            if(this->shape[y][x]) {
                if(board[this->getX() + x][this->getY() + y + 1] != game_constants::empty_boardblock && board[this->getX() + x][this->getY() + y + 1] != this->getSymbol()) return false;
                //break;
            }
        }
    }
    return true;
}

void tetromino::moveDown(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkDown(board)) {
        drawTetromino(board, true);
        this->top_point.second++; 
    }
}

void tetromino::moveUpDebug(char (&board)[game_constants::board_width][game_constants::board_height]) {
    drawTetromino(board, true);
    this->top_point.second--; 
}

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

bool tetromino::checkRotation(char (&board)[game_constants::board_width][game_constants::board_height]) {
    /*for(int y = 0; y < this->height; y++) {
        for(int x = 0; x < this->width; x++) {
            if(board[this->getX() + x][this->getY()+y] != game_constants::empty_boardblock && board[this->getX() + x][this->getY() + y] != this->getSymbol()) return false;
        }
    }*/
    for(int y = 0; y < this->width; y++) {
        cout << "Y:" << y <<  "Width " << this->width << endl;
        for(int x = 0; x < this->height; x++) {
            cout << "X:" << x << endl;
            cout << board[this->getX() + x][this->getY()+y] << endl;
            if(board[this->getX() + x][this->getY()+y] != game_constants::empty_boardblock && board[this->getX() + x][this->getY() + y] != this->getSymbol()) return false;
        }
    }
    return true;
}

void tetromino::rotate() {
    //Trying to transpose the vector
    std::vector<std::vector<bool>> transposedShape = transposeVector(this->shape);

    for(auto &row : transposedShape) {
        //Reversing every row of transposed vector using std::reverse of algortihm
        std::reverse(row.begin(), row.end());
    }
    this->shape = transposedShape;
    this->setBounds();
}

void tetromino::rotateChecked(char (&board)[game_constants::board_width][game_constants::board_height]) {
    if(checkRotation(board)) {
        this->drawTetromino(board, true);
        this->rotate();
    }
}

char tetromino::getSymbol() {
    return this->block_symbol;
}

int tetromino::getX() {
    return this->top_point.first;
}

int tetromino::getY() {
    return this->top_point.second;
}

void tetromino::drawTetromino(char (&board)[game_constants::board_width][game_constants::board_height], bool clear) {
    //cout << *this << endl;
    for(int y = 0; y < this->shape.size(); y++) {
        //cout << "hi ";
        //cout << this->shape.size() << endl;
        for(int x = 0; x < this->shape[y].size(); x++) {
            //cout << "ShapeSize" << this->shape[y].size() << endl;
            //cout << x << "|" << y << endl;
            //Changed from x y to y x
            if(shape[y][x] && !clear) board[getX() + x][getY() + y] = getSymbol();
            if(shape[y][x] && clear) board[getX() + x][getY() + y] = game_constants::empty_boardblock;
        }
    }
}

//tetromino tetromino::operator=(const tetromino &other) {
//    
//}

std::ostream& operator<<(std::ostream& os, const tetromino& t) {
    for(auto row : t.shape) {
        for(auto symbol : row) {
            os << symbol;
        }
        os << '\n';
    }
    return os;
}


        //tetromino_1::tetromino_1(const char block_symbol, const std::pair<int, int> start_point, const int current_rotation) : tetromino(block_symbol, start_point, current_rotation, tetromino_shapes::shape_1_0) {

        //}