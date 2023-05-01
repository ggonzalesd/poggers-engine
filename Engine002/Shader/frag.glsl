#version 330 core

in vec3 vColor;

uniform float uDesface;

void main() {
  vec3 color = vec3(sin(uDesface), cos(uDesface), 1.0-cos(uDesface)) * 0.5 + 0.5;
  gl_FragColor = vec4(vColor * color, 1.0);
}