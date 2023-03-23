// std lib
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

// glut lib
#include <GL/glut.h>

// Librairie de notre projet
#include <HypoGl/Arrow3D.h>

// Includes locaux
#include "Turtle.h"

bool leftMousePressed;
int anglex, angley, x, y, xold, yold;
float zoom = 1.f;

/* Prototypes */
void Loop();
void updateDeltaTime();
void Keyboard(unsigned char touche, int x, int y);
void KeyboardSpe(int touche, int x, int y);
void Reshape(int x, int y);
void Mouse(int bouton, int etat, int x, int y);
void MouseMotion(int x, int y);

/* Variables globales */

// Axes
Arrow3D axeX = Arrow3D(Transform(Vector3f(), Vector3f(0.f, 0.f, -90.f), {1.f, 4.f, 1.f}));
Arrow3D axeY = Arrow3D(Transform(Vector3f(), Vector3f(),               {1.f, 4.f, 1.f}));
Arrow3D axeZ = Arrow3D(Transform(Vector3f(), Vector3f(90.f, 0.f, 0.f), {1.f, 4.f, 1.f}));
bool axesShown = true;

// Une instance de tortue
Turtle turtle;

// Gestion du temps
auto lastTime = std::chrono::high_resolution_clock::now();
float deltaTime = 0.f;

// Objets de la scène
std::vector<Object3D*> sceneObjects{&axeX, &axeY, &axeZ, &turtle};

// Lumière ambiante
float ambiantStrength = 2.f;
float ambiantColor[] = { ambiantStrength * 1.f, ambiantStrength * 1.f, ambiantStrength * 1.f, 1.f};

// Lumière ponctuelle
float spotLightStrength = 100.f;
float spotLightPos[] = {0.f, 20.f, 0.f, 1.f};
float spotLightAmb[] = {0.f, 0.f, 0.f, 1.f};
float spotLightSpec[] = {1.f * spotLightStrength, 1.f * spotLightStrength, 1.f * spotLightStrength, 1.f};
float spotLightDiff[] = {1.f * spotLightStrength, 1.f * spotLightStrength, 1.f * spotLightStrength, 1.f};

int main(int argc,char **argv)
{
    // Initialisation de glut et de la fenetre
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Animation d'une tortue");

    // Initialisation de OpenGL
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    // Lumières
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambiantColor);

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, spotLightDiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, spotLightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, spotLightAmb);

    // Callbacks de glut
    glutDisplayFunc(Loop);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(KeyboardSpe);
    glutReshapeFunc(Reshape);
    glutMouseFunc(Mouse);
    glutMotionFunc(MouseMotion);

    // Initialisation des variables globales
    axeX.setTexture(&Texture::Red);
    axeY.setTexture(&Texture::Green);
    axeZ.setTexture(&Texture::Blue);

    glutMainLoop();

    return EXIT_SUCCESS;
}

void Loop()
{
    // Couleur du background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    // Gestion de la caméra
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-20.0 / zoom, 20.0 / zoom, -10.0 / zoom, 30.0 / zoom, -20.0 / zoom, 20.0 / zoom);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glRotatef(angley, 1.f, 0.f, 0.f);
    glRotatef(anglex, 0.f, 1.f, 0.f);

    // Mise à jour de la position de la lumière
    glLightfv(GL_LIGHT0, GL_POSITION, spotLightPos);

    // Update des objets de la scène
    for(auto& o : sceneObjects) { o->update(deltaTime); }

    // Drawcalls des objets de la scène
    for(const auto& o : sceneObjects) { o->draw(); }

    glFlush();
    glutSwapBuffers();

    // Pour ne pas trop surcharger un coeur du processeur
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(5ms);

    // Mettre à jour le temps écoulé depuis le dernier tour de boucle
    updateDeltaTime();

    glutPostRedisplay();
}

void updateDeltaTime()
{
    auto now = std::chrono::high_resolution_clock::now();
    deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count() / 1000.f;
    lastTime = now;
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'z': // Zoomer
        zoom += 0.01;
        break;
    case 'Z': // Dézoomer
        zoom -= 0.01;
        break;
    case ' ': // Sauter
        turtle.jump();
        break;
    case 'r': // Monter/cacher les axes
        axesShown = !axesShown;

        axeX.setVisible(axesShown);
        axeY.setVisible(axesShown);
        axeZ.setVisible(axesShown);
        break;
    case 'p': // Mode faces
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        break;
    case 'f': // Mode wireframe
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        break;
    case 'q' : // Quitter le programme
        exit(0);
        break;
    }
}

// Gestion de la rotation de la caméra avec les flèches directionnelles
void KeyboardSpe(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_UP :
        angley = angley - 1;
        break;
    case GLUT_KEY_DOWN :
        angley = angley + 1;
        break;
    case GLUT_KEY_RIGHT :
        anglex = anglex + 1;
        break;
    case GLUT_KEY_LEFT :
        anglex = anglex - 1;
        break;
    }
}

// Gérer le redimensionnement de la fenêtre
void Reshape(int x, int y)
{
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // LMB pressed
    {
        leftMousePressed = true;
        xold = x;
        yold = y;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) // LBM released
        leftMousePressed = false;
}

void MouseMotion(int x, int y)
{
    if (leftMousePressed)
    {
        anglex = anglex + (x - xold);
        angley = angley + (y - yold);

        xold = x;
        yold = y;
    }
}
