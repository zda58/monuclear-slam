#include <vector>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glext.h>
#include <iostream>
#include <SDL2/SDL.h>
#include "mapview.h"

MapView::MapView(int width, int height) {
    this->camera = Camera();
    this->width = width;
    this->height = height;
    this->window = SDL_CreateWindow("Map", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, SDL_WINDOW_OPENGL);
    if (this->window == nullptr) {
        std::cerr << "Failed to create map window: " << SDL_GetError() << std::endl;
        exit(1);
    }
    this->context = SDL_GL_CreateContext(this->window);
    if (this->context == NULL) {
        std::cerr << "Failed to create map window context: " << SDL_GetError() << std::endl;
        exit(1);
    }
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW: %s\n", glewGetErrorString(err));
        SDL_DestroyWindow(this->window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    gluPerspective(90.0, (double)this->width / height, 0.01, 1000.0);
}

void MapView::render() {
    glLoadIdentity();
    SDL_GL_MakeCurrent(this->window, this->context);

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(this->camera.get_view_matrix()));

    std::vector<glm::vec3> vertices;
    for (float i = -1; i < 10; i += 0.1) {
        for (float j = -10; j < 10; j+= 0.1) {
            vertices.push_back(glm::vec3(i, j, 0.0f));
        }
    }

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_POINTS, 0, vertices.size());
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    SDL_GL_SwapWindow(this->window);
    SDL_GL_MakeCurrent(this->window, nullptr);
}

void MapView::clean() {
    SDL_DestroyWindow(this->window);
    SDL_GL_DeleteContext(this->context);
}