Names: Sarah Wilkinson and Ethan Gray
emails: s.z.wilkinson@wustl.edu and ethan.gray@wustl.edu

LAB 2

8. We chose to use the default copy constructor as the only member variable is a vector, which has its own copy constructor allowing us to perform a successful deep copy.

Added an == operator to the card class.

Created a checkAllEightCards function that checks a hand for one of the 8 card combinations as well as the corresponding 4 card combinations.

Created a getCardRange function that returns a pair of iterators to the start of a card rank in the sorted vecotr and the end of a card rank in the sorted vector.

Created a findXofaKind function.

Created a checkForStraight function.

Added a vector<pokerrank> tieBreakers to the nested struct. We did this because it is more efficient to store the tieBreakers values in the call to the holdem_hand_evlaluatoin function instead of recheking the hands for the tiebreakers values in the < operator. So this meant that we added 4 additional parameters that are referecnes to pokerRanks for the 4 possible tiebreakers. These tie breakers values are stored in the tieBreakers vector<pokerRank>, so that they can be used in the < operator that we created.

Moved the undefined value in pokerRank to the lowest value so that the < operator for HoldEmHand Ranks would work as expected. Also had to adjust the ++ operator for poker so that it would work with this change.

//TODO

test pinochle evaluation function
test poker

runs:

1. test pinochle finding a pinochle

ethan@ethan-XPS-15-7590:~/cse428/Lab2$ ./lab2 Pinochle a b c d
a: A C A S A C Q C 10 C J C A D 9 C J H Q D 10 D A S

b: 9 S J C Q D 9 C K S 10 D A H 9 D 10 S Q H 9 S K D

c: J H J S Q S J D J S K C 10 C 10 S J D Q H 9 H A H

MELD: name: pinochle points: 40

d: A D Q C K C K H 9 H K D K H 10 H Q S 10 H 9 D K S

would you like to end the game? yes or no:

2. test double pinochle

would you like to end the game? yes or no:
no
a: Q H K C K D 10 C 9 S A C 9 D Q D 10 C 10 D 10 H 9 D

b: Q C 10 S Q H A H J H A D A C K D J C 9 H J H 9 H

c: Q S Q D K S A S J D 10 H J D Q S J S 9 C A H J S

MELD: name: doublepinochle points: 300

d: 10 D Q C A S K S K H A D J C K H K C 9 S 9 C 10 S

would you like to end the game? yes or no:

3. no melds found

would you like to end the game? yes or no:
no
a: A D Q S 10 C 9 C J H 10 D Q D K C K H A H 10 H J C

b: Q S A H K S Q H 10 C A C Q C 9 H 9 S Q H Q C K D

c: A S K H 10 S 9 C 9 S K S J S A D 9 H J D 10 H K C

d: A S 9 D Q D J H J D K D J S 10 S 10 D 9 D A C J C

would you like to end the game? yes or no:

4. test other melds

Poker tests:

5. test ranks x high and pair

ethan@ethan-XPS-15-7590:~/cse428/Lab2$ ./lab2 Holdem a b c d
a: A C 5 C

b: 8 H K H

c: 3 H 5 H

d: 8 C 9 D

BOARD(flop):2 D J C A D  
Player name: c
cards: 5 H 3 H A D J C 2 D  
 Hand rank: X High
Player name: d
cards: 9 D 8 C A D J C 2 D  
 Hand rank: X High
Player name: b
cards: K H 8 H A D J C 2 D  
 Hand rank: X High
Player name: a
cards: 5 C A C A D J C 2 D  
 Hand rank: Pair
would you like to end the game? yes or no:

6. test ties within pairs
   BOARD(flop):9 S J D J H  
   Player name: c
   cards: 10 C 7 C J H J D 9 S  
    Hand rank: Pair
   Player name: d
   cards: 3 S Q C J H J D 9 S  
    Hand rank: Pair
   Player name: a
   cards: Q D 5 H J H J D 9 S  
    Hand rank: Pair
   Player name: b
   cards: A S 3 C J H J D 9 S  
    Hand rank: Pair
   would you like to end the game? yes or no:

7. test three of a kind and two pair

would you like to end the game? yes or no:
no
a: 6 C K S

b: 5 D 4 H

c: 7 H 4 D

d: 9 H J C

e: K D Q C

f: 7 C K H

g: 8 C 5 C

h: 6 D 10 D

i: 9 D 10 H

BOARD(flop):8 D 8 S 9 C  
Player name: b
cards: 4 H 5 D 9 C 8 S 8 D  
 Hand rank: Pair
Player name: c
cards: 4 D 7 H 9 C 8 S 8 D  
 Hand rank: Pair
