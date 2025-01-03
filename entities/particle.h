#ifndef GAME_ENGINE_PARTICLE_H
#define GAME_ENGINE_PARTICLE_H

#include <glfw/glfw3.h>
#include "../shape.h"
#include "../shader-compiler.h"
#include "cube.h"
#define PARTICLE_SPEED 0.2f
#define PARTICLE_DURATION 1

class Particle : public Shape {
private:
    glm::vec3 direction;
    Shape* particle;
    float initializationTime;
public:
    Particle(float initTime, glm::vec3 position, glm::vec3 direction) {
        this->position = position;
        this->direction = direction;
        this->initializationTime = initTime;
        this->particle = new Cube(this->position);
        this->particle->initializeBuffers();
        this->particle->setDilation(0.0005);
    }

    void update(float deltaTime, Shader* shader) override {
        if(abs(initializationTime - glfwGetTime()) >= PARTICLE_DURATION) {
            this->setDestroyed();
        }
        this->position += this->direction * deltaTime * PARTICLE_SPEED;
        this->particle->setPosition(this->position);
        this->particle->update(deltaTime, shader);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, this->position);
        model = glm::scale(model, glm::vec3(this->particle->getDilation()));
        shader->setMat4("model", model);
    }

    void draw() override {
        this->particle->draw();
    }
};

#endif //GAME_ENGINE_PARTICLE_H