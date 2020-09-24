#version 330 core
in vec3 normal;
in vec3 fragWorldPosition;
in vec2 TexCoord;
out vec4 FragColor;

struct Material {
    sampler2D texture_diffuse0;
    sampler2D texture_specular0;
    float shininess;
};
struct Light {
    vec3 color;
//intensity of the basic components
    float ambient;
    float diffuse;
    float specular;
};

struct DirLight{
    Light light;
    vec3 dir;
};

struct PointLight{
    Light light;
    vec3 position;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight{
    Light light;
    vec3 position;
    vec3 direction;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform bool dirLightSet;
uniform bool pointLightSet;
uniform bool spotLightSet;
uniform sampler2D Texture0;
uniform vec3 viewPos;

vec3 CalcDirLight(vec3 normal, vec3 viewDir){
    vec3 lightDir = normalize(-dirLight.dir);
    //ambient
    vec3 ambient =  vec3(texture(material.texture_diffuse0, TexCoord)) * dirLight.light.color * dirLight.light.ambient;
    //diffuse
    vec3 diffuse =  max(dot(normal, lightDir), 0.0)  * dirLight.light.color * dirLight.light.diffuse * vec3(texture(material.texture_diffuse0, TexCoord));
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.texture_specular0, TexCoord))  * dirLight.light.color * dirLight.light.specular;

    return (ambient + diffuse + specular);
}
vec3 CalcPointLight(vec3 norm, vec3 viewDir){
    vec3 LightDir = pointLight.position - fragWorldPosition;
    float distance = length(LightDir);
    LightDir = normalize(LightDir);
    //calculating attentuation ( simulating model of light intensities for distances)
    float attentuation = 1.0 / (pointLight.constant + (pointLight.linear * distance) + (pointLight.quadratic * (distance * distance)));
    //ambient
    vec3 ambient = vec3(texture(material.texture_diffuse0, TexCoord))  * pointLight.light.color  * attentuation * pointLight.light.ambient;
    //diffuse
    vec3 diffuse = max(dot(norm, LightDir), 0.0) * vec3(texture(material.texture_diffuse0,TexCoord))  * pointLight.light.color * attentuation * pointLight.light.diffuse;
    //specular
    vec3 reflectDir = reflect(-LightDir, norm);
    vec3 specular = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess) * vec3(texture(material.texture_specular0,TexCoord)) *
    pointLight.light.color  * attentuation * pointLight.light.specular;

    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(vec3 viewDir, vec3 normal){
    vec3 lightDir = spotLight.position - fragWorldPosition;
    float distance = length(lightDir);
     lightDir = normalize(lightDir);
    float theta = dot(lightDir, normalize(-spotLight.direction));
    //the highest intensity is in the the inner cone, the lowest is at the oustisde of the outer cone
    float intensity = clamp((theta - spotLight.outerCutOff) / (spotLight.cutOff - spotLight.outerCutOff), 0.0, 1.0);
    //calculating attentuation ( simulating model of light intensities for distances)
    float attentuation = 1.0 / (spotLight.constant + (spotLight.linear * distance) + (spotLight.quadratic * (distance * distance)));
    //ambient
    vec3 ambient = vec3(texture(material.texture_diffuse0, TexCoord)) * spotLight.light.color  * attentuation * spotLight.light.ambient;
    //diffuse
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * vec3(texture(material.texture_diffuse0, TexCoord))  * spotLight.light.color * attentuation
    * intensity * spotLight.light.diffuse;
    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * vec3(texture(material.texture_specular0,TexCoord)) * spotLight.light.color  * attentuation  * intensity
    * spotLight.light.specular;
    return (ambient + diffuse + specular);
}
void main()
{
    vec3 viewDir = normalize(viewPos - fragWorldPosition);
    vec3 norm = normalize(normal);
    vec3 result;
    if (dirLightSet)
    result = CalcDirLight(norm, viewDir);
    if (pointLightSet)
    result += CalcPointLight(norm, viewDir);
    if (spotLightSet)
    result += CalcSpotLight(norm, viewDir);
    FragColor = vec4(result, 1);
}