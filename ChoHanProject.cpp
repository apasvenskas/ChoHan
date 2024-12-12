#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

class Die {
private:
    int sides;
    int value;

public:
    Die(int numSides = 6) : sides(numSides), value(0) {}

    void roll() {
        value = rand() % sides + 1;
    }

    int getSides() const {
        return sides;
    }

    int getValue() const {
        return value;
    }
};

class Player {
private:
    std::string name;
    std::string guess;
    int points;

public:
    Player() : name(""), guess(""), points(0) {}

    void setName(const std::string& playerName) {
        name = playerName;
    }

    void setGuess(const std::string& playerGuess) {
        guess = playerGuess;
    }

    void addPoints() {
        points++;
    }

    std::string getName() const {
        return name;
    }

    std::string getGuess() const {
        return guess;
    }

    int getPoints() const {
        return points;
    }
};

class Dealer {
private:
    Die die1;
    Die die2;

public:
    Dealer() : die1(6), die2(6) {}

    void rollDice() {
        die1.roll();
        die2.roll();
    }

    int getDie1Value() const {
        return die1.getValue();
    }

    int getDie2Value() const {
        return die2.getValue();
    }

    std::string getChoOrHan() const {
        int total = getDie1Value() + getDie2Value();
        return (total % 2 == 0) ? "Cho" : "Han";
    }
};

class ChoHan {
private:
    int maxRounds;
    Player player1;
    Player player2;
    Dealer dealer;

public:
    ChoHan(int rounds) : maxRounds(rounds) {}

    void start() {
        // Seed random number generator
        srand(static_cast<unsigned int>(time(nullptr)));

        // Get player names
        std::string name1, name2;
        
        std::cout << "Welcome to Cho-Han game!\n";
        
        // Clear any previous input buffer
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Enter Player 1's name: ";
        std::getline(std::cin, name1);
        player1.setName(name1);

        std::cout << "Enter Player 2's name: ";
        std::getline(std::cin, name2);
        player2.setName(name2);

        // Play rounds
        for (int round = 1; round <= maxRounds; ++round) {
            std::cout << "\n------------------------------ \n";
            std::cout << "Now playing round " << round << ":\n";
            playRound();
        }

        // Display final results
        displayGrandWinner();
    }

private:
    void playRound() {
        // Get player guesses
        std::string guess1, guess2;
        
        // Validate player 1's guess
        while (true) {
            std::cout << "Enter the guess for player " << player1.getName() << " (Cho/Han): ";
            std::getline(std::cin, guess1);
            if (guess1 == "Cho" || guess1 == "Han") {
                player1.setGuess(guess1);
                break;
            }
            std::cout << "Invalid guess. Please enter 'Cho' or 'Han'.\n";
        }

        // Validate player 2's guess
        while (true) {
            std::cout << "Enter the guess for player " << player2.getName() << " (Cho/Han): ";
            std::getline(std::cin, guess2);
            if (guess2 == "Cho" || guess2 == "Han") {
                player2.setGuess(guess2);
                break;
            }
            std::cout << "Invalid guess. Please enter 'Cho' or 'Han'.\n";
        }

        // Roll dice
        dealer.rollDice();
        std::string result = dealer.getChoOrHan();

        // Display dice rolls and result
        std::cout << "The dealer rolled " << dealer.getDie1Value() 
                  << " and " << dealer.getDie2Value() << std::endl;
        std::cout << "Result: " << result << " (";
        std::cout << (result == "Cho" ? "even" : "odd") << ")\n";

        // Check guesses and award points
        checkGuess(player1, result);
        checkGuess(player2, result);
    }

    void checkGuess(Player& player, const std::string& dealerResult) {
        std::cout << "The player " << player.getName() 
                  << " guessed " << player.getGuess() 
                  << " (" << (player.getGuess() == "Cho" ? "even" : "odd") << ")\n";

        if (player.getGuess() == dealerResult) {
            std::cout << "Awarding 1 point to " << player.getName() << std::endl;
            player.addPoints();
        }
    }

    void displayGrandWinner() {
        std::cout << "\n------------------------------ \n";
        std::cout << "Game over. Here are the results:\n";
        std::cout << player1.getName() << ": " << player1.getPoints() << " points\n";
        std::cout << player2.getName() << ": " << player2.getPoints() << " points\n";

        if (player1.getPoints() > player2.getPoints()) {
            std::cout << player1.getName() << " is the grand winner!\n";
        } else if (player2.getPoints() > player1.getPoints()) {
            std::cout << player2.getName() << " is the grand winner!\n";
        } else {
            std::cout << "It's a tie!\n";
        }
    }
};

int main() {
    ChoHan myGame(5); // Create a game with 5 rounds 
    myGame.start(); // Start the game 
    return 0;
}