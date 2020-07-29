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
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Material material;
uniform Light light;
uniform sampler2D Texture0;
uniform vec3 viewPos;
void main(){
    vec3 LightDir = normalize(light.position - fragWorldPosition);
    vec3 viewDir = normalize (viewPos - fragWorldPosition);
    vec3 norm = normalize(normal);
    vec3 reflectDir = reflect(-LightDir, norm);
    //ambient
    vec3 ambient = material.ambient * light.color;
    //diffuse
    // dot product between normal vertex of fragment and direction vector of light
    float diff = max(dot(norm,LightDir),0.0);
    vec3 diffuse = (diff * material.diffuse) * light.color;

    //specular
    float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
    vec3 specular = (spec * material.specular) * light.color;

    //texture
    vec4 texColor = texture(Texture0,TexCoord);
    vec3 result = ((ambient * light.ambient) + (diffuse * light.diffuse) + (specular * light.specular));
    FragColor = vec4(result,1.0) * texColor;
}