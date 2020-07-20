#version 330 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 vertex_texCoord;
layout (location = 3) in vec2 vertex_smileTexCoord;
out vec3 color;
out vec2 TexCoord;
out vec2 smileTexCoord;

uniform mat4 transform;

void main(){
    gl_Position = transform * vec4(vertex_pos,1.0f);
    color = vertex_color;
    TexCoord = vertex_texCoord;
    smileTexCoord = vertex_smileTexCoord;
}