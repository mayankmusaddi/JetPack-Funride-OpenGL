#include "health.h"
#include "main.h"

Health::Health(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.01f;

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data1[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data1[k++]= -this->radius;
        vertex_buffer_data1[k++]= 0.0f;
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= -this->radius+(this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data1[k++]= (this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= -this->radius+(this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= 0.0f;
    }

    k=0;
    GLfloat vertex_buffer_data2[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data2[k++]= this->radius;
        vertex_buffer_data2[k++]= 0.0f;
        vertex_buffer_data2[k++]= 0.0f;

        vertex_buffer_data2[k++]= this->radius+(this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data2[k++]= (this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data2[k++]= 0.0f;

        vertex_buffer_data2[k++]= this->radius+(this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data2[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data2[k++]= 0.0f;
    }

    static const GLfloat vertex_buffer_data3[] = {
        2*this->radius,-0.002f, 0.0f,
        0.0f,-3*this->radius, 0.0f, // triangle 1 : end
        -2*this->radius,-0.002f,0.0f, // triangle 2 : begin
    };

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data2, COLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_RED, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object2);
    draw3DObject(this->object1);
    draw3DObject(this->object3);
}

void Health::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Health::tick() {
}