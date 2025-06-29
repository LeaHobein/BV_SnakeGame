#version 430 core
// Basic fragment shader
// Simply forwarding the fragment color
// from the last pipeline stage to the next

// Edited by Merijam Gotzes, 15.03.2024

// User defined in variable
// Color from previous pipeline stage
// Matches the out variable name of the vertex shader
in vec4 color;
// User defined out variable, fragment color
out vec4 FragColor;

void main (void)
{
	// The input fragment color is forwarded
	// to the next pipeline stage
	FragColor = color;
}
