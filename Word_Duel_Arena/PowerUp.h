#ifndef POWERUP_H
#define POWERUP_H

#include <string>
#include <memory>

// Forward declarations
class Player;
class Word;
class Game;

// Apstraktna bazna klasa za power-upove
class PowerUp {
protected:
    std::string name;
    std::string description;

public:
    PowerUp(const std::string& name, const std::string& desc);
    virtual ~PowerUp() = default;

    virtual void apply(Game* game, Player* player, Word* word) = 0;

    std::string getName() const { return name; }
    std::string getDescription() const { return description; }
};

// RevealLetter - otkriva jedno slovo
class RevealLetterPowerUp : public PowerUp {
public:
    RevealLetterPowerUp();
    void apply(Game* game, Player* player, Word* word) override;
};

// DoubleScore - udvostrucuje bodove sljedeceg poteza
class DoubleScorePowerUp : public PowerUp {
public:
    DoubleScorePowerUp();
    void apply(Game* game, Player* player, Word* word) override;
};

// ExtraTurn - daje dodatni potez
class ExtraTurnPowerUp : public PowerUp {
public:
    ExtraTurnPowerUp();
    void apply(Game* game, Player* player, Word* word) override;
};

// Shield - stiti od gubitka bodova sljedeci potez
class ShieldPowerUp : public PowerUp {
public:
    ShieldPowerUp();
    void apply(Game* game, Player* player, Word* word) override;
};

#endif