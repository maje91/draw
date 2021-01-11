#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 delta;
layout (location = 2) in float dir;

uniform float width;
uniform mat2 A;
uniform vec2 b;

void main() {
    float w = width;
    float l = length(A * delta);

    mat2 R = mat2(
        0.0, -1.0,
        1.0, 0.0
    );

    vec2 p = A * pos + b + (dir * w / l) * R * A * delta;
    gl_Position = vec4(p, 0.0, 1.0);
}
