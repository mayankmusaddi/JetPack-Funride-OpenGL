#include "ring.h"
#include "main.h"

Ring::Ring(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.3f;

    int k=0;
    int n=40;
    GLfloat vertex_buffer_data[100000];
    for(int i=-n/2;i<0;i++)
    {
        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= ((this->radius+0.02)*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= ((this->radius+0.02)*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= ((this->radius+0.02)*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= ((this->radius+0.02)*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= ((this->radius+0.02)*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= ((this->radius+0.02)*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data, color, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ring::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ring::move() {
    this->position.x -= 0.01f;
}

void Ring::tick() {
    this->position.x-= 0.01f;
}