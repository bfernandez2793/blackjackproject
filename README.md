# blackjackproject

This is a two player blackjack game. It allows for multiple plays and for the player to place.

Branch exp was used to implement the game early on using dynamic memory, while following RAII. This proved difficult as getting new cards
for the players hand requires an extra set of pointers for each player anytime they wanted a new card. Essentially this would amount to 
writing a set of classes that would work similar to a list. So instead I implemented the project using std::list.

When trying to run the code all the png files should be in the build qt file in order for the project to run.
