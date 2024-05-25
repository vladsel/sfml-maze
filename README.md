# sfml-maze
(14.05.2020) A simple C++ game using SFML.
"Maze". Management takes place with the help of arrows on the keyboard. It is necessary to guide the given character through the drawn maze.

The program creates an int Maze[width][height] matrix in order to draw a maze. The matrix has two values: 0 and 1. 1 – obstacles, labyrinth walls. 0 is a free path along which you can move. 
We also have variables: float x_pos, y_pos, variables set the position of the character on the screen. Variables x and y control the movement of the character according to the given matrix. First, they have the meaning of the character's initial position, that is, the point from which he starts to move.
The variable float pixel is the size of one block in width and height, which is drawn on the screen using a matrix.
In main, the graphical mode is entered, all necessary files are loaded for the program to work and a check is performed for correct loading, all necessary functions are called with the help of which the program is implemented.
void Screen(Sprite &maze_sprite, Text &text, RenderWindow &window, Music &music, Clock &time_clock, bool *screen_ptr) – the screen saver is displayed when the program starts. It is reported that pressing esc exits the program, enter starts the game, after pressing enter the music starts playing, the stopwatch starts, and the maze appears.
void Finish(Music &music, Sound &finish_sound, Text &text_finish, RenderWindow &window) - the end of the game. The user is notified, the maze music stops, the stopwatch stops, the game winner's music plays, after the music ends, the program closes because the user has completed the game.
void Draw_Maze(RenderWindow &window, Sprite &map_sprite) – a maze is drawn according to the given matrix.
void Left_Move(Sound &fly_sound, Sprite &hero_sprite) - move to the left. 
void Right_Move(Sound &fly_sound, Sprite &hero_sprite) - move to the right.
void Up_move(Sound &fly_sound, Sprite &hero_sprite) - move up.
void Down_Move(Sound &fly_sound, Sprite &hero_sprite) - move down.
void Error() – error, program exit with code 1.
