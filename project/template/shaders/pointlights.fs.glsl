#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 TexCoords;

uniform sampler2D texture_diffuse;

out vec4 fFragColor;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){
    vec3 w0 = normalize(-position_vs);
    vec3 wi = normalize(uLightPos_vs - position_vs);
    float d = distance(uLightPos_vs, position_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    return (uLightIntensity/(d*d))*(uKd*dot(normal_vs, wi) + uKs*pow((dot(normal_vs,halfVector)), uShininess));
};

void main() {
	fFragColor = vec4( blinnPhong(vPosition_vs, normalize(vNormal_vs)) * texture(texture_diffuse, TexCoords).rgb, 1 );
};