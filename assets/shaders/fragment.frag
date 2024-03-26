#version 430 core

/** Inputs */
layout(location = 0) in vec3 vsColor;
layout(location = 1) in vec2 vsTex;

/** Outputs */
layout(location = 0) out vec4 outColor;

layout(binding = 0) uniform sampler2D uTextureA;


void main()
{
	
	if (vsTex == vec2(0.f, 0.f)) 
	{
		outColor = vec4(vsColor, 1.f);
	}
	else 
	{
		outColor = vec4(vsColor, 1.f) * texture(uTextureA, vsTex);
		
	}
}
