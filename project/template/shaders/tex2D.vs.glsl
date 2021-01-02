#version 300 es
precision mediump float;

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec2 aVertexTexture;

out vec2 vTexture;
out vec3 uColor;

void main() {
  gl_Position = vec4(aVertexPosition, 1.0);
  uColor = aVertexColor;
  vTexture = aVertexTexture;
}
