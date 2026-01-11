#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Word.h"
#include <vector>
#include <memory>
#include <string>

class Game {
private:
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::string> wordList;
    int currentPlayerIndex;
    int totalRounds;
    int currentRound;
    std::shared_ptr<Word> currentWord;

    // Power-up efekti
    int scoreMultiplier;
    bool shieldActive;
    bool extraTurnGranted;

    // Privatne helper metode
    void initializeWordList();
    std::shared_ptr<Word> selectRandomWord();
    void distributePowerUps();
    void nextPlayer();
    bool handlePlayerTurn(std::shared_ptr<Player> player);
    void displayGameStatus() const;
    void displayRoundStart() const;
    void displayRoundEnd() const;

public:
    Game(int rounds = 3);
    ~Game() = default;

    // Inicijalizacija
    void addPlayer(std::shared_ptr<Player> player);
    void initialize();

    // Glavna petlja igre
    void start();
    void playRound();

    // Zavrsetak igre
    void displayFinalResults() const;
    void saveResults(const std::string& filename) const;

    // Power-up efekti
    void setScoreMultiplier(int multiplier) { scoreMultiplier = multiplier; }
    void activateShield() { shieldActive = true; }
    void grantExtraTurn() { extraTurnGranted = true; }
    void resetPowerUpEffects();

    // Getteri
    int getCurrentRound() const { return currentRound; }
    int getTotalRounds() const { return totalRounds; }
};

#endif