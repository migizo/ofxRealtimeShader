#version 120

uniform float test_value_01;
uniform float test_value_02;
uniform float test_value_03;
uniform float test_value_04;
uniform float time;
uniform float millis;
uniform vec2 res;
uniform vec2 mouse;

void main()
{
    float x = gl_FragCoord.x / res.x - 0.5;
    float y = gl_FragCoord.y / res.y - 0.5;
    float w = distance(vec2(0, 0), vec2(x, y));
	gl_FragColor = vec4(w);
}