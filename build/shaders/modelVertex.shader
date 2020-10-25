#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragWorldPosition;
out vec2 TexCoord;

void main(){
    gl_Position = projection * view * model * vec4(aPos,1.0);
    fragWorldPosition = vec3(model * vec4(aPos,1.0));
    //scale the normal vector with normal matrix
    normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoords;
}