
#include <GLUT/glut.h>
#include "glsupport.h"

GLuint program;
GLuint vertPositionVBO;
GLuint positionAttribute;

/*
 
 1. Write and load a simple shader program.
 2. Get the location of the vertex “position” attribute in the loaded program.
 3. Create an array of position attributes as a vertex buffer object that
 describe two triangles.
 4. Render the vertex buffer object using the shader program by binding it to
 the location of the position attribute.
 
 */

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Rendering Vertex Buffer
    glUseProgram(program);
    glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(positionAttribute);
    
    glutSwapBuffers();
}

void init() {
    
    // Load a simple shader program
    
    program = glCreateProgram();
    
    // TODO: Get it to work as a global path
    readAndCompileShader(program, "/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/vertex.glsl", "/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/fragment.glsl");
    
    // Get an attribute location in program.
    glUseProgram(program);
    positionAttribute = glGetAttribLocation(program, "position");
    
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
    
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CS-6533");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    
    init();
    glutMainLoop();
    return 0;
}
