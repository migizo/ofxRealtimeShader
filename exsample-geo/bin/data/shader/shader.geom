#version 150
precision mediump float;

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec4 v2gPosition[];
uniform mat4 modelViewProjectionMatrix;

uniform float time;
uniform vec2 res;
uniform vec2 mouse;
void main() {    
    gl_Position = modelViewProjectionMatrix * v2gPosition[0];
    EmitVertex();
    float add_x = sin(time) * (100 + 100 * mouse.x / res.x);
    float add_y = 1000 * mouse.y / res.y;
    gl_Position = modelViewProjectionMatrix * (v2gPosition[0] + vec4(add_x, add_y, 0, 0));
    EmitVertex(); 
    EndPrimitive();

}