#include "main.h"

#ifndef BOOMERANG_H
#define BOOMERANG_H


class Boomerang {
public:
    Boomerang() {}
    Boomerang(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    bool state;
    bool direction;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double spawnTime;
private:
    VAO *object;
    VAO *object1;
};

#endif // BOOMERANG_H
