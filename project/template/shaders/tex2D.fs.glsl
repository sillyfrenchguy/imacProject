#version 300 es
precision mediump float;

in vec2 vTexture;
in vec3 vColor;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
  vec4 texture = texture(uTexture, vTexture);
  fFragColor = texture.rgb;
};