#version 430 core
// Algorithm based on algorithm from
// Sellers, Graham, Wright, Richard S., Haemel, Nicholas (2014).
// OpenGL Super Bible. 6th edition. Addison Wesley.

// Point light source
// To use this shader set for generating a directional light source,
// put the light source very far away from the objects to be lit

// Edited by Merijam Gotzes, 15.03.2024

// User defined in variables
// Position, color and normals of vertex
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

// Definition of uniforms
// Projection, model-view, transpose inverse model view matrix ans light source
layout (location = 0) uniform mat4 projectionMatrix;
layout (location = 1) uniform mat4 modelviewMatrix;
layout (location = 2) uniform mat4 modelviewITMatrix;
layout (location = 3) uniform vec4 lightPosition;

// User defined out variable
// Outputs from vertex shader
out VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} vs_out;

void main(void)
{

    // Calculate view-space coordinate
    vec4 P = modelviewMatrix * vec4(vertexPosition, 1.0);

    // Calculate normal in view-space
    // Matrix has to be the transpose inverse of mvMatrix
    // for transformation of normals!
    // The forth normal coordinate component is
    // 0.0f in homogenous coordinates
    // N is NOT equal to mat3(modelviewITMatrix) * vertexNormal;
    vs_out.N = vec3(modelviewITMatrix * vec4(vertexNormal, 0.0f));

    // Calculate light vector
    vs_out.L = lightPosition.xyz - P.xyz;

    // Calculate view vector
    vs_out.V = -P.xyz;

    // Calculate the clip-space position of each vertex
    gl_Position = projectionMatrix * P;
}


