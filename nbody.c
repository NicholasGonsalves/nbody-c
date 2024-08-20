#include <stdio.h>
#include <math.h>

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
const float G = 6.67430 * 0.00000000001;

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
        for (int j = 0; j < size; j++) { 
            if (i == j) { continue; }
            float dx = bodies[j].x - bodies[i].x;
            float dy = bodies[j].y - bodies[i].y;
            float dist_sq = dx * dx + dy * dy;
            float force = G * bodies[j].mass / dist_sq;
            float distance = pow(dist_sq, 0.5);
            bodies[i].ax += force * dx / distance;
            bodies[i].ay += force * dy / distance;
        }
    }
}

void simulate(struct Body bodies[], int size) {
    update_acceleration_all_bodies(bodies, 10);
    for (int i = 0; i < size; i++) {
        update_position(&bodies[i]);
        update_velocity(&bodies[i]);
    }
}

void print_bodies(struct Body bodies[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Body %d:\n", i);
        printf("  Position: (%.2f, %.2f)\n", bodies[i].x, bodies[i].y);
        printf("  Mass: %.2e\n", bodies[i].mass);
        printf("  Velocity: (%.2f, %.2f)\n", bodies[i].vx, bodies[i].vy);
        printf("  Acceleration: (%.2f, %.2f)\n", bodies[i].ax, bodies[i].ay);
        printf("\n");
    }
}

int main() {
    struct Body sun = {0, 0, 1.989 * 10e30, 0, 0, 0, 0};
    struct Body mercury = {57.9e9, 0, 3.285 * 10e23, 0, 47.87e3, 0, 0};
    struct Body venus = {108.2e9, 0, 4.867 * 10e24, 0, 35.02e3, 0, 0};
    struct Body earth = {149.6e9, 0, 5.972 * 10e24, 0, 29.78e3, 0, 0};
    struct Body mars = {227.9e9, 0, 6.39 * 10e23, 0, 24.07e3, 0, 0};
    struct Body jupiter = {778.5e9, 0, 1.898 * 10e27, 0, 13.07e3, 0, 0};
    struct Body saturn = {1.434e12, 0, 5.683 * 10e26, 0, 9.68e3, 0, 0};
    struct Body uranus = {2.871e12, 0, 8.681 * 10e25, 0, 6.80e3, 0, 0};
    struct Body neptune = {4.495e12, 0, 1.024 * 10e26, 0, 5.43e3, 0, 0};
    struct Body pluto = {5.906e12, 0, 1.309 * 10e22, 0, 4.74e3, 0, 0};

    struct Body bodies[10] = {sun, mercury, venus, earth, mars, jupiter, saturn, uranus, neptune, pluto};

    for (int i; i < 1000000; i++) {
        simulate(bodies, 10);
    }

    print_bodies(bodies, 10);
   
   return 0;
}