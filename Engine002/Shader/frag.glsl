#version 130

in vec3 vColor;
in vec2 vUV;

uniform sampler2D uTexture;

void main() {
  vec4 texColor = texture(uTexture, vUV);
  if (texColor.a < 0.5)
    discard;
  else
    gl_FragColor = vec4(texColor.rgb * vColor, 1.0);
}