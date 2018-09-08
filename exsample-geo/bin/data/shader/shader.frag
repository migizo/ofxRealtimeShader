#version 150

uniform vec4 globalColor;

out vec4 outputColor;

uniform float test_value_01;
uniform float test_value_02;
uniform float test_value_03;
uniform float test_value_04;

void main(){
    outputColor = vec4(test_value_01, test_value_02, test_value_03, test_value_04);
}