#include <iostream>
#include "glew.h"
#include "glfw3.h"
#include "Angel.h"

typedef vec4 color4;
typedef vec4 point4;

const float FRAME_RATE = 60.0f;
const float colorOffset = 0.02f;
int WIDTH = 720;
int HEIGHT = 720;

const int n = 3;
const int n2 = n * n;
const int n3 = n2 * n;

// points of a cube
point4 points[8]{
    point4(-0.5f, -0.5f, -0.5f, 1.0f),
    point4(-0.5f, -0.5f,  0.5f, 1.0f),
    point4(-0.5f,  0.5f, -0.5f, 1.0f),
    point4(-0.5f,  0.5f,  0.5f, 1.0f),
    point4(0.5f, -0.5f, -0.5f, 1.0f),
    point4(0.5f, -0.5f,  0.5f, 1.0f),
    point4(0.5f,  0.5f, -0.5f, 1.0f),
    point4(0.5f,  0.5f,  0.5f, 1.0f)
};

// RGBA colors
color4 colorTypes[7] = {
    color4(1.0f, 1.0f, 0.0f, 1.0f),  // yellow
    color4(0.2f, 0.2f, 1.0f, 1.0f),  // blue
    color4(1.0f, 0.6f, 0.0f, 1.0f),  // orange
    color4(1.0f, 0.0f, 0.0f, 1.0f),  // red
    color4(0.2f, 1.0f, 0.2f, 1.0f),  // green
    color4(0.8f, 0.8f, 0.8f, 1.0f),  // white
    color4(0.0f, 0.0f, 0.0f, 1.0f)   // black
};

point4 directionPoints[8]{
    point4(-0.5f, -0.5f,  0.0f, 1.0f),
    point4(-0.5f,  0.5f,  0.0f, 1.0f),
    point4(0.5f, -0.5f,  0.0f, 1.0f),
    point4(0.5f,  0.5f,  0.0f, 1.0f),
    point4(-0.7f, -0.7f,  0.0f, 1.0f),
    point4(-0.7f,  0.7f,  0.0f, 1.0f),
    point4(0.7f, -0.7f,  0.0f, 1.0f),
    point4(0.7f,  0.7f,  0.0f, 1.0f)
};

color4 directionColorTypes[6] = {
    color4(0.2f, 0.1f, 0.2f, 1.0f),
    color4(0.2f, 0.2f, 0.2f, 1.0f),
    color4(0.2f, 0.3f, 0.2f, 1.0f),
    color4(0.2f, 0.4f, 0.2f, 1.0f),
    color4(0.2f, 0.5f, 0.2f, 1.0f),
    color4(0.2f, 0.6f, 0.2f, 1.0f)
};

point4 vertices[24];
color4 colors[24];
point4 lvertices[8];
color4 lcolors[8];
point4 dvertices[32];
color4 dcolors[32];

int indices[36];
int lindices[24];
int dindices[48];

float colorIDs[n][n][n][4];
int positions[n][n][n];

//points array and colors array index pointer
int vindex = 0;
int index = 0;
int lindex = 0;
int dindex = 0;
int ColorIndex = 0;

void quad(int a, int b, int c, int d)
{
    vertices[vindex] = points[a];
    vertices[vindex + 1] = points[b];
    vertices[vindex + 2] = points[c];
    vertices[vindex + 3] = points[d];

    colors[vindex] = colorTypes[ColorIndex];
    colors[vindex + 1] = colorTypes[ColorIndex];
    colors[vindex + 2] = colorTypes[ColorIndex];
    colors[vindex + 3] = colorTypes[ColorIndex];

    indices[index++] = vindex;
    indices[index++] = vindex + 1;
    indices[index++] = vindex + 2;
    indices[index++] = vindex + 1;
    indices[index++] = vindex + 2;
    indices[index++] = vindex + 3;

    vindex += 4;
    ColorIndex++;
}

