layout (location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out gl_PerVertex
{
    vec4 gl_Position;
};

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
}