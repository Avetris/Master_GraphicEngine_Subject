#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec2 aUv;
layout (location=2) in vec3 aNormal;
layout (location=3) in vec3 aTangent;
layout (location=4) in vec3 aBitangent;

uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat3 normalMat;

uniform bool normalsEnabled = false;

#define NUMBER_GLOBAL_LIGHTS 11
#define NUMBER_LIGHTS 5
uniform int numberOfShadows = 0;
uniform mat4 lightSpaceMatrix[NUMBER_GLOBAL_LIGHTS];

out vec3 normal;
out vec3 tangentViewPos;
out vec3 tangentFragPos;
out vec2 uv;
out vec4 fragPosLightSpace[NUMBER_GLOBAL_LIGHTS];

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform int numPointLight = 0;
uniform PointLight pointLight[NUMBER_LIGHTS];
out vec3 tangentPointLight[NUMBER_LIGHTS];

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform int numSpotLight = 0;
uniform SpotLight spotLight[NUMBER_LIGHTS];
out vec3 tangentSpotLight[NUMBER_LIGHTS];

void main() {
    uv = aUv;  

    vec3 fragPos = vec3(model * vec4(aPos, 1.0));
    for(int i = 0; i < numberOfShadows; i++){
        fragPosLightSpace[i] = lightSpaceMatrix[i] * vec4(fragPos, 1.0);
    }
    if(normalsEnabled){
        vec3 T = normalize(normalMat * aTangent);
        vec3 N = normalize(normalMat * aNormal);
        T = normalize(T - dot(T,N) * N);
        vec3 B = cross(N, T);

        mat3 TBN = transpose(mat3(T, B, N));  //inverse of TBN, World -> tangent space
        tangentViewPos = TBN * viewPos;
        tangentFragPos = TBN * fragPos;

        for(int i = 0; i < numPointLight; i++){
            tangentPointLight[i] = TBN * pointLight[i].position;    
        }
        for(int i = 0; i < numSpotLight; i++){            
            tangentSpotLight[i] = TBN * spotLight[i].position;    
        }
    }else{
        tangentViewPos = viewPos;
        tangentFragPos = fragPos;
        normal = normalMat * aNormal;        
        for(int i = 0; i < numPointLight; i++){
            tangentPointLight[i] = pointLight[i].position;    
        }
        for(int i = 0; i < numSpotLight; i++){            
            tangentSpotLight[i] = spotLight[i].position;    
        }
    }
    gl_Position = proj * view * model * vec4(aPos, 1.0);
}