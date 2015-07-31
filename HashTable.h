// playerhash.h
// Header file for hashtable class, used in PlayerDB.

#ifndef PLAYERHASH_H
#define PLAYERHASH_H
#include "Player.h"
#include <iostream>
#include "ctype.h"

class playerNode {
    private:
        Player _player;
        playerNode* _next;

    public:
        playerNode();
        playerNode(const Player& newPlayer);
        playerNode(const playerNode& originalNode);
        playerNode& operator =(const playerNode& originalNode);
        
        const Player& getPlayer() const;
        Player* getPlayerPtr();
        playerNode* getNext() const;

        void setPlayer(const Player& newPlayer);
        void setNext(playerNode* newNode);
        bool operator ==(const char* name);
        bool operator !=(const char* name);
};

class playerList {
    private:
        playerNode* _head;

    public:
        playerList();
        playerList(const playerList& originalList);
        playerList& operator =(const playerList& originalList);

        void chainDelete();
        ~playerList();

        playerNode* getHead() const;
        playerNode* findPlayer(const char* name);
        bool addPlayer(const Player& newPlayer);
        bool removePlayer(const char* name);

        friend std::ostream& operator <<(std::ostream& os, 
                                         const playerList& list);
};

class playerHash {
    private:
        playerList *_hashTable;
        int _tableSize;
        int _entries;
        unsigned int getHash(const char* name);

    public:
        playerHash(unsigned int tableSize = 3);
        playerHash(const playerHash& originalHash);
        playerHash& operator =(const playerHash& originalHash);
        void chainDelete();
        ~playerHash();

        playerList* getTable() const;
        int getTableSize() const;
        int getEntries() const;
        Player* fetchPlayer(const char* name);
        bool addPlayer(const Player& newPlayer);
        bool removePlayer(const char* name);

        bool operator ==(const playerHash& otherHash);
        bool operator !=(const playerHash& otherHash);
        playerList& operator [](unsigned int index) const;
        friend std::ostream& operator <<(std::ostream& os, 
                                         const playerHash& hash);
};

void getInts(int* intArray, const char* str);
#endif
