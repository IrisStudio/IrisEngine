layout (location = 0) in vec3 position;

layout (location = 3) uniform mat4 model;
layout (location = 1) uniform mat4 view;
layout (location = 2) uniform mat4 projection;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
}