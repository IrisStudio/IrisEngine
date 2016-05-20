layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;

out vec2 ftexcoord;

const vec2 madd=vec2(0.5,0.5);

void main()
{
    gl_Position = vec4(position.xy, 0.0, 1.0);
	ftexcoord = position.xy*madd+madd; // scale vertex attribute to [0-1] range;
	ftexcoord = vec2( ftexcoord.x, 1.0 - ftexcoord.y );
}