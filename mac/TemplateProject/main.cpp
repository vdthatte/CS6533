
#include <GLUT/glut.h>
#include "glsupport.h"

GLuint program;
GLuint vertPositionVBO;
GLuint positionAttribute;
GLuint textCoordAttribute;
GLuint vertTexCoordVBO;
GLuint emojiTexture;

/*
 
    Red Rectangle:
 
    1. Write and load a simple shader program.
 
    2. Get the location of the vertex “position” attribute in the loaded program.
 
    3. Create an array of position attributes as a vertex buffer object that
       describe two triangles.
    
    4. Render the vertex buffer object using the shader program by binding it to
       the location of the position attribute.
 
    
    Image:
 
 
    1. Add a texture coordinate attribute to the vertex shader.
    
    2. Add a texture coordinate varying variable to the vertex shader and set it to the texture coordinate
       attribute.
    
    3. Add a texture coordinate varying variable to the fragment shader.
    
    4. Add a texture uniform to the fragment shader and sample it at the varying texture coordinate.
    
    5. Get the location of the texture coordinate attribute in the loaded program.
    
    6. Create an array of texture coordinates as a buffer object that describe how the vertices map to
       the image.
    
    7. Load an image file into memory and create an OpenGL texture from it.
    
    8. Bind the texture coordinate buffer object to the texture coordinate attribute location when we
       render.
    
    9. Get the location of the texture uniform and bind our texture location to it when we render.
 
 */

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertPositionVBO);
    glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(positionAttribute);
    glBindBuffer(GL_ARRAY_BUFFER, vertTexCoordVBO);
    glVertexAttribPointer(textCoordAttribute, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(textCoordAttribute);
    glBindTexture(GL_TEXTURE_2D, emojiTexture);
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
    
    // Get an attribute location in program.
    glUseProgram(program);
    positionAttribute = glGetAttribLocation(program, "position");
    
    // Getting locations of the new attribute on the C++ side.
    textCoordAttribute = glGetAttribLocation(program, "texCoord");
    
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
    
    emojiTexture = loadGLTexture("/Users/Vidyadhar/Desktop/Github/CS6533 - myVersion/mac/TemplateProject/emoji.png");
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
