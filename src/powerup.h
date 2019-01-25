#include "main.h"

#ifndef POWERUP_H
#define POWERUP_H


class Powerup {
public:
    Powerup() {}
    Powerup(float x, float y, bool type);
    glm::vec3 position;
    bool type;
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

#endif // POWERUP_H
