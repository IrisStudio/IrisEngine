layout (location = 0) out vec3 gAlbedoSpec;
layout (location = 1) out vec3 gWorldSpacePosition;
layout (location = 2) out vec3 gWorldSpaceNormal;


layout(location = 1) uniform sampler2D diffuse;

in vec2 ftexcoord;
in vec3 Normal;
in vec4 WorldPos0; 

void main() 
{ 
    gAlbedoSpec = texture(diffuse, ftexcoord).xyz;
	gWorldSpacePosition = WorldPos0.xyz;
	gWorldSpaceNormal = Normal;
}