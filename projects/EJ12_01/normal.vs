#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

out vec2 uv;
out vec3 fragPos;
out mat3 TBN;

uniform vec3 viewPos;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

void main() {
    uv = aUv;
    fragPos = vec3(model * vec4(aPos, 1.0));

    vec3 T = normalize(normalMat * aTangent);
    vec3 N = normalize(normalMat * aNormal);
    T = normalize(T - dot(T,N) * N);
    vec3 B = cross(N, T);

    TBN = mat3(T, B, N);  // se calcula la matriz TBN en vez de su inversa y se pasa al shader de fragmentos

    gl_Position = proj * view * model * vec4(aPos, 1.0);
}