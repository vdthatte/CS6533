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
uniform float time;
void main() {
    vec2 texCoord = vec2(varyingTexCoord.x + time, varyingTexCoord.y);
    gl_FragColor = texture2D(texture, texCoord);
}
