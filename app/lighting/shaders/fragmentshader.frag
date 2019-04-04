#version 330 core
out vec4 FragColor;

// in vec3 objectColor;
// in vec3 lightColor;

// in vec3 objectNormal;
// in vec3 lightPosition;
// in vec3 fragPosition;

// in vec3 viewPosition; 

// void main()
// {
// 	FragColor = vec4(lightColor * objectColor, 1.0);

// 	float ambientStrength = 0.1;
// 	vec3 ambient = ambientStrength * lightColor;
	
// 	vec3 norm = normalize(objectNormal);
// 	vec3 lightDir = normalize(lightPosition - fragPosition);
// 	float diff = max(dot(norm,lightDir), 0.0);
// 	vec3 diffuse = diff * lightColor;
	
// 	float specularStrength = 0.5;
// 	vec3 viewDir = normalize(viewPosition - fragPosition);
// 	vec3 reflectDir = reflect(-lightDir, norm);
// 	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
// 	vec3 specular = specularStrength * spec * lightColor;

// 	vec3 result = (ambient + diffuse + specular) * objectColor;
// 	FragColor = vec4(result, 1.0);
// }


struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;    
	float shininess;
}; 

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragPosition;  
in vec3 objectNormal;  

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffuse 
	vec3 norm = normalize(objectNormal);
	vec3 lightDir = normalize(light.position - fragPosition);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// specular
	vec3 viewDir = normalize(viewPos - fragPosition);
	vec3 reflectDir = reflect(-lightDir, norm);  
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);  
		
	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
}
