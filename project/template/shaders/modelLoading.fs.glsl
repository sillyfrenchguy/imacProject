#version 300 es
precision mediump float;

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse;

void main() {
  vec4 texture = texture(texture_diffuse, TexCoords);
  color = texture;
};