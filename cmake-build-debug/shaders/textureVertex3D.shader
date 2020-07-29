#version 330 core
layout (location = 0) in vec3 vertex_pos;
layout (location = 1) in vec2 vertex_texCoord;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform sampler2D Texture0;
uniform sampler2D Texture1;
void main(){
    gl_Position = projection * view * model * vec4(vertex_pos,1.0f);
    TexCoord = vertex_texCoord;
}