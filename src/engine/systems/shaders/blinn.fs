#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 tangentFragPos;
in vec2 uv;

#define NUMBER_GLOBAL_LIGHTS 11
#define NUMBER_LIGHTS 5
#define NUMBER_DIRECT_LIGHTS 1
uniform int numberOfShadows = 0;
in vec4 fragPosLightSpace[NUMBER_GLOBAL_LIGHTS];

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D normal;
    int shininess;
};
uniform bool hasMaterial = false;
uniform Material material;
uniform vec3 modelColor;

uniform bool normalsEnabled = false;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform int numDirectLight = 0;
uniform DirLight dirLight[NUMBER_DIRECT_LIGHTS];
in vec3 tangentDirLight[NUMBER_LIGHTS];

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
in vec3 tangentPointLight[NUMBER_LIGHTS];

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
in vec3 tangentSpotLight[NUMBER_LIGHTS];

in vec3 tangentViewPos;

uniform sampler2D depthMap;

float ShadowCalculation(float bias) {
//    float shadow = 0.0;
//    for(int i = 0; i < numberOfShadows; i++){
//
//        float currentShadow = 0.0;
//
//        vec3 projCoords = fragPosLightSpace[i].xyz / fragPosLightSpace[i].w;
//        projCoords = projCoords * 0.5 + 0.5;
//       // float closestDepth = texture(depthMap, projCoords.xy).r;
//        float currentDepth = projCoords.z;
//
//        vec2 texelSize = 1.0 / textureSize(depthMap, 0);
//        for(int x = -1; x <= 1; ++x) {
//            for (int y = -1; y <=1; ++y) {
//                float pcf = texture(depthMap, projCoords.xy + vec2(x,y) * texelSize).r;
//            
//                currentShadow += currentDepth - (bias / 
//        fragPosLightSpace[i].w) > pcf ? 1.0 : 0.0;
//            }
//	    }
//        currentShadow  /= 9.0;
//
//        if (projCoords.z > 1.0) {
//          currentShadow  = 0.0;
//	    }
//        shadow += currentShadow;
//    }

    vec3 projCoords = fragPosLightSpace[0].xyz / fragPosLightSpace[0].w;
    projCoords = projCoords * 0.5 + 0.5;
    //float closestDepth = texture(depthMap, projCoords.xy).r;
    float currentDepth = projCoords.z;

    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(depthMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for (int y = -1; y <=1; ++y) {
            float pcf = texture(depthMap, projCoords.xy + vec2(x,y) * texelSize).r;
            shadow += currentDepth -bias > pcf ? 1.0 : 0.0;
        }
	}
    shadow /= 9.0;

    if (projCoords.z > 1.0) {
     shadow = 0.0;
	}

    return shadow;
}

vec3 calcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedoMap, vec3 specularMap) {
    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), hasMaterial ? material.shininess : 0);
    vec3 specular = spec * specularMap * light.specular;

     float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
     float shadow = ShadowCalculation(bias);
    
    return (ambient + ((1.0 - shadow) * (diffuse + specular)));
}


vec3 calcPointLight(PointLight light, vec3 lightPos, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap) {
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (light.constant +
        light.linear * distance +
        light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), hasMaterial ? material.shininess : 0);
    vec3 specular = spec * specularMap * light.specular;    

     float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
     float shadow = ShadowCalculation(bias);

    return (ambient + ((1.0 - shadow) * (diffuse + specular))) * attenuation;
}

vec3 calcSpotLight(SpotLight light, vec3 lightPos, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap) {
    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (light.constant +
        light.linear * distance +
        light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

     vec3 halfwayDir = normalize(lightDir + viewDir);
     float spec = pow(max(dot(normal, halfwayDir), 0.0), hasMaterial ? material.shininess : 0);
     vec3 specular = spec * specularMap * light.specular;    

     float theta = dot(lightDir, normalize (-light.direction)); 
     float epsilon = light.cutOff - light.outerCutOff; 
     float intensity = clamp ((theta -  light.outerCutOff) /  epsilon , 0.0 , 1.0 );  
    
      
     float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

     float shadow = ShadowCalculation(bias);

    return (ambient + ((1.0 - shadow) * intensity *  (diffuse + specular))) * attenuation;
}

void main() {
    vec3 albedo = hasMaterial ? vec3(texture(material.diffuse, uv)) : modelColor;
    vec3 specular =  hasMaterial ? vec3(texture(material.specular, uv)) : modelColor;

    vec3 norm = vec3(0.0, 0.0, 0.0);

    if(normalsEnabled){
        norm = vec3(texture(material.normal, uv));
        norm = normalize(norm * 2.0 - 1.0);
    }else{
        norm = normalize(normal);
    }

    vec3 viewDir = normalize(tangentViewPos - tangentFragPos);

    int indexFragPosLightSpace = 0;
    vec4 currentFragPosLightSpace = vec4(1.0, 1.0, 1.0, 1.0);
    vec3 phong = vec3(0.0, 0.0, 0.0);

    for(int i = 0; i < numDirectLight; i++){
        if(indexFragPosLightSpace < numberOfShadows){
            currentFragPosLightSpace = fragPosLightSpace[indexFragPosLightSpace];
            indexFragPosLightSpace++;
        }
        phong += calcDirectionalLight(dirLight[i], norm, viewDir, albedo, specular);
    }
    for(int i = 0; i < numPointLight; i++){
        if(indexFragPosLightSpace < numberOfShadows){
            currentFragPosLightSpace = fragPosLightSpace[indexFragPosLightSpace];
            indexFragPosLightSpace++;
        }
        phong += calcPointLight(pointLight[i], tangentPointLight[i], norm, viewDir, tangentFragPos, albedo, specular);
    }
    for(int i = 0; i < numSpotLight; i++){
        if(indexFragPosLightSpace < numberOfShadows){
            currentFragPosLightSpace = fragPosLightSpace[indexFragPosLightSpace];
            indexFragPosLightSpace++;
        }
        phong += calcSpotLight(spotLight[i], tangentSpotLight[i], norm, viewDir, tangentFragPos, albedo, specular);
    }
    FragColor = vec4(phong, 1.0f);
}