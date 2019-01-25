#include "coin.h"
#include "main.h"

Coin::Coin(float x, float y,bool type) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->radius = 0.03f;
    this->type = type;
    color_t color;
    
    if(this->type==0)
        color = COLOR_YELLOW;
    else
        color = COLOR_VIOLET;

    int k=0;
    int n=20;
    GLfloat vertex_buffer_data[100000];
    for(int i=0;i<n;i++)
    {
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (0.03*cos(2*M_PI/n*i));
        vertex_buffer_data[k++]= (0.03*sin(2*M_PI/n*i));
        vertex_buffer_data[k++]= 0.0f;

        vertex_buffer_data[k++]= (0.03*cos(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= (0.03*sin(2*M_PI/n*(i+1)));
        vertex_buffer_data[k++]= 0.0f;
    }

    this->object = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
}

void Coin::draw(glm::mat4 VP) {
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

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Coin::move() {
    this->position.x -= 0.01f;
}

void Coin::tick() {
    this->position.x-= 0.01f;
}