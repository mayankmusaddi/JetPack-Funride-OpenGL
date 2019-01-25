#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float width;
    float height;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void move_right();
    void move_left();
    void move_up();
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
