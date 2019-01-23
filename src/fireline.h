#include "main.h"

#ifndef FIRELINE_H
#define FIRELINE_H


class Fireline {
public:
    Fireline() {}
    Fireline(float x, float y, int angle, color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // FIRELINE_H
