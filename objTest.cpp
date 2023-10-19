// Making an object to understand the basics of OpenGL

#include <Angel.h>

// Define initial angle of rotation.
GLfloat theta = 0.0;
// Location to update the rotation angle in the shader.
GLint thetaLoc;
// Number of vertices for the triangle
const int NUMVERTICES = 3;

void init()
{
    vec2 points[NUMVERTICES] = {
        vec2(0.0, 1.0),
        vec2(-1.0, -1.0),
        vec2(1.0, -1.0),
    };

    //***********************************

    /*The following chunk of code creates a vertex array
    object and sets it as the current/active one*/
    // Vertex array object stores states of vertices.
    GLuint vao[1];
    // Generate a vertex array object.
    glGenVertexArrays(1, vao);
    // Make it the active vertex array object.
    glBindVertexArray(vao[0]);

    /*The following chunk of code creates a buffer to give our object to openGL */
    // Vertex buffer object stores vertices.
    GLuint buffer;
    // Generate one buffer to hold our vertex data in GPU memory.
    glGenBuffers(1, &buffer);
    // Make it the active buffer.
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Copy our vertex data to the active buffer (note: `points` has static size).
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    // Load vertex and fragment shaders and create a shader program.
    GLuint program = InitShader("vshader.glsl", "fshader.glsl");
    // Use the just-created shader program.
    glUseProgram(program);

    // Get the location of the vertex position attribute in the vertex shader.
    GLuint loc = glGetAttribLocation(program, "vPosition");
    // Enable this attribute.
    glEnableVertexAttribArray(loc);
    // Describe how to interpret our vertex buffer to OpenGL.
    glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    // Get the location of the rotation angle in the shader.
    thetaLoc = glGetUniformLocation(program, "uTheta");

    // Set the clear color to black.
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //***************************************
}

void display()
{
    // Clear the color buffer.
    glClear(GL_COLOR_BUFFER_BIT);
    // Set the rotation angle in the shader.
    glUniform1f(thetaLoc, theta);

    // Draw the triangle using a triangle.
    glDrawArrays(GL_TRIANGLE_FAN, 0, NUMVERTICES);

    // Swap the front and back buffers (double buffering).
    glutSwapBuffers();
}

// Updates the object shape?
void idle()
{
    // Increment the rotation angle.
    theta += 0.01;
    // Redraw the scene.
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 033: // Escape key (in octal)
        // Close the program.
        exit(EXIT_SUCCESS);
        break;
    case 'e': // 'e' key
        // Stop calling the idle function, stops the animation.
        glutIdleFunc(0);
        break;
    case 's': // 's' key
        // Start calling the idle function, starts the animation.
        glutIdleFunc(idle);
        break;
    }
}

int main(int argc, char **argv)
{
    //**********************************
    // Initialize GLUT: The OpenGL Utility Toolkit.
    glutInit(&argc, argv);
    // Define display mode: RGBA color and double buffering.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    // Set the window's initial width and height.
    glutInitWindowSize(512, 512);

    // Check if the version is 3.2 (if using freeglut).
    glutInitContextVersion(3, 2);
    // Set OpenGL context to core profile (if using freeglut).
    glutInitContextProfile(GLUT_CORE_PROFILE);

    // Create a window with a title.
    glutCreateWindow("A Triangle");

    // Initialize GLEW: The OpenGL Extension Wrangler Library.
    glewInit();

    // Call our initialization function.
    init();

    // Register our display function, so GLUT knows how to redraw the scene.
    glutDisplayFunc(display);
    // Register our keyboard function, so GLUT can handle keyboard input.
    glutKeyboardFunc(keyboard);

    // Enter GLUT's main loop.
    glutMainLoop();
    //*************************************

    return 0;
}