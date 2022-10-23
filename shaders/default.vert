#version 460 core
layout (location = 0) in vec3 i_pos;

uniform vec3 u_scales = vec3(1.0, 1.0, 1.0);
uniform	mat4 u_cam_matrix;
uniform mat4 transform;
uniform vec3 offsets[1000];

void main()
{
	vec3 offsett = offsets[gl_InstanceID];
	gl_Position = u_cam_matrix * transform * vec4(
			i_pos.x + offsett.x * u_scales.x, 
			i_pos.y + offsett.y * u_scales.y, 
			i_pos.z + offsett.z * u_scales.z, 
			1.0);
}

