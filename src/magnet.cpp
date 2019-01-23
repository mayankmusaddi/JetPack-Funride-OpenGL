#include "magnet.h"
#include "main.h"
#include "ball.h"

Magnet::Magnet(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;

    static const GLfloat vertex_buffer_data1[] = {
        0.02f,0.0f,0.0f, // triagle 1 : begin
        0.02f,-0.05f, 0.0f,
        0.05f,-0.05f, 0.0f, // triangle 1 : end
        0.05f,-0.05f, 0.0f,
        0.05f,0.0f,0.0f, 
        0.02f,0.0f,0.0f
    };

    static const GLfloat vertex_buffer_data2[] = {
        -0.02f,0.0f,0.0f, // triagle 1 : begin
        -0.02f,-0.05f, 0.0f,
        -0.05f,-0.05f, 0.0f, // triangle 1 : end
        -0.05f,-0.05f, 0.0f,
        -0.05f,0.0f,0.0f, 
        -0.02f,0.0f,0.0f
    };

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data3[100000];
    for(int i=0;i<n/2;i++)
    {
        vertex_buffer_data3[k++]= (0.02*cos(2*M_PI/n*i));
        vertex_buffer_data3[k++]= (0.02*sin(2*M_PI/n*i));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= (0.02*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= (0.02*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= (0.05*cos(2*M_PI/n*i));
        vertex_buffer_data3[k++]= (0.05*sin(2*M_PI/n*i));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= (0.05*cos(2*M_PI/n*i));
        vertex_buffer_data3[k++]= (0.05*sin(2*M_PI/n*i));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= (0.05*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= (0.05*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= (0.02*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= (0.02*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= 0.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, color, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data3, color, GL_FILL);
}

void Magnet::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
}

void Magnet::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Magnet::move() {
    this->position.x -= 0.01f;
}

void Magnet::tick() {
    this->position.x-= 0.01f;
}