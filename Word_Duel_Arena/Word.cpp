#include "Word.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <random>

// Word bazna klasa
Word::Word(const std::string& word) : secretWord(word) {
    // Pretvori rijec u velika slova
    std::transform(secretWord.begin(), secretWord.end(), secretWord.begin(), ::toupper);
    initializeDisplayWord();
}

void Word::initializeDisplayWord() {
    displayWord = "";
    for (char c : secretWord) {
        if (std::isalpha(c)) {
            displayWord += '_';
        }
        else {
            displayWord += c; // Razmaci i interpunkcija ostaju vidljivi
        }
    }
}

bool Word::guessLetter(char letter) {
    letter = std::toupper(letter);

    // Provjeri je li slovo vec pogodeno
    if (guessedLetters.find(letter) != guessedLetters.end()) {
        return false;
    }

    guessedLetters.insert(letter);

    // Provjeri postoji li slovo u rijeci
    bool found = false;
    for (size_t i = 0; i < secretWord.length(); ++i) {
        if (secretWord[i] == letter) {
            displayWord[i] = letter;
            found = true;
        }
    }

    return found;
}

bool Word::guessWord(const std::string& guess) {
    std::string upperGuess = guess;
    std::transform(upperGuess.begin(), upperGuess.end(), upperGuess.begin(), ::toupper);

    if (upperGuess == secretWord) {
        displayWord = secretWord;
        return true;
    }
    return false;
}

void Word::revealLetter() {
    // Pronadi nasumicno nepokazano slovo i otkrij ga
    std::vector<size_t> hiddenIndices;
    for (size_t i = 0; i < displayWord.length(); ++i) {
        if (displayWord[i] == '_') {
            hiddenIndices.push_back(i);
        }
    }

    if (!hiddenIndices.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, static_cast<int>(hiddenIndices.size()) - 1);
        size_t index = hiddenIndices[dis(gen)];

        char letter = secretWord[index];
        guessedLetters.insert(letter);

        // Otkrij sva pojavljivanja tog slova
        for (size_t i = 0; i < secretWord.length(); ++i) {
            if (secretWord[i] == letter) {
                displayWord[i] = letter;
            }
        }
    }
}

bool Word::isComplete() const {
    return displayWord.find('_') == std::string::npos;
}

int Word::getRemainingLetters() const {
    return static_cast<int>(std::count(displayWord.begin(), displayWord.end(), '_'));
}

void Word::display() const {
    std::cout << "  ";
    for (char c : displayWord) {
        std::cout << c << " ";
    }
    std::cout << "\n";
}

// NormalWord
NormalWord::NormalWord(const std::string& word) : Word(word) {}

// EncryptedWord - ROT13 sifriranje za prikaz
EncryptedWord::EncryptedWord(const std::string& word) : Word(word) {}

char EncryptedWord::encryptChar(char c) const {
    if (c >= 'A' && c <= 'Z') {
        return ((c - 'A' + 13) % 26) + 'A';
    }
    return c;
}

void EncryptedWord::display() const {
    std::cout << "  [ENCRYPTED] ";
    for (char c : displayWord) {
        if (c == '_') {
            std::cout << "? ";
        }
        else if (std::isalpha(c)) {
            std::cout << encryptChar(c) << " ";
        }
        else {
            std::cout << c << " ";
        }
    }
    std::cout << "\n";
}

// BonusWord
BonusWord::BonusWord(const std::string& word, int multiplier)
    : Word(word), bonusMultiplier(multiplier) {
}