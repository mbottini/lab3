// playerdb.h
// Header file for player database, a hashtable implementation.

#ifndef PLAYERDB_H
#define PLAYERDB_H
#include "HashTable.h"
#include <iostream>

class PlayerDB {
    private:
        playerHash _hash;
        std::ostream &_os;

    public:
        PlayerDB(std::ostream& os) : _os(os) {}
        void PrintDiagnostics();
        Player* FetchPlayer(const char* name);
        void AddPlayer(const Player& newPlayer);
        void RemovePlayer(const char* name);
};
#endif
