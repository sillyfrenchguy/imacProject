#version 300 es
precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;

out vec3 fFragColor;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(vec3 position_vs, vec3 normal_vs){
    vec3 w0 = normalize(-position_vs);
    vec3 wi = normalize(uLightDir_vs);
    vec3 halfVector = (w0 + wi)/2.0;
    return uLightIntensity*(uKd*dot(normal_vs, wi) + uKs*pow((dot(normal_vs,halfVector)), uShininess));
};

void main() {
  fFragColor = blinnPhong(vPosition_vs, normalize(vNormal_vs));
};