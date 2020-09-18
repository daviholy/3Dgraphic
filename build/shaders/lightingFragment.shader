#version 330 core
in vec3 normal;
in vec3 fragWorldPosition;
in vec2 TexCoord;
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

vec3 CalcDirLight(vec3 texColor){
    vec3 LightDir = normalize(-dirLight.dir);
    vec3 norm = normalize(normal);
    //ambient
    vec3 ambient = material.ambient * texColor * dirLight.light.color * dirLight.light.ambient;
    //diffuse
    float diff = max(dot(norm, LightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * texColor * dirLight.light.color * dirLight.light.diffuse;
    //specular
    vec3 reflectDir = reflect(-LightDir, norm);
    vec3 viewDir = normalize (viewPos - fragWorldPosition);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * texColor * dirLight.light.color * dirLight.light.specular;

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(vec3 texColor){
    vec3 LightDir = pointLight.position - fragWorldPosition;
    float distance = length(LightDir);
    LightDir = normalize(LightDir);
    float attentuation = 1.0 / (pointLight.constant + (pointLight.linear * distance) + (pointLight.quadratic * (distance * distance)));
    vec3 norm = normalize(normal);
    //ambient
    vec3 ambient = material.ambient * texColor * pointLight.light.color  * attentuation * pointLight.light.ambient;
    //diffuse
    float diff = max(dot(norm, LightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * texColor * pointLight.light.color * attentuation * pointLight.light.diffuse;
    //specular
    vec3 reflectDir = reflect(-LightDir, norm);\
    vec3 viewDir = normalize (viewPos - fragWorldPosition);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * texColor * pointLight.light.color  * attentuation * pointLight.light.specular;

    return (ambient + diffuse + specular);
}
vec3 CalcSpotLight(vec3 texColor){
    vec3 lightDir = spotLight.position - fragWorldPosition;
    float distance = length(lightDir);
    lightDir = normalize(lightDir);
    float theta = dot(lightDir, normalize(-spotLight.direction));
    //the highest intensity is in the the inner cone, the lowest is at the oustisde of the outer cone
    float intensity = clamp((theta - spotLight.outerCutOff) / (spotLight.cutOff - spotLight.outerCutOff), 0.0, 1.0);
    float attentuation = 1.0 / (spotLight.constant + (spotLight.linear * distance) + (spotLight.quadratic * (distance * distance)));
    vec3 norm = normalize(normal);
    //ambient
    vec3 ambient = material.ambient * texColor * spotLight.light.color  * attentuation * spotLight.light.ambient;
    //diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * texColor * spotLight.light.color * attentuation * intensity * spotLight.light.diffuse;
    //specular
    vec3 reflectDir = reflect(-lightDir, norm);\
    vec3 viewDir = normalize (viewPos - fragWorldPosition);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = spec * material.specular * texColor * spotLight.light.color  * attentuation  * intensity * spotLight.light.specular;
    return (ambient + diffuse + specular);
}
void main(){
/*======================================================
the lighting is break up into 3 different sources, which we can enable or disable by their specific bool uniform.
Each phase is calculated in specific function and summed up to the result.
========================================================*/
vec3 texColor = vec3(texture(Texture0, TexCoord));
vec3 result;
if (dirLightSet)
result = CalcDirLight(texColor);
if (pointLightSet)
result += CalcPointLight(texColor);
if (spotLightSet)
result += CalcSpotLight(texColor);
FragColor = vec4(result, 1.0);
}