#version 150

uniform vec4 globalColor;

out vec4 outputColor;
 
uniform float test_value_03;

void main(){
    outputColor = vec4(1.0, test_value_03, 1.0, 1.0);
}