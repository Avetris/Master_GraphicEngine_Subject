#version 330 core

out vec4 FragColor;

in vec3 normal;
in vec3 fragPos;
in vec2 uv;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emissive; // Obtenemos la textura del mapa emisivo
    int shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emissive; // Obtenemos el color que le queremos dar al mapa mapa emisivo
};
uniform Light light;

uniform vec3 viewPos;

void main() {
    vec3 albedo = vec3(texture(material.diffuse, uv));
    vec3 ambient = albedo * light.ambient;

    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * albedo * light.diffuse;

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.specular, uv)) * light.specular; 

    vec3 emissive =  vec3(texture(material.emissive, uv)) * light.emissive; // Calculamos el vetor de los valores de la emision con la textura + el color de emision que le queremos dar

    vec3 phong = ambient + diffuse + specular + emissive; // Anadimos la emision al phong
    FragColor = vec4(phong, 1.0f);
}