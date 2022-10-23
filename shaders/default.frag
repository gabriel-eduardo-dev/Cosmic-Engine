#version 460 core 

#define PI 3.141592653589793
#define TWO_PI 6.28318530718

out vec4 frag_color;

uniform vec2 u_mouse;
uniform float u_time;
uniform vec2 u_resolution;

vec3 hsb2rgb( in vec3 c )
{
    vec3 rgb = clamp(abs(mod(c.x*6.0+vec3(0.0,4.0,2.0),
						6.0)
					-3.0)
				-1.0,0.0,1.0);
    rgb = rgb*rgb*(3.0-2.0*rgb);
    return c.z * mix( vec3(1.0), rgb, c.y);
}

void main()
{
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec3 color = vec3(0.0);

    vec2 toCenter = vec2(0.5)-st;
    float angle = atan(toCenter.x * 0.5,toCenter.y * 0.5) + u_time;
    float radius = length(toCenter)*2.0;

    color = hsb2rgb(vec3((angle / PI) + u_mouse.x,radius,1.0));

    frag_color = vec4(color,1.0);
}
