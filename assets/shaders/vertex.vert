#version 430 core

/** Inputs */
layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

/** Outputs */
layout(location = 0) out vec3 vsColor;
layout(location = 1) out vec2 vsTex;

uniform vec2 posTex;


void main()
{
    vsColor = aColor;
    gl_Position = vec4(aPosition, 0.0, 1.0);
    if (aTex != vec2(0.f, 0.f)) 
    {
        vsTex = aTex + posTex;
    }
}
