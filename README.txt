Battleship

Compile: g++ -g -std=c++11 main.cpp src/Ship.cpp src/Player.cpp src/Board.cpp src/Computer.cpp src/Game.cpp -o Battleship
Run: ./Battleship Ships

Best if played with the terminal at 80x31 pixels

This is Battleship in the terminal!
There are two choices to play, either single player or multiplayer.
For multiplayer, both players have 5 ships and must place their ships on their 10x10 board.
The axis' are labeled and the players must enter in the coordinates of where they'd like to place the beginning of their ship.
Once the player has decided where the beginning of their ship will be placed they will the pick which direction the rest of the ship will go.
The game makes sure that no ship is placed on top of another and that all of the ship is placed within the coordinate system.

After both players have created their boards that game begins!
The game will notify which players turn it is and when it's your turn you'll see two boards.
I'm gonna assume you know what battleship and give a brief explanation of what's shown.
One board on top that is the enemies board as a concealed version (doesn't show the ships) and one board on the bottom that
you board. The player must enter in a target on the enemies board, but targets will show up on both boards and "M"s and "X"s.
X's are hits and M's are misses.

Once a player loses all their ships they have lost!
The winner gets to choose if they'd like to enter their name into a list of winners file.

Single player is exactly the same thing except the second player is a computer that you play against.

Steps:
1) Each player must place their ships on their boards
2) After the boards are finished the actual game will begin
3) Each round the specified player must input coordinates of where they'd like to attack on the enemies board
4) If the target is a "hit" it will get marked as a "X" and the game will tell you that you got a hit
5) If the target is a "miss" it will get marked as a "M" and the game will tell you that you missed
6) Once a player destroys all of the other players ships before all theirs die, he/she wins
7) Winner is asked if they want to enter their name into a document of winners
