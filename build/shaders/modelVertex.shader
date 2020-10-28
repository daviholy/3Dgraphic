#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 fragWorldPosition;
out vec2 TexCoord;
out mat3 TBN;
void main(){
    gl_Position = projection * view * model * vec4(aPos,1.0);

    fragWorldPosition = vec3(model * vec4(aPos,1.0));
    //scale the normal vector with normal matrix
    mat3 normal = (transpose(inverse(mat3(model))));
    //set TBN matrix
    vec3 T = normalize(normal * aTangent);
    vec3 N = normalize(normal * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
     TBN = mat3(T, B, N);

    //
    TexCoord = aTexCoords;
}