#version 450 core

out gl_PerVertex
{
    vec4 gl_Position;
};

layout(location = 0) in vec2 AttrPosition;

out vec3 Color;

void main()
{	
	gl_Position = vec4(AttrPosition.xy, 0.0, 1.0);
	Color = vec3(1.0, 0.9, 0.8);
}

