#version 330 core
out vec4 FragColor;
// in vec4 vertexColor;// the input variable from the vertex shader (same name and same type)
//uniform vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

// uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
//    FragColor = vertexColor;
    // FragColor = texture(ourTexture, TexCoord);
	FragColor = texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y));
    // FragColor = texture(ourTexture, TexCoord) * vertexColor;
    // FragColor = mix(texture(ourTexture, TexCoord), texture(texture2, TexCoord), 0.2);
    //vec2(1.0 - TexCoord.x, TexCoord.y)
    // FragColor = mix(texture(ourTexture, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}
