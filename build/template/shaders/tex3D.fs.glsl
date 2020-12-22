#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;
uniform sampler2D uTexture;

void main() {
  vec4 texture = texture(uTexture, vTexCoords);
  fFragColor = texture.rgb;
};