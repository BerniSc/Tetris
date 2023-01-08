COMPILER = "g++"
PROJECTNAME = tetris_output
SOURCE = game.cpp tetromino.cpp tetromino_factory.cpp utility_tetris.cpp tetris_exception.cpp
FLAGS = -std=c++17 -pthread

$(PROJECTNAME) : $(SOURCE)
		$(COMPILER) $(SOURCE) $(FLAGS) -o $(PROJECTNAME)