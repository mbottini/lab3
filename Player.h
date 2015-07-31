// player.h
// Header file for Player class, which creates a Player object for the
// PlayerDB class.

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <cstring>

enum GENDER {
    UNKNOWN,
    MALE,
    FEMALE
};
    

class Player {
    private:
        char* _name;
        GENDER _gender;
        unsigned int _level;

    public:
        Player(const char* name = "", const GENDER gender = UNKNOWN,
               const unsigned int level = 0);
        Player(const Player& originalPlayer);
        Player& operator =(const Player& originalPlayer);
        ~Player();
        char* getName() const;
        GENDER getGender() const;
        unsigned int getLevel() const;

        friend std::ostream& operator <<(std::ostream& os, 
                                         const Player& player);
        bool operator ==(const Player& otherPlayer);
        bool operator ==(const char* name);
        bool operator !=(const Player& otherPlayer);
        void LevelUp();
};

#endif


