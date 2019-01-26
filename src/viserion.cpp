#include "viserion.h"
#include "main.h"
#include "water.h"

Viserion::Viserion(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.1f;
    this->width = 0.1f;
    this->height = 0.1f;
    this->spawntime = tm;

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data[100000];
    for(int i=0;i<n/3;i++)
    {
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= 0.8*(this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.8*(this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;
    }

    k=0;
    GLfloat vertex_buffer_data1[100000];
    for(int i=n/3;i<n;i++)
    {
        vertex_buffer_data1[k++]= 0.01f+0.0f;
        vertex_buffer_data1[k++]= 0.01f+0.0f;
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= 0.01f+0.7*(this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data1[k++]= 0.01f+0.7*(this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= 0.01f+0.7*(this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= 0.01f+0.7*(this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= 0.0f;
    }

    static const GLfloat vertex_buffer_data2[] = {
        0.08f,0.0f,0.0f, // triangle 1 : begin
        0.12f,-0.1f, 0.0f,
        0.04f,-0.04f, 0.0f, // triangle 1 : end
    };

    static const GLfloat vertex_buffer_data3[] = {
        0.0f,0.03f,0.0f, // triangle 1 : begin
        -0.13f,0.08f, 0.0f,
        -0.05f,0.1f, 0.0f, // triangle 1 : end
    };

    static const GLfloat vertex_buffer_data4[] = {
        -0.045f,0.08f,0.0f, // triangle 1 : begin
        -0.07f,0.09f, 0.0f,
        -0.055f,0.095f, 0.0f, // triangle 1 : end
    };

    this->object = create3DObject(GL_TRIANGLES, n, vertex_buffer_data, COLOR_GREEN, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, 2.5*n, vertex_buffer_data1, COLOR_GREEN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_GREEN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data3, COLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, COLOR_BLACK, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::move() {
    this->position.x -= 0.01f;
}

void Viserion::tick() {
    this->position.x -= 0.002f;
    if(this->position.y < ground)
        this->position.y = ground;
}