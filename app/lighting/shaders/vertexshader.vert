// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aNormal;

// out vec3 objectNormal;
// out vec3 fragPosition;

// out vec3 lightPosition;

// out vec3 objectColor;
// out vec3 lightColor;

// out vec3 viewPosition;

// uniform mat4 model;
// uniform mat4 view;
// uniform mat4 projection;

// uniform vec3 object;
// uniform vec3 light;
// uniform vec3 lightPos;

// uniform vec3 viewPos;

// void main()
// {
// 	gl_Position = projection * view * model * vec4(aPos, 1.0);
// //	gl_Position = vec4(aPos, 1.0);
// //	vertexColor = vec4(aColor, 1.0);
// 	objectColor = object;
// 	lightColor = light;

// 	objectNormal = vec3(model * vec4(aNormal, 1.0));
// 	lightPosition = lightPos.xyz;
// 	fragPosition = vec3(model * vec4(aPos, 1.0));

// 	viewPosition = viewPos;
// }


#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 objectNormal;
out vec3 fragPosition;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragPosition = vec3(model * vec4(aPos, 1.0));
	objectNormal = mat3(transpose(inverse(model))) * aNormal;  

	gl_Position = projection * view * vec4(fragPosition, 1.0);

	TexCoord = aTexCoord;
}
