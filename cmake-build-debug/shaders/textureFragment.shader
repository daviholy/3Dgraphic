#version 330 core

in vec2 TexCoord;
in vec2 smileTexCoord;
in vec3 color;

out vec4 FragColor;

uniform sampler2D Texture0;
uniform sampler2D Texture1;
uniform float Transparency;
void main(){
    FragColor = mix(texture(Texture0,TexCoord), texture(Texture1,smileTexCoord),Transparency);
}