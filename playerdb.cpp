// playerdb.cpp
// Implementation file for player database, a hashtable implementation.
// Most of the functionality is actually handled by the hashtable itself.
// This is mostly a wrapper class to fit output requirements.

#include "PlayerDB.h"

void PlayerDB::PrintDiagnostics() {
    _os << "====================\n\n";
    _os << "Table Size: " << _hash.getTableSize() << "\n";
    _os << "Number of Entries: " << _hash.getEntries() << "\n";
    _os << _hash;
    _os << "====================\n";
}

Player* PlayerDB::FetchPlayer(const char* name) {
    Player* fetchedPlayer = _hash.fetchPlayer(name);

    _os << "Fetching player \"" << name << "\" -- ";

    if(fetchedPlayer) {
        _os << "Success!\n";
    }

    else {
        _os << "Failed.\n";
    }

    return fetchedPlayer;
}

void PlayerDB::AddPlayer(const Player& newPlayer) {
    _os << "Attempting to add player \"" << newPlayer.getName() <<
          "\" to the database -- ";
    if(_hash.addPlayer(newPlayer)) {
        _os << "Success!\n";
    }

    else {
        _os << "Failed.\n";
    }

    return;
}

void PlayerDB::RemovePlayer(const char* name) {
    _os << "Removing player \"" << name << "\" from the database -- ";

    if(_hash.removePlayer(name)) {
        _os << "Success!\n";
    }

    else {
        _os << "Failed.\n";
    }

    return;
}
