#version 330 core

in vec3 color;
in vec3 Normal;
in vec3 currentPos;

out vec4 FragColor;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - currentPos);

    float diffuse = max(dot(normal, lightDir), 0.0f);
    float specularLight = 0.5f;
    vec3 viewDir = normalize(camPos - currentPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectDir), 0.0f), 8);
    float specular = specAmount * specularLight;

    FragColor = vec4(color, 1.0f) * lightColor * (diffuse + ambient + specular);
}