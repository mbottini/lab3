// player.cpp
// Implementation file for Player class for PlayerDB class.

#include "Player.h"

Player::Player(const char* name, const GENDER gender, 
               const unsigned int level) {
    int stringLength = strlen(name);

    _name = new char[stringLength + 1];

    if(_name) {
        strncpy(_name, name, stringLength + 1);
        _gender = gender;
        _level = level;
    }

    return;
}

Player::Player(const Player& originalPlayer) {
    _name = NULL;
    *this = originalPlayer;
    return;
}

Player& Player::operator =(const Player& originalPlayer) {
    if(*this != originalPlayer) {
        delete [] _name;
        int stringLength = strlen(originalPlayer.getName());
        _name = new char[stringLength + 1];

        if(_name) {
            strncpy(_name, originalPlayer.getName(), stringLength + 1);
            _gender = originalPlayer.getGender();
            _level = originalPlayer.getLevel();
        }
    }

    return *this;
}

Player::~Player() {
    delete [] _name;
    _gender = UNKNOWN;
    _level = 0;
    return;
}

char* Player::getName() const {
    return _name;
}

GENDER Player::getGender() const {
    return _gender;
}

unsigned int Player::getLevel() const {
    return _level;
}

std::ostream& operator <<(std::ostream& os, const Player& player) {
    os << player.getName() << " [" << player.getLevel() << "]\n";
    return os;
}

bool Player::operator ==(const Player& otherPlayer) {
    // The name pointer is what's important, so we're just going to compare
    // that.
    return _name && otherPlayer.getName() &&
                    strcmp(_name, otherPlayer.getName()) == 0;
}

bool Player::operator ==(const char* name) {
    return strcmp(_name, name) == 0;
}

bool Player::operator !=(const Player& otherPlayer) {
    return !(*this == otherPlayer);
}

void Player::LevelUp() {
    _level++;
    return;
}
