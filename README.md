# Tetris

A console Port of Tetris for Linux based Consoles. The game is best played by increasing Font Size in the Console using 'Strg' + '+'
Variables for changing the gameplay are collected in "game_constants.hpp". Here it is possible to for example change the Symbols in which the Tetrominos are drawn.
It is also possible to add own Tetromino Shapes, speed up the game or change the Size of the Board.

(For Adding own Tetromino Shapes and 'Colors' the Hard-Coded Random Values in Tetromino-Controller have to be adapted)

Currently the Tetromino "colors" are {'#', 'O', '0', 'o', '@'} and for every Tetromino the "color" in which it is drawn is picked at random.

The current Tetrominos include:
    
      @@    @     @@@   @@    @@@    @
      @@    @@           @@    @     @@@
      
Control:
  - 'a' to move Tetromino to the left
  - 'd' to move Tetromino to the right
  - 's' to move Tetromino down faster
  - 'q' to quit Game
  
Plans for the Future:<br>Ci
&emsp; Remove Debug Features<br>
&emsp; Calculating Score -> Currently only number of Cleared Rows is collected<br>
&emsp; Actually implement Game-Over Handling -> Currently game just "crashes" and exits (Adding Catch)<br>
&emsp; Implement Progressive Speed<br>
&emsp; Adding more Tetrominos and replace Hard-Coded Values with dynamic values<br>
&emsp; Hunt Bugs<br>
  
  
![image](https://user-images.githubusercontent.com/117440705/223176607-f4c0c137-4fc9-43ad-8c4c-3f02fe2d616f.png)
