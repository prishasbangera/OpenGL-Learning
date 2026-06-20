#version 330 core
out vec4 FragColor;

in vec3 vertexColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec4 ourColor;

void main()
{
	FragColor = vec4( vec4(vertexColor, 1.0) + ourColor * texture(texture1, TexCoord));
	//FragColor = mix(texture(texture2, TexCoord), FragColor, 0.5);
	FragColor *= texture(texture2, TexCoord);
}