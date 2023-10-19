#version 150

// Input vertex position from the OpenGL program.
in vec4 vPosition;

// A uniform value; remains the same for all vertices.
// Used for rotation.
uniform float uTheta;

// Output color that will be sent to the fragment shader.
out vec4 vColor;

void main()
{
  // Calculate the rotated x-coordinate using a 2D rotation matrix.
  gl_Position.x = -sin(uTheta) * vPosition.x + cos(uTheta) * vPosition.y;
  // Calculate the rotated y-coordinate using a 2D rotation matrix.
  gl_Position.y =  sin(uTheta) * vPosition.y + cos(uTheta) * vPosition.x;
  // Set the z-coordinate. Here it's always 0 since we're working in 2D.
  gl_Position.z = 0.0;
  // Set the w-coordinate. Typically set to 1.0 for positions.
  gl_Position.w = 1.0;

  // Define an array of colors.
  vec4 color[4];
  color[0] = vec4(1, 0, 0, 1); // Red
  color[1] = vec4(0, 1, 0, 1); // Green
  color[2] = vec4(0, 0, 1, 1); // Blue
  color[3] = vec4(1, 1, 1, 1); // White

  // Set the output color based on the current vertex's ID.
  vColor = color[gl_VertexID];
}
