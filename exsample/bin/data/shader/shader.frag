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
    // convert to -0.5 ~ 0.5
    float x = gl_FragCoord.x / res.x - 0.5; 
    float y = gl_FragCoord.y / res.y - 0.5;    
    vec4 w = vec4(distance(vec2(0, 0), mod(vec2(x, y), test_value_01)));
    w.r *= test_value_02;
    w.g *= test_value_03;
    w.b *= test_value_04;

	gl_FragColor = vec4(w);
}