void line(int a, int b, int c, int d, int shift) {
    lindices[lindex++] = vindex + a;
    lindices[lindex++] = vindex + a + shift;
    lindices[lindex++] = vindex + b;
    lindices[lindex++] = vindex + b + shift;
    lindices[lindex++] = vindex + c;
    lindices[lindex++] = vindex + c + shift;
    lindices[lindex++] = vindex + d;
    lindices[lindex++] = vindex + d + shift;
}

void addLines() {
    lvertices[0] = points[0];
    lvertices[1] = points[1];
    lvertices[2] = points[2];
    lvertices[3] = points[3];
    lvertices[4] = points[4];
    lvertices[5] = points[5];
    lvertices[6] = points[6];
    lvertices[7] = points[7];
    lcolors[0] = colorTypes[6];
    lcolors[1] = colorTypes[6];
    lcolors[2] = colorTypes[6];
    lcolors[3] = colorTypes[6];
    lcolors[4] = colorTypes[6];
    lcolors[5] = colorTypes[6];
    lcolors[6] = colorTypes[6];
    lcolors[7] = colorTypes[6];
    line(0, 2, 4, 6, 1);
    line(0, 1, 2, 3, 4);
    line(0, 1, 4, 5, 2);
    vindex += 8;
}

// colorcube: it creates 1 Cube (there will be 27 cubes) and also it creates the black line that covers the lines
void colorcube()
{
    quad(0, 1, 2, 3);
    quad(4, 5, 6, 7);
    quad(0, 1, 4, 5);
    quad(2, 3, 6, 7);
    quad(0, 2, 4, 6);
    quad(1, 3, 5, 7);
    addLines();
}

void initColorIDs() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                colorIDs[i][j][k][0] = (float)i * colorOffset;
                colorIDs[i][j][k][1] = (float)j * colorOffset;
                colorIDs[i][j][k][2] = (float)k * colorOffset;
                colorIDs[i][j][k][3] = 1.0f;
            }
        }
    }
}

void addSquareToDirectionArea(int a, int b, int c, int d, int i) {
    dvertices[i * 4] = directionPoints[a];
    dvertices[i * 4 + 1] = directionPoints[b];
    dvertices[i * 4 + 2] = directionPoints[c];
    dvertices[i * 4 + 3] = directionPoints[d];

    dcolors[i * 4] = directionColorTypes[i % 6];
    dcolors[i * 4 + 1] = directionColorTypes[i % 6];
    dcolors[i * 4 + 2] = directionColorTypes[i % 6];
    dcolors[i * 4 + 3] = directionColorTypes[i % 6];

    dindices[dindex++] = vindex;
    dindices[dindex++] = vindex + 1;
    dindices[dindex++] = vindex + 2;
    dindices[dindex++] = vindex + 1;
    dindices[dindex++] = vindex + 2;
    dindices[dindex++] = vindex + 3;
    vindex += 4;
}

void initDirectionArea() {
    addSquareToDirectionArea(0, 1, 4, 5, 0);
    addSquareToDirectionArea(2, 3, 6, 7, 1);
    addSquareToDirectionArea(0, 2, 4, 6, 2);
    addSquareToDirectionArea(1, 3, 5, 7, 3);
    addSquareToDirectionArea(0, 1, 4, 5, 4);
    addSquareToDirectionArea(2, 3, 6, 7, 5);
    addSquareToDirectionArea(0, 2, 4, 6, 6);
    addSquareToDirectionArea(1, 3, 5, 7, 7);
}

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection, TurnView, colorID, colorCheck;
mat4 ModelViews[n3];
mat4 InitialModelViews[n3];
mat4 turnView;
mat4 defaultTurnView = mat4();
mat4  projection, scale;
int cubeCheck_ = 0;
bool directionCheck_ = false;

