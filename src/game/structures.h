#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <string>
#include <vector>
#include <tuple>

using namespace std;

namespace JupThrGlobal { // NAMESPACE JupThrGlobal
    typedef std::string Script;

    struct Value;
    struct Pos {
        int x;
        int y;

        bool is(Pos &p) {return this->x==p.x && this->y==p.y;}
    };

    struct Location;
    struct LocationEvents;
    struct WorldObject;
} // END JupThrGlobal

namespace JupThrGlobal::LocationEvent { // NAMESPACE JupThrGlobal::LocationEvent
    struct OnLoad {
        bool exist;
        Script script;
    };
    struct PlayerPos {
        bool exist;
        vector<Pos> postitions;
        vector<Script> scripts;

        Script match(Pos pos) {
            for (int i = 0; i < this->scripts.size(); i++) {
                if (pos.is(this->postitions[i])) {
                    return this->scripts[i];
                }
            };
            return "";
        }
    };
} // END JupThrGlobal::LocationEvent

struct JupThrGlobal::Value {
    bool isScript;
    string content;
};

struct JupThrGlobal::LocationEvents {
    LocationEvent::OnLoad onLoad;
    LocationEvent::PlayerPos playerPos;
};

struct JupThrGlobal::Location {
    Value name;
    string id;

    LocationEvents events;

    vector<string> layout;
    vector<tuple<string, string>> flags;
    vector<Script> scripts;

    vector<WorldObject> objects;
};

struct JupThrGlobal::WorldObject {
    Value name;
    Value character;
    string id;

    Pos position;

    Value description;
    Script use;

    // properties
    bool isWalkable;
    bool isTransition;
    int useRange;
};


#endif // STRUCTURES_H
