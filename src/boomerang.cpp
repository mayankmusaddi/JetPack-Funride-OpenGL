#include "boomerang.h"
#include "main.h"

#include <iostream>
using namespace std;

Boomerang::Boomerang(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.02f;
    this->spawnTime=tm;
    this->direction = 0;

    int k=0;
    int n=30;
    GLfloat vertex_buffer_data[100000];
    for(int i=-n/3;i<n/3;i++)
    {
        vertex_buffer_data[k++]= this->radius*(1 - tan(M_PI/n*i)*tan(M_PI/n*i));
        vertex_buffer_data[k++]= this->radius*(2.0*tan(M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= this->radius/2*(1 - tan(M_PI/n*i)*tan(M_PI/n*i));
        vertex_buffer_data[k++]= this->radius/2*(2.0*tan(M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= this->radius*(1 - tan(M_PI/n*(i+1) )*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= this->radius*(2.0*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= this->radius*(1 - tan(M_PI/n*(i+1) )*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= this->radius*(2.0*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= this->radius/2*(1 - tan(M_PI/n*(i+1) )*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= this->radius/2*(2.0*tan(M_PI/n*(i+1) ));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= this->radius/2*(1 - tan(M_PI/n*i)*tan(M_PI/n*i));
        vertex_buffer_data[k++]= this->radius/2*(2.0*tan(M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;
    }

    k=0;
    GLfloat vertex_buffer_data1[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data1[k++]= 0.0f;
        vertex_buffer_data1[k++]= 0.0f;
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= (this->radius*cos(2*M_PI/n*i));
        vertex_buffer_data1[k++]= (this->radius*sin(2*M_PI/n*i));
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= (this->radius*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= (this->radius*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= 0.0f;
    }

    static const GLfloat vertex_buffer_data2[] = {
        this->radius,-0.06f,0.0f, // triangle 1 : begin
        this->radius,0.06f, 0.0f,
        -2*this->radius,-0.06f, 0.0f, // triangle 1 : end
        -2*this->radius,-0.06f,0.0f, // triangle 2 : begin
        -2*this->radius,0.06f,0.0f,
        this->radius,0.06f,0.0f, // triangle 2 : end
    };

    this->object = create3DObject(GL_TRIANGLES, n*6, vertex_buffer_data, color, GL_FILL);
    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_YELLOW, GL_FILL);
}

void Boomerang::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object2);
    draw3DObject(this->object);
    // draw3DObject(this->object1);
}

void Boomerang::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boomerang::tick() {
    this->rotation+=5;

    if(this->position.x>=0.43 && this->position.y >=0.5)
        this->position.x-=0.01;
    if(this->position.x >=0.43 && this->position.y <0.5)
        this->position.x+=0.01;
    if(this->position.x<0.43)
    {
        this->position.y-=0.008;
        this->position.x= -sqrt((0.3*0.3 - (this->position.y-0.5)*(this->position.y-0.5))) + 0.5;
    }
}