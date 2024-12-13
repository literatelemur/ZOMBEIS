#include <GL/glut.h>


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int windowWidth = 1920;
    int windowHeight = 1080;
    gluOrtho2D(0, windowWidth, windowHeight, 0);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw a rectangle in pixel coordinates
    glColor3f(1.0f, 0.0f, 0.0f); // Red color
    glBegin(GL_QUADS);
        glVertex2i(100, 100); // Bottom-left
        glVertex2i(200, 100); // Bottom-right
        glVertex2i(200, 200); // Top-right
        glVertex2i(100, 200); // Top-left
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    // int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    int windowWidth = 1920;
    int windowHeight = 1080;
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("2D Drawing with Pixels");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glutDisplayFunc(display);
    glutMainLoopEvent();
    return 0;
}
