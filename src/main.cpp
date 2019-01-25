#include "main.h"
#include "ball.h"
#include "platform.h"
#include "wall.h"
#include "coin.h"
#include "magnet.h"
#include "fireline.h"
#include "firebeam.h"
#include "powerup.h"
#include "water.h"
#include "boomerang.h"
// Include any new component here
#include <cstdlib> // for rand() function

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

long long dist=0;
long long score=0;
long long life=5;

Timer timer;
Ball ball;
Platform platform;
Wall wall1,wall2,wall3;
vector <Coin> coins;
vector <Magnet> magnets;
vector <Fireline> firelines;
vector <Firebeam> firebeams;
vector <Powerup> powerups;
vector <Water> waters;

Boomerang boomerang;
//Initialize new components globally here

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float gravity = 0.001f;
float ground = 0.1f;
double tm=0; // for time

Timer t60(1.0 / 60);

void draw() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram (programID);
    glm::vec3 eye ( 0, 0, 1 );
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);
    Matrices.view = glm::lookAt( eye, target, up );
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;

    // Scene render
    platform.draw(VP);
    wall1.draw(VP);
    wall2.draw(VP);
    wall3.draw(VP);
    ball.draw(VP);

    for(int i=0;i<(int)(coins).size();i++)
        coins[i].draw(VP);
    for(int i=0;i<(int)(magnets).size();i++)
        magnets[i].draw(VP);
    for(int i=0;i<(int)(firelines).size();i++)
        firelines[i].draw(VP);
    for(int i=0;i<(int)(firebeams).size();i++)
        firebeams[i].draw(VP);
    for(int i=0;i<(int)(powerups).size();i++)
        powerups[i].draw(VP);
    for(int i=0;i<(int)(waters).size();i++)
        waters[i].draw(VP);

    boomerang.draw(VP);
    // Draw new components here
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int up = glfwGetKey(window, GLFW_KEY_UP);

    if (left && ball.position.x > 0) {
        dist-=1;
        ball.move_left();
    }
    if (right) {
        dist+=1;
        if(ball.position.x > 0.45f)
        {
            wall1.move();
            wall2.move();
            wall3.move();
            for(int i=0;i<(int)(coins).size();i++)
                coins[i].move();
            for(int i=0;i<(int)(magnets).size();i++)
                magnets[i].move();
            for(int i=0;i<(int)(firelines).size();i++)
                firelines[i].move();
            for(int i=0;i<(int)(powerups).size();i++)
                powerups[i].move();
            for(int i=0;i<(int)(waters).size();i++)
                waters[i].move();

            // Move the frame components here
        }
        else
            ball.move_right();
    }
    if (space && ball.position.y < 0.9f) {
        ball.move_up();
    }
    if(down) {
        ball.position.y-=0.01f;
    }
    if(up){
        waters.push_back(Water(ball.position.x+ball.width,ball.position.y+ball.height));
    }
}

void die(){
    ball.position.x=0;
    ball.position.y=-0.1f;
    life-=1;
}

