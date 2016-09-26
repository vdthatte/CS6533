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
void main() {
    varyingTexCoord = texCoord;
    gl_Position = position;
}
