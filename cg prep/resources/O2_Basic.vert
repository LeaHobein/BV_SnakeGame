#version 430 core
// Basic vertex shader that performs geometric transformations

// Edited by Merijam Gotzes, 15.03.2024

// User defined in variables
// Position and color of vertex
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 vertexColor;
// Definition of uniforms
// Projection and model-view matrix
layout (location = 0) uniform mat4 projectionMatrix;
layout (location = 1) uniform mat4 modelviewMatrix;

// User defined out variable
// Color of the vertex
out vec4 color;

void main(void) {
// Calculation of the model-view-perspective transform
gl_Position = projectionMatrix * modelviewMatrix * vec4(vertexPosition, 1.0);
// The color information is forwarded in homogeneous coordinates
color = vec4(vertexColor, 1.0);
}
