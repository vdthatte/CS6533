
#include <GLUT/glut.h>
#include "glsupport.h"

GLuint program;
GLuint vertPositionVBO;
GLuint positionAttribute;
GLuint textCoordAttribute;
GLuint vertTexCoordVBO;
GLuint emojiTexture;
GLuint positionUniform;
GLuint timeUniform;
GLuint illuminatiTexture;

float textureOffset = 0.0;

void display(void) {
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUniform1f(timeUniform, textureOffset);
    glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
    
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
    
    glVertexAttribPointer(textCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(textCoordAttribute);
    
    glBindTexture(GL_TEXTURE_2D, emojiTexture);
    glUniform2f(positionUniform, 0.5, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glBindTexture(GL_TEXTURE_2D, illuminatiTexture);
    glUniform2f(positionUniform, 0.5, 0.0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(positionAttribute);
    glDisableVertexAttribArray(textCoordAttribute);
    
    glutSwapBuffers();
}


void init() {
    
    // Load a simple shader program
    
    program = glCreateProgram();
    
    // TODO: Get it to work as a global path
    readAndCompileShader(program, "/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/vertex.glsl", "/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/fragment.glsl");
    
    glUseProgram(program);
    
    // Get an attribute location in program.
    positionAttribute = glGetAttribLocation(program, "position");
    
    // Positin uniform Location
    positionUniform =  glGetUniformLocation(program, "positionUniform");

    // Time uniform
    timeUniform = glGetUniformLocation(program, "time");
    
    // Getting locations of the new attribute on the C++ side.
    textCoordAttribute = glGetAttribLocation(program, "texCoord");
    
    // laod textures
    emojiTexture = loadGLTexture("/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/emoji.png");
    illuminatiTexture = loadGLTexture("/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/illuminati.png");
    
    // Create a vertex buffer object
    glGenBuffers(1, &vertPositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
    GLfloat sqVerts[12] = {
        -0.5f, -0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f,
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f
    };
    
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), sqVerts, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertTexCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
    GLfloat sqTexCoords[12] = {
        0.0f, 1.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, 12*sizeof(GLfloat), sqTexCoords, GL_STATIC_DRAW);
    
    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0.5, 0.5, 0.5, 1.0); // set the clear color
    
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void idle(void) {
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'a':
            textureOffset += 0.05;
            break;
        case 'd':
            textureOffset -= 0.05;
            break;
    }
}

void mouse(int button, int state, int x, int y) {
    float newPositionX = (float)x/250.0f - 1.0f;
    float newPositionY = (1.0-(float)y/250.0);
    glUniform2f(positionUniform, newPositionX, newPositionY);
}

void mouseMove(int x, int y) {
    float newPositionX = (float)x/250.0f - 1.0f;
    float newPositionY = (1.0-(float)y/250.0);
    glUniform2f(positionUniform, newPositionX, newPositionY);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CS-6533");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    init();
    glutMainLoop();
    return 0;
}
