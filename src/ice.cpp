#include "ice.h"
#include "main.h"

#include <iostream>
using namespace std;

Ice::Ice(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.02f;
    this->speed = -0.03f;
    
    color_t color = COLOR_BLUE;

    int k=0;
    int n=4;
    GLfloat vertex_buffer_data[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;
    }
    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Ice::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ice::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ice::move() {
    this->position.x -= 0.01f;
}

void Ice::tick() {
    this->position.x -= 0.015f;
}