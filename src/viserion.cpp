#include "viserion.h"
#include "main.h"
#include "water.h"

Viserion::Viserion(float x, float y) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->width = 0.1f;
    this->height = 0.1f;
    this->spawntime = tm;

    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data1[] = {
        0.0f,0.0f,0.0f, // triangle 1 : begin
        0.0f,0.08f, 0.0f,
        0.04f,0.08f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data2[] = {
        0.005f,0.01f,0.0f, // triangle 1 : begin
        0.035f,0.07f, 0.0f,
        0.035f,0.01f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data6[] = {
        0.007f,0.01f,0.0f, // triangle 1 : begin
        0.033f,0.01f, 0.0f,
        0.020f,-0.02f,0.0f,
    };
    static const GLfloat vertex_buffer_data3[] = {
        0.04f,0.0f,0.0f, // triangle 1 : begin
        0.04f,0.1f, 0.0f,
        0.1f,0.0f, 0.0f, // triangle 1 : end
        0.1f,0.0f,0.0f, // triangle 2 : begin
        0.1f,0.1f,0.0f,
        0.04f,0.1f,0.0f, // triangle 2 : end
    };
    static const GLfloat vertex_buffer_data4[] = {
        0.04f,0.1f,0.0f, // triangle 1 : begin
        0.1f,0.1f, 0.0f,
        0.1f,0.07f, 0.0f, // triangle 1 : end
    };
    static const GLfloat vertex_buffer_data5[] = {
        0.08f,0.095f,0.0f, // triangle 1 : begin
        0.09f,0.095f, 0.0f,
        0.09f,0.085f, 0.0f, // triangle 1 : end
    };

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data7[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data7[k++]= 0.05+(0.1*cos(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.05+(0.1*sin(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.0f;

        vertex_buffer_data7[k++]= 0.05+(0.1*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.05+(0.1*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.0f;

        vertex_buffer_data7[k++]= 0.05+(0.12*cos(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.05+(0.12*sin(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.0f;

        vertex_buffer_data7[k++]= 0.05+(0.12*cos(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.05+(0.12*sin(2*M_PI/n*i));
        vertex_buffer_data7[k++]= 0.0f;

        vertex_buffer_data7[k++]= 0.05+(0.12*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.05+(0.12*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.0f;

        vertex_buffer_data7[k++]= 0.05+(0.1*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.05+(0.1*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data7[k++]= 0.0f;
    }

    this->object1 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data1, COLOR_GRAY, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data2, COLOR_DARKGRAY, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_LIGHTBLUE, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data4, COLOR_LIGHTGREEN, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 3, vertex_buffer_data5, COLOR_BLACK, GL_FILL);
    this->object6 = create3DObject(GL_TRIANGLES, 1*3, vertex_buffer_data6, COLOR_ORANGE, GL_FILL);
    this->object7 = create3DObject(GL_TRIANGLES, 2*3*n, vertex_buffer_data7, COLOR_DARKGRAY, GL_FILL);
}

void Viserion::draw(glm::mat4 VP) {
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
    draw3DObject(this->object4);
    draw3DObject(this->object5);
    draw3DObject(this->object6);
}

void Viserion::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Viserion::move() {
    this->position.x -= 0.01f;
}

void Viserion::hit() {
    Water water = Water(0,0);
}

void Viserion::tick() {
    this->position.x -= 0.003f;
    if(this->position.y < ground)
        this->position.y = ground;
}