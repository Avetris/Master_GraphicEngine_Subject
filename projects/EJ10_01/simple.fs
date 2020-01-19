#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 uv;

struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

struct PointLight {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLight;

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
uniform int shininess;
uniform bool lanternEnabled;
uniform SpotLight spotLight;

uniform vec3 viewPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

vec3 calcDirectionalLight(DirLight light, vec3 normal, vec3 viewDir, vec3 albedoMap, vec3 specularMap) {
    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = spec * specularMap * light.specular;

    return ambient + diffuse + specular;
}

vec3 calcPointLight(PointLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap) {
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
        light.linear * distance +
        light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec3 specular = spec * specularMap * light.specular;

    return (ambient + diffuse + specular) * attenuation;
}


vec3 calcSpotLight(SpotLight light, vec3 normal, vec3 viewDir, vec3 fragPos, vec3 albedoMap, vec3 specularMap) {
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant +
        light.linear * distance +
        light.quadratic * distance * distance);

    vec3 ambient = albedoMap * light.ambient;

    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * albedoMap * light.diffuse;

     vec3 halfwayDir = normalize(lightDir + viewDir);
     float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
     vec3 specular = spec * specularMap * light.specular;    

     float theta = dot(lightDir, normalize (-light.direction)); 
     float epsilon = light.cutOff - light.outerCutOff; 
     float intensity = clamp ((theta -  light.outerCutOff) /  epsilon , 0.0 , 1.0 );  

    return (ambient + (diffuse * intensity) + (specular * intensity)) * attenuation; 
}

void main() {
    vec3 albedo = vec3(texture(texture_diffuse1, uv));
    vec3 specular = vec3(texture(texture_specular1, uv));

    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(viewPos - fragPos);

    vec3 finalColor = calcDirectionalLight(dirLight, norm, viewDir, albedo, specular);

    finalColor += calcPointLight(pointLight, norm, viewDir, fragPos, albedo, specular);
    if(lanternEnabled){
        finalColor += calcSpotLight(spotLight, norm, viewDir, fragPos, albedo, specular);
    }
    
    FragColor = vec4(finalColor, 1.0);
}