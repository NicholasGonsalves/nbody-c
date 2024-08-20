#include <stdio.h>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Body {
    float x;
    float y;
    float mass;
    float vx;
    float vy;
    float ax;
    float ay;
};

const int dt = 60 * 60 * 24;  // 1 day
const float G = 6.67430e-11; // Gravitational constant

void update_velocity(struct Body* b) {
    b->vx += b->ax * dt;
    b->vy += b->ay * dt;
}

void update_position(struct Body* b) {
    b->x += b->vx * dt + 0.5 * b->ax * dt * dt;
    b->y += b->vy * dt + 0.5 * b->ay * dt * dt;
}

void update_acceleration_all_bodies(struct Body bodies[], int size) {
    for (int i = 0; i < size; i++) {
        // printf("Body %d\n", i);
        bodies[i].ax = 0;
        bodies[i].ay = 0;
        for (int j = 0; j < size; j++) { 
            if (i == j) { continue; }
            float dx = bodies[j].x - bodies[i].x;
            float dy = bodies[j].y - bodies[i].y;
            float dist_sq = dx * dx + dy * dy;
            float force = G * bodies[j].mass / dist_sq;
            float distance = sqrt(dist_sq);
            bodies[i].ax += force * dx / distance;
            bodies[i].ay += force * dy / distance;
        }
    }
}

void simulate(struct Body bodies[], int size) {
    update_acceleration_all_bodies(bodies, size);
    for (int i = 0; i < size; i++) {
        update_position(&bodies[i]);
        update_velocity(&bodies[i]);
    }
}

void setupViewport(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Set up orthographic projection
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

GLFWwindow* initOpenGL() {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "N-Body", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
    }

    setupViewport(800, 600);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set clear color to black
    glEnable(GL_POINT_SMOOTH); // Enable point smoothing
    glPointSize(5.0f); // Set point size

    return window;
}

void renderBodies(struct Body bodies[], int size) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); // Load the identity matrix to reset transformations
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    float scaling_factor = 3e11f;
    for (int i = 0; i < size; i++) {
        glVertex2f(bodies[i].x / scaling_factor, bodies[i].y / scaling_factor); // Scale down positions
    }
    glEnd();
    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    GLFWwindow* window = initOpenGL();
    if (!window) return -1;

    const int n = 5;

    struct Body sun = {0, 0, 1.989e30, 0, 0, 0, 0};
    struct Body mercury = {57.9e9, 0, 3.285e23, 0, 47.87e3, 0, 0};
    struct Body venus = {108.2e9, 0, 4.867e24, 0, 35.02e3, 0, 0};
    struct Body earth = {149.6e9, 0, 5.972e24, 0, 29.78e3, 0, 0};
    struct Body mars = {227.9e9, 0, 6.39e23, 0, 24.07e3, 0, 0};
    struct Body jupiter = {778.5e9, 0, 1.898e27, 0, 13.07e3, 0, 0};
    struct Body saturn = {1.434e12, 0, 5.683e26, 0, 9.68e3, 0, 0};
    struct Body uranus = {2.871e12, 0, 8.681e25, 0, 6.80e3, 0, 0};
    struct Body neptune = {4.495e12, 0, 1.024e26, 0, 5.43e3, 0, 0};
    struct Body pluto = {5.906e12, 0, 1.309e22, 0, 4.74e3, 0, 0};

    // struct Body bodies[n] = {sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, pluto};
    struct Body bodies[n] = {sun, mercury, venus, earth, mars};

    while (!glfwWindowShouldClose(window)) {
        simulate(bodies, n);
        renderBodies(bodies, n);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
   
   return 0;
}