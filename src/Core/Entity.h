#ifndef WABBLE_ENTITY_H
#define WABBLE_ENTITY_H


#include <memory>

class Entity {
public:
    std::shared_ptr<Entity> parent;

    float X,Y;

};


#endif //WABBLE_ENTITY_H
