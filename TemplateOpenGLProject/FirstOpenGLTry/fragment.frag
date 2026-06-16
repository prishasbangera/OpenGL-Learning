#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D outTexture;

uniform vec4 ourColor;

void main()
{
	FragColor = vec4( vec4(vertexColor, 1.0) + ourColor + 4.0 * texture(outTexture, TexCoord));
	FragColor = texture(outTexture, TexCoord);
}