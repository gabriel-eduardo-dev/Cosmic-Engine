#version 460 core

// code from: https://github.com/StanislavPetrovV/The-Planet-Sine

layout(location = 0) in vec3 in_position;

void main() {
    gl_Position = vec4(in_position, 1.0);
}
