#version 330 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 Normal;
layout (location = 2) in vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 normal;
out vec3 fragWorldPosition;
out vec2 TexCoord;
void main(){
    gl_Position = projection * view * model * vec4(vertex_pos,1.0);
    fragWorldPosition = vec3(model * vec4(vertex_pos,1.0));
    //scale the normal vector with 
    normal = mat3(transpose(inverse(model))) * Normal;
    TexCoord = texCoord;
}