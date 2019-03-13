#version 330 core
in vec2 TexCoord;
in vec4 vertexColor;// the input variable from the vertex shader (same name and same type)

out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float awesomeAlpha;
uniform float colorAlpha;

void main()
{
	vec2 texCoordTrans = vec2(1.0 - TexCoord.x, TexCoord.y);
	vec4 color1 = texture(texture1, texCoordTrans);
	vec4 color2 = texture(texture2, texCoordTrans);
	vec4 mixColor = mix(color1, color2, awesomeAlpha);
//	FragColor = mixColor * vertexColor;
	FragColor = mix(mixColor, vertexColor, colorAlpha);
}
