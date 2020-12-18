#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

out vec3 fFragColor;
uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

void main() {
  vec4 color = texture(uEarthTexture, vTexCoords);
  vec4 color2 = texture(uCloudTexture, vTexCoords);
  fFragColor = color.rgb + color2.rgb;
};