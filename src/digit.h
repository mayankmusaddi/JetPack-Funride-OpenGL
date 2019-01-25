#include "main.h"

#ifndef DIGIT_H
#define DIGIT_H


class Digit {
public:
    Digit() {}
    Digit(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;
    VAO *object7;
};

#endif // DIGIT_H
