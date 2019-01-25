#include "main.h"

#ifndef VISERION_H
#define VISERION_H


class Viserion {
public:
    Viserion() {}
    Viserion(float x, float y);
    glm::vec3 position;
    float rotation;
    float width;
    float height;
    double spawntime;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move();
    void tick();
    void hit();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // VISERION_H
