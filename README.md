# BattleshipGame
TITLE: 
Thaddious Douthit, Battleship Game

PROBLEM DESCRIPTION: 
I created a user interactive Battleship game that allows the user to place their battleships and play against the computer. The computer 
has pre-defined ship locations but takes in one of 3 random text files containing all the possible coordinates on the board to make random 
attacks against the user (created in excel and then converted to .txt). The general game displays two boards: the computer’s board with 
the ship locations hidden and the user board with the user defined ship locations on the board. The game has the user call out a location 
on the computer’s board and if a hit occurs the computer board will update that location with an “X” and with miss an “O”. The computer then uses its next location coordinates, which is taken from a vector that stores the file’s read 
coordinates, to call out a location on the user board and then update the user board with an “X” for a hit or an “O” for a miss and it 
further tells the user the result of the computer’s attack. The computer and the user attack back and forth, as ships “sink” the user is 
notified what ship has been sunk, until the computer or the user has sunken all the other’s ships. A win or lose message is displayed at 
the end of the game which is denoted by one player’s ships being all sunk.

PROGRAM DOCUMENTATION: 

Run Program
To run the program, ensure that the 3 random computer attack location files are in the same file as the main. These three files are 
called “computer_gameV1”, “computer_gameV2”, “computer_gameV3”. With the files in the same location, the program just needs to be run, 
and the user just needs to follow the directions displayed on the screen. Note the user should extended the run display window to its 
maximum size to help see the game being played.
Modify/extend Program
Features that could be added to this program are random ship boards for the computer, which could be created from reading an input 
file, better display interaction (i.e a single window that has the two boards and user input areas in the same location), and color to 
the ships, misses, and hits. The program itself functions well and can identify and correct all user input mistakes, as far as I am aware 
of, which means it could be a good base model for a better interactive battleship game.
 
TESTS: 
Program can correct these User input Errors
1)	User inputs an incorrect coordinate location like
a.	a0, j11, 122, 9b, j0, k1, p11, p, a, etc.
i.	has user enter a new coordinate location until correct

2)	User places a ship on another ship while placing a ship
a.	has user enter a new ship orientation and starting location until correct

3)	User places a ship that would be off the board
a.	Has user pick a new starting location until correct

4)	User enters an incorrect ship orientation while placing a ship 
a.	Has user enter a new ship orientation until correct

5)	User has made an attack at a location before
a.	Has user enter a new attack location until that attack location has not been made before

REFLECTIONS: 
I learned a lot from this project specifically how to plan out and develop functions based on desired outcomes, how to 
account for user input error, how to use struct header files to store and access desired data, and various techniques to 
debug code such as using another main.cpp file to try and test functions with data. This project also helped me understand classes, 
as I did not really understand how they worked until doing this project. One thing that I didn’t really do a great job of in this 
project was manage how data and memory was being referenced initially and even a little bit in the final program. In the future, 
I am going to pay more attention to how data is stored and referenced through memory to help ease the flow of the program and aid in 
the overall function of the program. Furthermore, in the future I am going to try and plan out the program even more than I did this 
time around to help save on the time taken to go back in and recreate functions. Overall, this project was a lot of fun. It also was 
very grindy and chippy but the satisfaction of creating, debugging, and implementing a puzzle piece of the program properly was very 
satisfying and having a fully functional program was super rewarding.
