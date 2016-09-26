//
//  fragment.glsl
//  TemplateProject
//
//  Created by Vidyadhar V. Thatte on 9/25/16.
//  Copyright © 2016 Ivan Safrin. All rights reserved.
//

/*
 
 
        THIS IS THE FRAGMENT SHADER PROGRAM
 
 
 */


varying vec2 varyingTexCoord;
uniform sampler2D texture;
void main() {
    gl_FragColor = texture2D(texture, varyingTexCoord);
}
