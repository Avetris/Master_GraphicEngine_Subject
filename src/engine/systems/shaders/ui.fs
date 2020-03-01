#version 330 core

in vec2 uv;
out vec4 FragColor;

uniform sampler2D textTexture;
uniform vec3 textColor;

void main()
{    
	vec4 text = texture(textTexture, uv);
	if(text.a < 0.1)
		discard;
	FragColor = text * vec4(textColor, 1.0);
}  