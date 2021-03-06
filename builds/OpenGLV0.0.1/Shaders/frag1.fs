#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixAmount;

void main()
{
   FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixAmount);

}