Player name: h
cards: 10 D 6 D 9 C 8 S 8 D  
 Hand rank: Pair
Player name: a
cards: K S 6 C 9 C 8 S 8 D  
 Hand rank: Pair
Player name: f
cards: K H 7 C 9 C 8 S 8 D  
 Hand rank: Pair
Player name: e
cards: Q C K D 9 C 8 S 8 D  
 Hand rank: Pair
Player name: i
cards: 10 H 9 D 9 C 8 S 8 D  
 Hand rank: Two Pair
Player name: d
cards: J C 9 H 9 C 8 S 8 D  
 Hand rank: Two Pair
Player name: g
cards: 5 C 8 C 9 C 8 S 8 D  
 Hand rank: Three of a kind
would you like to end the game? yes or no:

8. test straight
   would you like to end the game? yes or no:
   no
   a: A H 4 C

b: 2 H 5 D

c: 10 S 2 D

d: 8 S 3 C

e: 7 C 9 S

f: 4 D J S

g: 6 H 3 H

h: 4 S 7 H

i: Q H J C

BOARD(flop):10 D 6 D 8 D  
Player name: b
cards: 5 D 2 H 8 D 6 D 10 D  
 Hand rank: X High
Player name: h
cards: 7 H 4 S 8 D 6 D 10 D  
 Hand rank: X High
Player name: f
cards: J S 4 D 8 D 6 D 10 D  
 Hand rank: X High
Player name: i
cards: J C Q H 8 D 6 D 10 D  
 Hand rank: X High
Player name: a
cards: 4 C A H 8 D 6 D 10 D  
 Hand rank: X High
Player name: g
cards: 3 H 6 H 8 D 6 D 10 D  
 Hand rank: Pair
Player name: d
cards: 3 C 8 S 8 D 6 D 10 D  
 Hand rank: Pair
Player name: c
cards: 2 D 10 S 8 D 6 D 10 D  
 Hand rank: Pair
Player name: e
cards: 9 S 7 C 8 D 6 D 10 D  
 Hand rank: Straight
would you like to end the game? yes or no:

9. test flush
   would you like to end the game? yes or no:
   no
   a: 10 D 10 S

b: 4 S 5 C

c: 6 D K C

d: A C 8 C

e: Q S 6 S

f: 2 H 6 H

g: 2 C 8 D

h: 9 D 2 S

i: K S 8 S

BOARD(flop):10 H 3 H 5 H  
Player name: g
cards: 8 D 2 C 5 H 3 H 10 H  
 Hand rank: X High
Player name: h
cards: 2 S 9 D 5 H 3 H 10 H  
 Hand rank: X High
Player name: e
cards: 6 S Q S 5 H 3 H 10 H  
 Hand rank: X High
Player name: c
cards: K C 6 D 5 H 3 H 10 H  
 Hand rank: X High
Player name: i
cards: 8 S K S 5 H 3 H 10 H  
 Hand rank: X High
Player name: d
cards: 8 C A C 5 H 3 H 10 H  
 Hand rank: X High
Player name: b
cards: 5 C 4 S 5 H 3 H 10 H  
 Hand rank: Pair
Player name: a
cards: 10 S 10 D 5 H 3 H 10 H  
 Hand rank: Three of a kind
Player name: f
cards: 6 H 2 H 5 H 3 H 10 H  
 Hand rank: Flush
would you like to end the game? yes or no:

10. test full house

would you like to end the game? yes or no:
no
a: 9 S Q C

b: 2 S 7 C

c: Q H 6 C

d: Q D 2 H

e: 6 D 4 H

f: 8 S 8 D

g: 4 C 10 C

h: J C 4 D

i: 9 C 10 H

BOARD(flop):9 D 9 H 10 D  
Player name: e
cards: 4 H 6 D 10 D 9 H 9 D  
 Hand rank: Pair
Player name: b
cards: 7 C 2 S 10 D 9 H 9 D  
 Hand rank: Pair
Player name: h
cards: 4 D J C 10 D 9 H 9 D  
 Hand rank: Pair
Player name: d
cards: 2 H Q D 10 D 9 H 9 D  
 Hand rank: Pair
Player name: c
cards: 6 C Q H 10 D 9 H 9 D  
 Hand rank: Pair
Player name: f
cards: 8 D 8 S 10 D 9 H 9 D  
 Hand rank: Two Pair
Player name: g
cards: 10 C 4 C 10 D 9 H 9 D  
 Hand rank: Two Pair
Player name: a
cards: Q C 9 S 10 D 9 H 9 D  
 Hand rank: Three of a kind
Player name: i
cards: 10 H 9 C 10 D 9 H 9 D  
 Hand rank: Full House
would you like to end the game? yes or no:
