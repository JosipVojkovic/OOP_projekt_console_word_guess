#include "Game.h"
#include "PowerUp.h"
#include <random>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <sstream>

Game::Game(int rounds)
    : currentPlayerIndex(0), totalRounds(rounds), currentRound(0),
    currentWord(nullptr),
    scoreMultiplier(1), shieldActive(false), extraTurnGranted(false) {
    initializeWordList();
}

Game::~Game() {
    for (auto p : players) {
        delete p;
    }
    players.clear();

    delete currentWord;
    currentWord = nullptr;
}

void Game::initializeWordList() {
    std::ifstream file("words.txt");
    std::vector<std::string> loaded;

    auto trim = [](std::string s) {
        while (!s.empty() && std::isspace(s.front()))
            s.erase(s.begin());

        while (!s.empty() && std::isspace(s.back()))
            s.pop_back();

        return s;
    };

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty()) continue;
            if (!line.empty() && line[0] == '#') continue;

            std::transform(line.begin(), line.end(), line.begin(),
                [](unsigned char c) { return static_cast<char>(std::toupper(c)); });
            loaded.push_back(line);
        }
        file.close();
    }

    if (!loaded.empty()) {
        wordList = std::move(loaded);
        return;
    }

    wordList = {
        "PROGRAMIRANJE", "ALGORITAM", "STRUKTURA", "NASLJEDIVANJE",
        "POLIMORFIZAM", "ENKAPSULACIJA", "APSTRAKCIJA", "KONSTRUKTOR",
        "DESTRUKTOR", "POKAZIVAC", "REFERENCA", "LAMBDA", "EXCEPTION",
        "TEMPLATE", "NAMESPACE", "VIRTUALNA", "KOMPAJLIRANJE",
        "DEBUGIRANJE", "TESTIRANJE", "DOKUMENTACIJA", "VERZIONIRANJE"
    };
}

Word* Game::selectRandomWord() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> wordDis(0, static_cast<int>(wordList.size()) - 1);
    std::uniform_int_distribution<> typeDis(0, 1);

    std::string selectedWord = wordList[wordDis(gen)];
    int wordType = typeDis(gen);

    switch (wordType) {
    case 0:
        return new NormalWord(selectedWord);
    case 1:
        return new BonusWord(selectedWord, 2);
    default:
        return new NormalWord(selectedWord);
    }
}

void Game::distributePowerUps() {
    std::vector<std::string> availableNames = {
        "Reveal Letter", "Double Score", "Extra Turn", "Shield"
    };

    std::random_device rd;
    std::mt19937 gen(rd());

    for (auto& player : players) {
        std::shuffle(availableNames.begin(), availableNames.end(), gen);
        std::uniform_int_distribution<int> numDis(1, 2);
        int numPowerUps = numDis(gen);

        for (int i = 0; i < numPowerUps && i < static_cast<int>(availableNames.size()); ++i) {
            PowerUp* powerUp = nullptr;
            const std::string& name = availableNames[i];
            if (name == "Reveal Letter") {
                powerUp = new RevealLetterPowerUp();
            }
            else if (name == "Double Score") {
                powerUp = new DoubleScorePowerUp();
            }
            else if (name == "Extra Turn") {
                powerUp = new ExtraTurnPowerUp();
            }
            else {
                powerUp = new ShieldPowerUp();
            }
            player->addPowerUp(powerUp);
        }
    }
}

void Game::addPlayer(Player* player) {
    players.push_back(player);
}

void Game::initialize() {
    if (players.size() != 3) {
        throw std::runtime_error("Igra zahtijeva tocno 3 igraca!");
    }

    distributePowerUps();
    currentPlayerIndex = 0;
    currentRound = 0;
}

void Game::resetPowerUpEffects() {
    scoreMultiplier = 1;
    shieldActive = false;
    extraTurnGranted = false;
}

void Game::nextPlayer() {
    if (!extraTurnGranted) {
        currentPlayerIndex = (currentPlayerIndex + 1) % static_cast<int>(players.size());
    }
    extraTurnGranted = false;
}