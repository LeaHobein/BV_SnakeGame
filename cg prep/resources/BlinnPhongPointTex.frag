#version 430 core

// Algorithm based on algorithmen from
// Sellers, Graham, Wright, Richard S., Haemel, Nicholas (2014).
// OpenGL Super Bible. 6th edition. Addison Wesley.

// Point light source
// To use this shader set for generating a directional light source,
// put the light source very far away from the objects to be lit

// Puts a texture on the surfaces of the object

// Edited by Merijam Gotzes, 15.03.2024

// Parameters of light source as uniform variables from application
layout (location = 4) uniform vec4 lightSourceAmbient;
layout (location = 5) uniform vec4 lightSourceDiffuse;
layout (location = 6) uniform vec4 lightSourceSpecular;
// Material parameters as uniform variables
layout (location = 7) uniform vec4 materialEmission;
layout (location = 8) uniform vec4 materialAmbient;
layout (location = 9) uniform vec4 materialDiffuse;
layout (location = 10) uniform vec4 materialSpecular;
layout (location = 11) uniform float materialShininess;

// predefined type for texture usage
layout (binding = 0) uniform sampler2D tex;

//in vec4 vColor;
out vec4 FragColor;

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
    vec2 vUV;
} fs_in;

void main(void)
{
    vec3 emissiv = vec3(materialEmission);
    vec3 ambient = vec3(materialAmbient) * vec3(lightSourceAmbient);
    vec3 diffuseAlbedo = vec3(materialDiffuse) * vec3(lightSourceDiffuse);
    vec3 specularAlbedo = vec3(materialSpecular) * vec3(lightSourceSpecular);

    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);
    vec3 H = normalize(L + V);

    // Compute the diffuse and specular components for each fragment
    vec3 diffuse = max(dot(N, L), 0.0) * diffuseAlbedo;
    vec3 specular = pow(max(dot(N, H), 0.0), materialShininess) * specularAlbedo;

    // Write final color to the framebuffer
    FragColor = (vec4(emissiv + ambient + diffuse, 1.0) * texture(tex, fs_in.vUV)) + vec4(specular, 1.0);
}

