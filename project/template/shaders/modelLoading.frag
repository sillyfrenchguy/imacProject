#version 310 es
precision mediump float;

in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture_diffuse;

void main( )
{
    color = vec4( texture( texture_diffuse, TexCoords ));
}
