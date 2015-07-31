// playerhash.cpp
// Implementation file for hashtable class, used in PlayerDB.

#include "HashTable.h"

playerNode::playerNode() {
    _next = NULL;
    return;
}

playerNode::playerNode(const Player& newPlayer) {
    _player = newPlayer;
    _next = NULL;
    return;
}

playerNode::playerNode(const playerNode& originalNode) {
    *this = originalNode;
    return;    
}

playerNode& playerNode::operator =(const playerNode& originalNode) {
    _player = originalNode.getPlayer();
    _next = NULL;
    return *this;
}

const Player& playerNode::getPlayer() const {
    return _player;
}

Player* playerNode::getPlayerPtr() {
    return &_player;
}

playerNode* playerNode::getNext() const {
    return _next;
}

void playerNode::setPlayer(const Player& newPlayer) {
    _player = newPlayer;
    return;
}

void playerNode::setNext(playerNode* newNode) {
    _next = newNode;
    return;
}

bool playerNode::operator ==(const char* name) {
    return _player == name;
}

bool playerNode::operator !=(const char* name) {
    return _player != name;
}

playerList::playerList() {
    _head = NULL;
    return;
}

playerList::playerList(const playerList& originalList) {
    _head = NULL;
    *this = originalList;
    return;
}

playerList& playerList::operator =(const playerList& originalList) {
    if(_head != originalList.getHead()) {
        chainDelete();
        playerNode *currentNode;
        playerNode *otherNode = originalList.getHead();
        playerNode *tempNode = NULL;

        while(otherNode) {
            currentNode = new playerNode;

            if(currentNode) {
                *currentNode = *otherNode;
            }

            if(_head == NULL) {
                _head = currentNode;
            }

            if(tempNode) {
                tempNode->setNext(currentNode);
            }

            tempNode = currentNode;
            otherNode = otherNode->getNext();
        }
    }

    return *this;
}

void playerList::chainDelete() {
    playerNode* currentNode = _head;
    playerNode* tempNode;

    while(currentNode) {
        tempNode = currentNode;
        currentNode = currentNode->getNext();
        delete tempNode;
    }

    _head = NULL;
    return;
}

playerList::~playerList() {
    chainDelete();
    return;
}
playerNode* playerList::getHead() const {
    return _head;
}

playerNode* playerList::findPlayer(const char* name) {
    playerNode* currentNode = _head;
    playerNode* returnNode = NULL;

    while(currentNode && !(returnNode)) {
        if(*currentNode == name) {
            returnNode = currentNode;
        }
        currentNode = currentNode->getNext();
    }

    return returnNode;
}

bool playerList::addPlayer(const Player& newPlayer) {
    playerNode *currentNode = _head;
    bool foundPlayer = false;
    bool memoryFailure = false;

    if(!(findPlayer(newPlayer.getName()))) { // findPlayer returns NULL if 
                                             // not found
       playerNode *newNode = new playerNode;
       if(newNode) {
           newNode->setPlayer(newPlayer);
           newNode->setNext(_head);
           _head = newNode;
       }

       else { 
           memoryFailure = true;
       }
    }

    else {
        foundPlayer = true;
    }

    return !(foundPlayer) || memoryFailure;
}

bool playerList::removePlayer(const char* name) {
    bool foundPlayer = false;
    playerNode* currentNode = _head;
    playerNode* prevNode = NULL;

    // Can't use "findPlayer" here because we need the previous node.
    while(currentNode && !(foundPlayer)) {
        if(*currentNode == name) {
            foundPlayer = true;
            if(prevNode) {
                prevNode->setNext(currentNode->getNext());
            }

            else {
                _head = _head->getNext();
            }

            delete currentNode;
        }

        else {
            prevNode = currentNode;
            currentNode = currentNode->getNext();
        }
    }

    return foundPlayer;
}

std::ostream& operator <<(std::ostream& os, const playerList& list) {
    playerNode* currentNode = list.getHead();

    if(!(currentNode)) {
        os << "  EMPTY\n";
    }

    while(currentNode) {
        os << "  " << currentNode->getPlayer();
        currentNode = currentNode->getNext();
    }

    return os;
}

unsigned int playerHash::getHash(const char* name) {
    int strSize = strlen(name);
    int sum = 0;
    int *hashInput = new int[strSize + 1];

    if(hashInput) {
        getInts(hashInput, name);

        for(int i = 0; i < strSize; i++) {
            sum *= 32;
            sum += (hashInput[i]);
            sum %= _tableSize;
        }
        delete [] hashInput;
    }

    return sum;
}

playerHash::playerHash(unsigned int tableSize) {
    _hashTable = new playerList[tableSize];

    if(_hashTable) {
        _tableSize = tableSize;
    }

    else {
        _tableSize = 0;
    }
    _entries = 0;

    return;
}

playerHash::playerHash(const playerHash& originalHash) {
    _hashTable = NULL;
    *this = originalHash;
    return;
}

playerHash& playerHash::operator =(const playerHash& originalHash) {
    if(*this != originalHash) {
        chainDelete();
        _hashTable = new playerList[originalHash.getTableSize()];

        if(_hashTable) {
            _tableSize = originalHash.getTableSize();

            for(int i = 0; i < _tableSize; i++) {
                _hashTable[i] = originalHash[i];
            }
        }
    }

    return *this;
}

void playerHash::chainDelete() {
    delete [] _hashTable;
    return;
}

playerHash::~playerHash() {
    chainDelete();
    return;
}

playerList* playerHash::getTable() const {
    return _hashTable;
}

int playerHash::getTableSize() const {
    return _tableSize;
}

int playerHash::getEntries() const {
    return _entries;
}

Player* playerHash::fetchPlayer(const char* name) {
    Player *foundPlayer = NULL;
    playerNode *foundPlayerNode = NULL;
    unsigned int index = getHash(name);

    foundPlayerNode = _hashTable[index].findPlayer(name);

    if(foundPlayerNode) {
        foundPlayer = foundPlayerNode->getPlayerPtr();
    }

    return foundPlayer;
}

bool playerHash::addPlayer(const Player& newPlayer) {
    bool foundPlayer = false;
    unsigned int index = getHash(newPlayer.getName());
    if(_hashTable[index].addPlayer(newPlayer)) {
        foundPlayer = true;
        _entries++;
    }

    return foundPlayer;
}

bool playerHash::removePlayer(const char* name) {
    bool foundPlayer = false;
    unsigned int index = getHash(name);
    if(_hashTable[index].removePlayer(name)) {
        foundPlayer = true;
        _entries--;
    }

    return foundPlayer;
}

bool playerHash::operator ==(const playerHash& otherHash) {
    return _hashTable == otherHash.getTable();
}

bool playerHash::operator !=(const playerHash& otherHash) {
    return _hashTable != otherHash.getTable();
}

playerList& playerHash::operator [](unsigned int index) const {
    return _hashTable[index];
}

std::ostream& operator <<(std::ostream& os, const playerHash& hash) {
    for(int i = 0; i < hash.getTableSize(); i++) {
        os << "Slot[" << i << "]:\n";
        os << hash[i];
    }

    return os;
}

void getInts(int* intArray, const char* str) {
    for(int i = 0; str[i]; i++) {
        if(!isalpha(str[i])) { // All non-alpha characters treated as 0 in hash.
            intArray[i] = 0;
        }
        else if(int(str[i]) < 91) { // If uppercase,
            intArray[i] = int(str[i]) - 65;
        }

        else {
            intArray[i] = int(str[i]) - 97;
        }

        intArray[i] = int(str[i]);
    }

    return;
}
