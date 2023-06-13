#version 130

in vec3 aPosition;
in vec3 aColor;
in vec2 aUV;

out vec3 vColor;
out vec2 vUV;

uniform mat4 uCamera;
uniform mat4 uModel;
uniform vec3 uColor;

void main() {
  gl_Position = uCamera * uModel * vec4(aPosition, 1.0);
  vColor = aColor * uColor;
  vUV = aUV;
}