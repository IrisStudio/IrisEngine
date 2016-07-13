layout (location = 0) out vec3 gAlbedoSpec;
layout (location = 1) out vec3 gWorldSpacePosition;
layout (location = 2) out vec3 gWorldSpaceNormal;


layout(location = 1) uniform sampler2D diffuse;

in vec2 ftexcoord;
in vec3 Normal;

void main() 
{ 
    gAlbedoSpec = texture(diffuse, ftexcoord).xyz;
	gWorldSpacePosition = vec3(0.0, 1.0, 0.0);
	gWorldSpaceNormal = Normal;
}