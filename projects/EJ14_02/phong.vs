#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

#define NUMBER_SPOT_LIGHTS 2
uniform mat4 lightSpaceMatrix[NUMBER_SPOT_LIGHTS];

out vec3 normal;
out vec3 fragPos;
out vec2 uv;
out vec4 fragPosLighSpace[NUMBER_SPOT_LIGHTS];

void main() {
    uv = aUv;
    normal = normalMat * aNormal;
    fragPos = vec3(model * vec4(aPos, 1.0));
    for(int i = 0; i < NUMBER_SPOT_LIGHTS; i++){
        fragPosLighSpace[i] = lightSpaceMatrix[i] * vec4(fragPos, 1.0);
    }
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}