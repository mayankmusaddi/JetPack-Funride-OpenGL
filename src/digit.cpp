#include "digit.h"
#include "main.h"

Digit::Digit(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    static const GLfloat vertex_buffer_data1[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        0.0f,0.01f, 0.0f,
        0.05f,0.01f, 0.0f, // triangle 1 : end
        0.05f,0.01f,0.0f, // triangle 2 : begin
        0.05f,0.0f,0.0f,
        0.0f,0.0f,0.0f, // triangle 2 : end
    };

    

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    // this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    // this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data3, color, GL_FILL);
}

void Digit::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
}

void Digit::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Digit::tick() {
}