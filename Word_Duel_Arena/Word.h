#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
#include <set>

// Apstraktna bazna klasa za rijeci
class Word {
protected:
    std::string secretWord;
    std::string displayWord;
    std::set<char> guessedLetters;

    void initializeDisplayWord();

public:
    Word(const std::string& word);
    virtual ~Word() = default;

    // Virtualne metode koje mogu biti prepisane
    virtual bool guessLetter(char letter);
    virtual bool guessWord(const std::string& guess);
    virtual void revealLetter(); // Za power-up

    // Getteri
    std::string getDisplayWord() const { return displayWord; }
    std::string getSecretWord() const { return secretWord; }
    bool isComplete() const;
    int getRemainingLetters() const;

    // Prikaz
    virtual void display() const;
    virtual std::string getType() const = 0;
};

// NormalWord - obicna rijec bez posebnih efekata
class NormalWord : public Word {
public:
    NormalWord(const std::string& word);
    std::string getType() const override { return "Normal"; }
};

// EncryptedWord - rijec s jednostavnom sifrom (ROT13)
class EncryptedWord : public Word {
private:
    std::string encryptedDisplay;
    char encryptChar(char c) const;

public:
    EncryptedWord(const std::string& word);
    void display() const override;
    std::string getType() const override { return "Encrypted"; }
};

// BonusWord - daje dodatne bodove
class BonusWord : public Word {
private:
    int bonusMultiplier;

public:
    BonusWord(const std::string& word, int multiplier = 2);
    int getBonusMultiplier() const { return bonusMultiplier; }
    std::string getType() const override { return "Bonus"; }
};

#endif