void initModelViews() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                float s = 1.0f / n;
                ModelViews[i * n2 + j * n + k] = Scale(s, s, s);
                InitialModelViews[i * n2 + j * n + k] = Scale(s, s, s);
                ModelViews[i * n2 + j * n + k] *= Translate(i - ((float)(n - 1) / 2), j - ((float)(n - 1) / 2), k - ((float)(n - 1) / 2));
                InitialModelViews[i * n2 + j * n + k] *= Translate(i - ((float)(n - 1) / 2), j - ((float)(n - 1) / 2), k - ((float)(n - 1) / 2));
            }
        }
    }
}

void init() {
    // Load shaders and use the resulting shader program
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    colorcube();
    initDirectionArea();

    // Create a vertex array object
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create and initialize a buffer object
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(lvertices) + sizeof(dvertices) + sizeof(colors) + sizeof(lcolors) + sizeof(dcolors), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(lvertices), lvertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(lvertices), sizeof(dvertices), dvertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(lvertices) + sizeof(dvertices), sizeof(colors), colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(lvertices) + sizeof(dvertices) + sizeof(colors), sizeof(lcolors), lcolors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices) + sizeof(lvertices) + sizeof(dvertices) + sizeof(colors) + sizeof(lcolors), sizeof(dcolors), dcolors);

    // Create and initialize an index buffer object
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) + sizeof(lindices) + sizeof(dindices), NULL, GL_STATIC_DRAW);

    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), sizeof(lindices), lindices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) + sizeof(lindices), sizeof(dindices), dindices);

    // set up vertex array for position
    GLuint vPosition = glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);

    // set up vertex array for color
    GLuint vColor = glGetAttribLocation(program, "vColor");
    glEnableVertexAttribArray(vColor);
    glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(vertices) + sizeof(lvertices) + sizeof(dvertices)));

    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation(program, "ModelView");
    Projection = glGetUniformLocation(program, "Projection");
    TurnView = glGetUniformLocation(program, "TurnView");
    colorID = glGetUniformLocation(program, "colorID");
    colorCheck = glGetUniformLocation(program, "colorCheck");

    // Set projection matrix
    scale = Scale(1.0f);
    projection = RotateY(15) * RotateX(-10);
    turnView = mat4();
    glUniformMatrix4fv(Projection, 1, GL_TRUE, scale * projection);
    glUniformMatrix4fv(TurnView, 1, GL_TRUE, turnView);
    glUniform1i(colorCheck, 0);

    initColorIDs();
    initModelViews();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                positions[i][j][k] = i * n2 + j * n + k;

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

bool turnUp, turnDown, turnRight, turnLeft;
bool mousePressed = false;
int firstPressed = n3;
int firstColor = 0;
int turningPositions[n][n];
const float TURN_RATE = 90.0f / FRAME_RATE;

bool isTurning(int x) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (turningPositions[i][j] == x)
                return true;
    return false;
}

