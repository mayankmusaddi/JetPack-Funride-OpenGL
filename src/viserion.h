#include "main.h"

#ifndef VISERION_H
#define VISERION_H


class Viserion {
public:
    Viserion() {}
    Viserion(float x, float y);
    glm::vec3 position;
    float rotation;
    float radius;
    float width;
    float height;
    double spawntime;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move();
    void tick();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // VISERION_H
