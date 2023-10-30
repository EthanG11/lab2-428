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

//TODO

two pair function
test pinochle evaluation function
add tie breaker code to exisiting hold emevaluation functions
step 17
