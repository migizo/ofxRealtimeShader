#version 150
precision mediump float;

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec4 v2gPosition[];
uniform mat4 modelViewProjectionMatrix;

uniform float test_value_02;

void main() {    
    gl_Position = modelViewProjectionMatrix * v2gPosition[0];
    EmitVertex();
    gl_Position = modelViewProjectionMatrix * (v2gPosition[0] + vec4(0, 1000 * test_value_02, 0, 0));
    EmitVertex(); 
    EndPrimitive();

}