void tick_elements() {
    dist+=1;
    if (timer.processTick())
        tm+=0.01;
        
    ball.tick();
    wall1.tick();
    wall2.tick();
    wall3.tick();

    boomerang.tick();

    // Add tick of new Components Here

    bounding_box_t b;
    b.x = ball.position.x+ball.width/2;
    b.y = ball.position.y+ball.height/2;
    b.width = ball.width;
    b.height = ball.height;

    //Waters
    for(int i=0;i<(int)(waters).size();i++)
    {
        waters[i].tick();

        bounding_box_t w;
        w.x = waters[i].position.x;
        w.y = waters[i].position.y;
        w.width = w.height = waters[i].radius*2;

        point_t u,v,p;
        p.x=waters[i].position.x;
        p.y=waters[i].position.y;
        for(int i=0;i<(int)(firelines).size();i++)
        {
            u.x=firelines[i].position.x;
            u.y=firelines[i].position.y;
            v.x= u.x+ 0.3f*cos( firelines[i].rotation * M_PI / 180.0f);
            v.y= u.y+ 0.3f*sin( firelines[i].rotation * M_PI / 180.0f);

            bounding_box_t fl;
            fl.x = (u.x+v.x)/2;
            fl.y = (u.y+v.y)/2;
            fl.width = abs(v.x-u.x);
            fl.height = abs(v.y-u.y);

            if( firelines[i].state && distance(u,v,p) <= waters[i].radius && detect_collision(w,fl))
                firelines[i].state=0;
        }

        for(int i=0;i<(int)(firebeams).size();i++)
        {
            bounding_box_t fb;
            fb.x = firebeams[i].position.x+0.45f;
            fb.y = firebeams[i].position.y;
            fb.width = 0.9f;
            fb.height = 0.06f;

            if( firebeams[i].state && detect_collision(w,fb) )
                firebeams[i].state=0;
        }

        if((waters[i].position.y) <= ground )
            waters.erase(waters.begin()+i);
    }
    
    //Powerups
    if( dist%240 == 0)
       powerups.push_back(Powerup(1.0,0.9,rand()%2));
    for(int i=0;i<(int)(powerups).size();i++)
    {
        powerups[i].tick();

        bounding_box_t p;
        p.x = powerups[i].position.x;
        p.y = powerups[i].position.y;
        p.width = p.height = powerups[i].radius*2;
        if(detect_collision(b,p))
        {
            powerups.erase(powerups.begin()+i);
            if(powerups[i].type == 0)
            {
                life+=1;
                cout << "Life : " << life << " Life Increased\n";
            }
            else
            {
                score+=100;
                cout << "Score : " << score  << " Score Increased\n";
            }
            
        }
        if(powerups[i].position.x < 0)
            powerups.erase(powerups.begin()+i);
    }

    //FireBeam
    if( int(tm*100)%1000 == 0)
       firebeams.push_back(Firebeam(0.05f,0.9f,1,COLOR_DARKGRAY));
    for(int i=0;i<(int)(firebeams).size();i++)
    {
        firebeams[i].tick();

        bounding_box_t fb;
        fb.x = firebeams[i].position.x+0.45f;
        fb.y = firebeams[i].position.y;
        fb.width = 0.9f;
        fb.height = 0.06f;

        if( detect_collision(b,fb) && tm - firebeams[i].spawnTime > 1.5 && firebeams[i].state )
        {
            die();
            cout << "Life : " << life  << " Distance : " << dist << endl;
        }

        if( tm - firebeams[i].spawnTime > 3)
            firebeams.erase(firebeams.begin()+i);
    }

    //Fireline
    if( dist%300 == 0)
       firelines.push_back(Fireline(1.0,(rand()%8+1)/10.0,rand()%90,COLOR_DARKGRAY));
    for(int i=0;i<(int)(firelines).size();i++)
    {
        firelines[i].tick();

        line_segment_t l;
        l.x1=firelines[i].position.x;
        l.y1=firelines[i].position.y;
        l.x2= l.x1+ 0.3f*cos( firelines[i].rotation * M_PI / 180.0f);
        l.y2= l.y1+ 0.3f*sin( firelines[i].rotation * M_PI / 180.0f);

        bounding_box_t fl;
        fl.x = (l.x1+l.x2)/2;
        fl.y = (l.y1+l.y2)/2;
        fl.width = abs(l.x2-l.x1);
        fl.height = abs(l.y2-l.y1);

        if( detect_collision(b,fl) && detect_collision(b,l) && firelines[i].state)
        {
            die();
            cout << "Life : " << life  << " Distance : " << dist << endl;
        }

        if(firelines[i].position.x < -0.3f)
            firelines.erase(firelines.begin()+i);
    }

    //Magnets
    if( dist%500 == 0)
       magnets.push_back(Magnet(1.1,(rand()%8+2)/10.0,COLOR_RED));
    for(int i=0;i<(int)(magnets).size();i++)
    {
        magnets[i].tick();

        if(magnets[i].position.x > ball.position.x+ball.width/2)
            ball.position.x+=0.008f;
        if(magnets[i].position.x < ball.position.x +ball.width/2)
            ball.position.x-=0.008f;
        if(magnets[i].position.y > ball.position.y)
            ball.position.y+=0.008f;
        if(magnets[i].position.y < ball.position.y)
            ball.position.y-=0.008f;

        if(magnets[i].position.x < 0)
            magnets.erase(magnets.begin()+i);
    }

    //Coins
    if( dist%50 == 0)
       coins.push_back(Coin(1.0,(rand()%8+2)/10.0,COLOR_YELLOW));
    for(int i=0;i<(int)(coins).size();i++)
    {
        coins[i].tick();

        bounding_box_t c;
        c.x = coins[i].position.x;
        c.y = coins[i].position.y;
        c.width = c.height = coins[i].radius*2;
        if(detect_collision(b,c))
        {
            coins.erase(coins.begin()+i);
            score+=1;
            cout << "Score : " << score  << " Distance : " << dist << endl;
        }
        if(coins[i].position.x < 0)
            coins.erase(coins.begin()+i);
    }
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    timer = Timer(0.01);
    platform    = Platform(0,0, COLOR_GRAY);
    wall1 = Wall(0,0.1f,COLOR_BLUEGRAY);
    wall2 = Wall(0.8,0.1f,COLOR_BLUEGRAY);
    wall3 = Wall(1.6,0.1f,COLOR_BLUEGRAY);
    ball = Ball(0,0.1f,COLOR_GREEN);

    boomerang = Boomerang(1.0,0.8,COLOR_GREEN);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    reshapeWindow (window, width, height);
    // Background color of the scene
    glClearColor (COLOR_LIGHTGRAY.r / 256.0, COLOR_LIGHTGRAY.g / 256.0, COLOR_LIGHTGRAY.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);
    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }
    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

bool detect_collision(bounding_box_t a, line_segment_t b) { 
    a.x-=a.width/2; a.y-=a.height/2;
    point_t u,v,p1,p2,p3,p4;
    u.x=b.x1;               u.y=b.y1;
    v.x=b.x2;               v.y=b.y2;
    p1.x=a.x;               p1.y=a.y;
    p2.x=a.x+a.width;       p2.y=a.y;
    p3.x=a.x+a.width;       p3.y=a.y+a.height;
    p4.x=a.x;               p4.y=a.y+a.height;
    return (distance(u,v,p1) <= 0.05 || distance(u,v,p2) <= 0.05 || distance(u,v,p3) <= 0.05 || distance(u,v,p4) <= 0.05);
}

float distance(point_t u,point_t v,point_t p) {
    float a = (v.y-u.y);
    float b = (u.x-v.x);
    float num = a*p.x + b*p.y - a*u.x - b*u.y;
    float den = sqrt(a*a+b*b);
    return abs(num/den);
}

void reset_screen() {
    float top    = screen_center_y + 1 / screen_zoom;
    float bottom = screen_center_y - 0 / screen_zoom;
    float left   = screen_center_x - 0 / screen_zoom;
    float right  = screen_center_x + 1 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
