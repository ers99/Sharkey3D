#version 450 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixAmount;

void main()
{
   FragColor = texture(ourTexture1, TexCoord);

}