//draw: this method draws the cubes and the lines
void draw() {
    if (directionCheck_) {
        mat4 dirView = InitialModelViews[firstPressed];
        switch (firstColor) {
        case (0):
            dirView *= Translate(-0.5f, 0.0f, 0.0f);
            dirView *= RotateY(90);
            break;
        case (1):
            dirView *= Translate(0.5f, 0.0f, 0.0f);
            dirView *= RotateY(-90);
            dirView *= RotateX(180);
            break;
        case (2):
            dirView *= Translate(0.0f, -0.5f, 0.0f);
            dirView *= RotateX(90);
            dirView *= RotateZ(90);
            break;
        case (3):
            dirView *= Translate(0.0f, 0.5f, 0.0f);
            dirView *= RotateX(90);
            dirView *= RotateZ(-90);
            break;
        case (4):
            dirView *= Translate(0.0f, 0.0f, -0.5f);
            dirView *= RotateX(0);
            dirView *= RotateZ(-90);
            break;
        case (5):
            dirView *= Translate(0.0f, 0.0f, 0.5f);
            dirView *= RotateZ(90);
            break;
        }
        glUniformMatrix4fv(ModelView, 1, GL_TRUE, dirView);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, (GLvoid*)(sizeof(indices) + sizeof(lindices) + (int)(firstColor / 2) * 48));
    }
    else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    if (cubeCheck_ == 1) {
                        float* temp = colorIDs[i][j][k];
                        glUniform4f(colorID, temp[0], temp[1], temp[2], temp[3]);
                        glUniformMatrix4fv(ModelView, 1, GL_TRUE, InitialModelViews[i * n2 + j * n + k]);
                    }
                    else if (cubeCheck_ == 2) {
                        glUniformMatrix4fv(ModelView, 1, GL_TRUE, InitialModelViews[i * n2 + j * n + k]);
                    }
                    else {
                        glUniformMatrix4fv(ModelView, 1, GL_TRUE, ModelViews[i * n2 + j * n + k]);
                        glUniformMatrix4fv(TurnView, 1, GL_TRUE, isTurning(i * n2 + j * n + k) ? turnView : defaultTurnView);
                    }
                    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                    glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, (GLvoid*)(sizeof(indices)));
                }
            }
        }
    }
}

void display() {
    //SET-UP
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LINE_SMOOTH);

    draw();

    glFlush();
}

int direction;
const int TURN_NUM = 90.0f / TURN_RATE;
int turn = 0;

void update() {
    if (turn > 0) {
        switch (direction) {
        case (0): turnView = RotateY(-turn * TURN_RATE); break;
        case (1): turnView = RotateY(turn * TURN_RATE); break;
        case (2): turnView = RotateZ(-turn * TURN_RATE); break;
        case (3): turnView = RotateZ(turn * TURN_RATE); break;
        case (4): turnView = RotateX(-turn * TURN_RATE); break;
        case (5): turnView = RotateX(turn * TURN_RATE); break;
        default: turnView = defaultTurnView;
        }
        turn -= 3;
        if (turn <= 0)
            turnView = defaultTurnView;
    }
    else {
        if (turnUp && !turnDown)
            projection = RotateX(TURN_RATE) * projection;
        if (turnDown && !turnUp)
            projection = RotateX(-TURN_RATE) * projection;
        if (turnRight && !turnLeft)
            projection = RotateY(-TURN_RATE) * projection;
        if (turnLeft && !turnRight)
            projection = RotateY(TURN_RATE) * projection;

        glUniformMatrix4fv(Projection, 1, GL_TRUE, scale * projection);
    }
}

