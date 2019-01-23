#include "wall.h"
#include "main.h"

Wall::Wall(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    static const GLfloat vertex_buffer_data[] = {
        0.05f, 0.05f, 0.0f, // triangle 1 : begin
        0.75f, 0.05f, 0.0f,
        0.05f, 0.85f, 0.0f, // triangle 1 : end
        0.05f, 0.85f, 0.0f, // triangle 2 : begin
        0.75f, 0.85f, 0.0f,
        0.75f, 0.05f, 0.0f, // triangle 2 : end
    };
    static const GLfloat vertex_buffer_data1[] = {
        0.05f, 0.05f, 0.0f, // triangle 1 : begin
        0.15f, 0.05f, 0.0f,
        0.05f, 0.15f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.75f, 0.05f, 0.0f, // triangle 1 : begin
        0.65f, 0.05f, 0.0f,
        0.75f, 0.15f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data3[] = {
        0.05f, 0.85f, 0.0f, // triangle 1 : begin
        0.05f, 0.75f, 0.0f,
        0.15f, 0.85f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data4[] = {
        0.75f, 0.85f, 0.0f, // triangle 1 : begin
        0.65f, 0.85f, 0.0f,
        0.75f, 0.75f, 0.0f, // triangle 1 : end
    };

    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data1, COLOR_LIGHTGRAY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data2, COLOR_LIGHTGRAY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data3, COLOR_LIGHTGRAY, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data4, COLOR_LIGHTGRAY, GL_FILL);
}

void Wall::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -3, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Wall::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Wall::move() {
    this->position.x -= 0.01f;
}

void Wall::tick() {
    if(this->position.x < -0.8f)
        this->position.x+=2.4f;
    this->position.x-=0.01f;
}

