#version 130

in vec3 vColor;
in vec2 vUV;

uniform sampler2D uTexture;

void main() {
  vec4 texColor = texture2D(uTexture, vUV);
  if (texColor.a < 0.5)
    discard;
  else {
    //float c = max(texColor.r, max(texColor.g, texColor.b));
    //c = 1.0f - clamp(sin(3.141592 * c), 0.0f, 1.0f);
    //texColor = 2.5f * vec4(1.0f, 0.75f, 0.25, 1.0) * vec4(c, c, c, 1.0f);
    gl_FragColor = vec4(texColor.rgb * vColor, 1.0);
  }
}