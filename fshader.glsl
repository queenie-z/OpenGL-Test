#version 150

// Input color from the vertex shader.
in vec4 vColor;
// Output color that will be used for the fragment.
out vec4  fColor;

void main()
{
    // Directly pass the input color to the output.
    fColor = vColor;
}
