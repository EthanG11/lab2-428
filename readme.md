Names: Sarah Wilkinson and Ethan Gray
emails: s.z.wilkinson@wustl.edu and ethan.gray@wustl.edu

LAB 1

errors: 
1. template argument deduction/substitution failed
The cause of this error was a circular dependency. To fix this we removed the extra includes that were creating this circular dependency.
2. a template argument may not reference a variable-length array type
This was caused due to trying to pass an array to the shared_ptr that initializes a game with a size value that is not initiated until run time.
After learning that you can't use a run time value for the size of an array, we modified our logic to pass in the whole argv into the respective
Game constructors and handling the player list logic there instead of in the lab1.cpp file.
3. We were getting this error for no command line arguments given:

-bash-4.2$ ./lab1
terminate called after throwing an instance of 'std::logic_error'
  what():  basic_string::_M_construct null not valid
Aborted

Caused by trying to convert nothing into a string.
We fixed it by adding a condition check for more than one command line argument before anything else happens in the main.


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

4. Poker with 2 players
[e.h.gray@linuxlab002 428Lab1]$ ./lab1 Holdem a b
a: 6  2  

b: 10  5  

BOARD(flop):9  5  8  
BOARD(turn):9  5  8  7  
BOARD(river):9  5  8  7  2  
nould you like to end the game? yes or no: 
a: 9  5  

b: 3  9  

BOARD(flop):A  8  K  
BOARD(turn):A  8  K  10  
BOARD(river):A  8  K  10  6  
would you like to end the game? yes or no: 
yes


5. Poker w/ wrong number of players with proper exit codes

-bash-4.2$ ./lab1 Holdem a
Usage: ./lab1 GAMENAME Player1 Player2 Player3 ... PlayerN
HoldEm: 2-9 players
Pinochle: 4 players
-bash-4.2$ echo $?
3


6. no additional command line arguments given beyond program name with proper exit code

-bash-4.2$ ./lab1
Usage: ./lab1 GAMENAME Player1 Player2 Player3 ... PlayerN
HoldEm: 2-9 players
Pinochle: 4 players
-bash-4.2$ echo $?
2