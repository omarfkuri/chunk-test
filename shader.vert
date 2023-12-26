#version 330

layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vCoords;
layout (location = 3) in float vTexID;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 outPosition;
out vec2 texCoords;
out float texID;

void main() {
    mat4 modelView = view * model;
    vec4 mvPosition =  modelView * vec4(vPos, 1.0);
    gl_Position = projection * mvPosition;
    outPosition = (model * vec4(vPos, 1.0)).xyz;
    normal = vNormal;
    texCoords = vCoords;
    texID = vTexID;
}