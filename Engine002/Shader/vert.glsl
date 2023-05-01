#version 330 core

in vec3 aPosition;
in vec3 aColor;

out vec3 vColor;

uniform float uDesface;
uniform vec2 uAddPoss;
vec3 pos = vec3(uAddPoss, 0.0);

void main() {

  vec3 pos = 0.3*vec3(cos(uDesface), sin(uDesface), 0.0);
  pos += vec3(uAddPoss, 0.0);

  gl_Position = vec4(aPosition + pos, 1.0);
  vColor = aColor;
}