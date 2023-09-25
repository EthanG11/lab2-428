Names: Sarah Wilkinson and Ethan Gray
emails: s.z.wilkinson@wustl.edu and ethan.gray@wustl.edu

LAB 1

errors: 
1. template argument deduction/substitution failed
The cause of this error was a circular dependency. To fix this we removed the extra includes that were creating this circular dependency.
2. a template argument may not reference a variable-length array type
This was caused due to trying to pass an array to the shared_ptr that initializes a game with a size value that is not initiated until run time. After learning that you can't use a run time value for the size of an array, we modified our logic to pass in the whole argv into the respective Game constructors and handling the player list logic there instead of in the lab1.cpp file.

Successful runs:

1. Pinochle w/ 4 players
[e.h.gray@linuxlab002 Lab1]$ ./lab1 Pinochle j a d e
j: 10  Q  Q  10  J  K  J  Q  9  K  A  K  

a: Q  J  9  J  A  9  9  K  10  10  A  10  

d: Q  J  J  10  A  10  A  A  K  9  10  K  

e: K  Q  K  A  Q  9  9  9  A  J  J  Q  

would you like to end the game? yes or no: 
no
j: J  J  10  K  J  K  J  9  K  10  K  A  

a: 9  K  10  Q  10  K  K  J  Q  9  Q  J  

d: 9  9  9  9  Q  9  A  A  10  K  A  A  

e: J  Q  A  10  Q  10  Q  10  A  J  A  Q  
would you like to end the game? yes or no: 
yes

2. Pinochle with wrong number players
[e.h.gray@linuxlab002 Lab1]$ ./lab1 Pinochle j a d
Usage: ./lab1 GAMENAME Player1 Player2 Player3 ... PlayerN
HoldEm: 2-9 players
Pinochle: 4 players

3. Wrong game name

[e.h.gray@linuxlab002 Lab1]$ ./lab1 Chess j a d
Game not successfuly created.

4. Poker with 3 players
[e.h.gray@linuxlab002 Lab1]$ ./lab1 Holdem j a d
j: K  A  

a: 2  8  

d: 4  2  

BOARD(flop):K  4  J  2  3  
BOARD(turn):K  4  J  2  3  
BOARD(river):K  4  J  2  3  
would you like to end the game? yes or no: 
no
j: 6  2  

a: 10  6  

d: 7  K  

BOARD(flop):10  4  5  K  4  
BOARD(turn):10  4  5  K  4  
BOARD(river):10  4  5  K  4  
would you like to end the game? yes or no: 
yes

5. Poker w/ wrong number of players

[e.h.gray@linuxlab002 Lab1]$ ./lab1 Holdem j
Usage: ./lab1 GAMENAME Player1 Player2 Player3 ... PlayerN
HoldEm: 2-9 players
Pinochle: 4 players



