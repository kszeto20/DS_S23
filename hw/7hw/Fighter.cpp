#include "Fighter.h"

using std::string; using std::map; using std::pair; using std::cout; using std::endl;

int Fighter::getMoveFrame(const string move_name) const {
    map<string, int>::const_iterator at = move_frames.find(move_name);
    if (at != move_frames.end()) {
        return at->second;
    }
    return -1;
}

void Fighter::setNewMove(const string move_name, int frames) {
    move_frames.insert(std::make_pair(move_name, frames));
}
