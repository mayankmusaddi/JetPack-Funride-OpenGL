#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H


class Health {
public:
    Health() {}
    Health(float x, float y);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // HEALTH_H
