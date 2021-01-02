#version 300 es
precision mediump float;

in vec2 vTexture;
in vec4 vColor;

out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
  vec4 texture = texture(uTexture, vTexture);
  fFragColor = texture.rgba;
};