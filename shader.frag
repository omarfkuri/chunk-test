#version 330

in vec3 normal;
in vec3 outPosition;
in vec2 texCoords;
in float texID;

out vec4 fragment;
uniform sampler2DArray textures;

void main() {

    fragment = texture(textures, vec3(texCoords.xy, texID));
}