#include "main.h"

#ifndef FIREBEAM_H
#define FIREBEAM_H


class Firebeam {
public:
    Firebeam() {}
    Firebeam(float x, float y, bool direction,color_t color);
    glm::vec3 position;
    float rotation;
    float radius;
    bool state;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double spawnTime;
    bool direction;
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
};

#endif // FIREBEAM_H
