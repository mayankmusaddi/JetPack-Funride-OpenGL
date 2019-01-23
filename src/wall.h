#include "main.h"

#ifndef WALL_H
#define WALL_H


class Wall {
public:
    Wall() {}
    Wall(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void move();
private:
    VAO *object;
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
};

#endif // WALL_H
