out vec4 color;

layout (location = 0) uniform vec4 in_color;
layout (location = 1) uniform sampler2D tex;

in vec2 ftexcoord;

void main()
{
    color = texture(tex, ftexcoord);
} 