layout(location = 0) uniform mat4 model;
layout(location = 1) uniform mat4 view;
layout(location = 2) uniform mat4 projection;

layout (location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 uv;

out vec3 Normal;
out vec2 ftexcoord;

void main()
{
     gl_Position = projection * view * model * vec4(position, 1.0f);
	 Normal = normal;
	 ftexcoord = vec2( uv.x, 1 - uv.y );
}