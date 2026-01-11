#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include <vector>

// Forward declaration
class PowerUp;

// Apstraktna bazna klasa za sve tipove igraca
class Player {
protected:
    std::string name;
    int score;
    std::vector<std::shared_ptr<PowerUp>> powerUps;
    bool powerUpUsedThisRound;

public:
    Player(const std::string& playerName);
    virtual ~Player() = default;

    // Virtualne metode za bodovanje - razliciti tipovi igraca imaju razlicita pravila
    virtual void addPoints(int points) = 0;
    virtual void subtractPoints(int points) = 0;

    // Getteri
    std::string getName() const { return name; }
    int getScore() const { return score; }
    bool hasPowerUpUsed() const { return powerUpUsedThisRound; }

    // Setteri
    void resetPowerUpFlag() { powerUpUsedThisRound = false; }

    // Power-up management
    void addPowerUp(std::shared_ptr<PowerUp> powerUp);
    bool hasPowerUps() const { return !powerUps.empty(); }
    std::shared_ptr<PowerUp> usePowerUp(int index);
    void displayPowerUps() const;
    int getPowerUpCount() const { return static_cast<int>(powerUps.size()); }

    // Prikaz informacija
    virtual void displayInfo() const;
    virtual std::string getType() const = 0;
};

// AggressivePlayer - veci dobitak i veci gubitak bodova
class AggressivePlayer : public Player {
public:
    AggressivePlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Aggressive"; }
};

// DefensivePlayer - manji gubitak bodova
class DefensivePlayer : public Player {
public:
    DefensivePlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Defensive"; }
};

// BalancedPlayer - standardno bodovanje
class BalancedPlayer : public Player {
public:
    BalancedPlayer(const std::string& playerName);

    void addPoints(int points) override;
    void subtractPoints(int points) override;
    std::string getType() const override { return "Balanced"; }
};

#endif