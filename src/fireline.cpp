#include "fireline.h"
#include "main.h"

Fireline::Fireline(float x, float y, int angle, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = angle;
    this->radius = 0.03f;
    this->state = 1;

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data1[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data1[k++]= 0.0f;
        vertex_buffer_data1[k++]= 0.0f;
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= (0.03*cos(2*M_PI/n*i));
        vertex_buffer_data1[k++]= (0.03*sin(2*M_PI/n*i));
        vertex_buffer_data1[k++]= 0.0f;

        vertex_buffer_data1[k++]= (0.03*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= (0.03*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data1[k++]= 0.0f;
    }

    static const GLfloat vertex_buffer_data2[] = {
        0.0f,-0.01f,0.0f, // triangle 1 : begin
        0.3f,-0.01f, 0.0f,
        0.3f,0.01f, 0.0f, // triangle 1 : end
        0.3f,0.01f,0.0f, // triangle 2 : begin
        0.0f,0.01f,0.0f,
        0.0f,-0.01f,0.0f, // triangle 2 : end
    };

    k=0;
    GLfloat vertex_buffer_data3[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data3[k++]= 0.3f;
        vertex_buffer_data3[k++]= 0.0f;
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= 0.3f+(0.03*cos(2*M_PI/n*i));
        vertex_buffer_data3[k++]= (0.03*sin(2*M_PI/n*i));
        vertex_buffer_data3[k++]= 0.0f;

        vertex_buffer_data3[k++]= 0.3f+(0.03*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= (0.03*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data3[k++]= 0.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data1, color, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_ORANGE, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data3, color, GL_FILL);
}

void Fireline::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if(this->state)
        draw3DObject(this->object2);
    draw3DObject(this->object1);
    draw3DObject(this->object3);
}

void Fireline::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireline::move() {
    this->position.x -= 0.01f;
}

void Fireline::tick() {
    this->position.x-= 0.01f;
}