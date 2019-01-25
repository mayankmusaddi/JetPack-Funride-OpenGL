#include "main.h"

#ifndef ICE_H
#define ICE_H


class Ice {
public:
    Ice() {}
    Ice(float x, float y);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move();
    double speed;
private:
    VAO *object;
};

#endif // ICE_H
