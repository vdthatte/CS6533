//
//  vertex.glsl
//  TemplateProject
//
//  Created by Vidyadhar V. Thatte on 9/25/16.
//  Copyright © 2016 Ivan Safrin. All rights reserved.
//

/*
 
        THIS IS THE VERTEX SHADER PROGRAM
 
 */


attribute vec4 position;
attribute vec2 texCoord;
varying vec2 varyingTexCoord;
uniform vec2 modelPosition;
uniform vec4 positionUniform;


void main() {
    varyingTexCoord = texCoord;
    //gl_Position = vec4(modelPosition.x, modelPosition.y, 0.0, 0.0) + position + positionUniform;
    gl_Position = position + positionUniform; // change the position using a shader uniform in the vertex shader
}