void turnCube(int dir) {
    direction = dir;
    turn = TURN_NUM;
    int fi = firstPressed / n2;
    int fj = (firstPressed % n2) / n;
    int fk = firstPressed % n;
    int spin = (dir % 2) ? -1 : 1;
    mat4 turnSide = mat4();
    if ((int)(dir / 2) == 0) {
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                turningPositions[i][k] = positions[i][fj][k];
        turnSide = RotateY(spin * 90);
    }
    else if ((int)(dir / 2) == 1) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                turningPositions[i][j] = positions[i][j][fk];
        turnSide = RotateZ(spin * 90);
    }
    else if ((int)(dir / 2) == 2) {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                turningPositions[j][k] = positions[fi][j][k];
        turnSide = RotateX(spin * 90);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int pos = turningPositions[i][j];
            ModelViews[pos] = turnSide * ModelViews[pos];
        }
    }

    if ((int)(dir / 2) == 0) {
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                positions[i][fj][k] = spin == 1 ? turningPositions[n - k - 1][i] : turningPositions[k][n - i - 1];
    }
    else if ((int)(dir / 2) == 1) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                positions[i][j][fk] = spin == -1 ? turningPositions[n - j - 1][i] : turningPositions[j][n - i - 1];
    }
    else if ((int)(dir / 2) == 2) {
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                positions[fi][j][k] = spin == -1 ? turningPositions[n - k - 1][j] : turningPositions[k][n - j - 1];
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key) {
    case GLFW_KEY_ESCAPE:
    case GLFW_KEY_Q:
        exit(EXIT_SUCCESS);
        break;
    case GLFW_KEY_R:
        projection = RotateY(15) * RotateX(-10);
        break;
    case GLFW_KEY_UP:
        switch (action) {
        case GLFW_PRESS:
            turnUp = true;
            mousePressed = false;
            break;
        case GLFW_RELEASE:
            turnUp = false;
            break;
        }
        break;
    case GLFW_KEY_DOWN:
        switch (action) {
        case GLFW_PRESS:
            turnDown = true;
            mousePressed = false;
            break;
        case GLFW_RELEASE:
            turnDown = false;
            break;
        }
        break;
    case GLFW_KEY_LEFT:
        switch (action) {
        case GLFW_PRESS:
            turnLeft = true;
            mousePressed = false;
            break;
        case GLFW_RELEASE:
            turnLeft = false;
            break;
        }
        break;
    case GLFW_KEY_RIGHT:
        switch (action) {
        case GLFW_PRESS:
            turnRight = true;
            mousePressed = false;
            break;
        case GLFW_RELEASE:
            turnRight = false;
            break;
        }
        break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS && !turnUp && !turnDown && !turnLeft && !turnRight && turn <= 0) {
            float pixel[4];
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            if (xpos > 0 && xpos < WIDTH && ypos > 0 && ypos < HEIGHT) {
                cubeCheck_ = 2;
                display();
                glReadPixels(xpos, HEIGHT - ypos, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
                for (int i = 0; i < 6; i++)
                    if (pixel[0] == colorTypes[i][0] && pixel[1] == colorTypes[i][1] && pixel[2] == colorTypes[i][2])
                        firstColor = i;
                glUniform1i(colorCheck, 1);
                cubeCheck_ = 1;
                display();
                glReadPixels(xpos, HEIGHT - ypos, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
                int cubeNum = (int)(pixel[0] / colorOffset + 0.5) * n2
                    + (int)(pixel[1] / colorOffset + 0.5) * n
                    + (int)(pixel[2] / colorOffset + 0.5);
                if (cubeNum < n3) {
                    firstPressed = cubeNum;
                    mousePressed = true;
                }
                glUniform1i(colorCheck, 0);
                cubeCheck_ = 0;
            }
        }
        else if (action == GLFW_RELEASE) {
            directionCheck_ = false;
            mousePressed = false;
        }
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height); //may not need this since the default is usually the window size
    WIDTH = width;
    HEIGHT = height;

    // Set scale matrix
    if (width <= height)
        scale = Scale(1.0f, (float)width / (float)height, 1.0f);
    else
        scale = Scale((float)height / (float)width, 1.0f, 1.0f);

    glUniformMatrix4fv(Projection, 1, GL_TRUE, scale * projection);
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
    if (mousePressed) {
        float pixel[4];
        if (xpos > 0 && xpos < WIDTH && ypos > 0 && ypos < HEIGHT) {
            directionCheck_ = true;
            display();
            glReadPixels(xpos, HEIGHT - ypos, 1, 1, GL_RGBA, GL_FLOAT, &pixel);
            int dir = (int)(pixel[1] / 0.1 - 0.5);
            if (dir != 9) {
                turnCube(dir);
                directionCheck_ = false;
                mousePressed = false;
            }
            directionCheck_ = false;
        }
    }
}

int main(void) {
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(WIDTH, HEIGHT, "Rubic's Cube", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize glew
    if (glewInit() != GLEW_OK)
        return -1;

    // Set key, mouse, framebuffer callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    // Init
    init();

    double curtime, prevtime = glfwGetTime();
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        curtime = glfwGetTime();
        if (curtime - prevtime > 1.0 / FRAME_RATE) {
            prevtime = curtime;
            update();
        }

        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Display
        display();

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Exit Program
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}