//
// Created by anne.konicki on 10/4/2024.
//

#include "Camera.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "GLFW/glfw3.h"

#define SPRINT_SPEED 0.65f
#define WALK_SPEED 0.25f

namespace ak {
    Camera::Camera() {
        updateLocalAngles();
    }

    void Camera::processKeyboardInput(float deltaTime) {

        auto getKeyPressed = [&](int key) {
            return glfwGetKey(mWindow, key) == GLFW_PRESS;
        };

        if (getKeyPressed(GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(mWindow, true);

        // Sprint function
        mSpeed = glfwGetKey(mWindow, GLFW_KEY_LEFT_SHIFT) ? SPRINT_SPEED : WALK_SPEED;
        mSpeed *= deltaTime;

        if (getKeyPressed(GLFW_KEY_W))
            mPosition += mSpeed * mLocalForward;
        if (getKeyPressed(GLFW_KEY_S))
            mPosition -= mSpeed * mLocalForward;
        if (getKeyPressed(GLFW_KEY_A))
            mPosition -= glm::normalize(glm::cross(mLocalForward, mLocalUp)) * mSpeed;
        if (getKeyPressed(GLFW_KEY_D))
            mPosition += glm::normalize(glm::cross(mLocalForward, mLocalUp)) * mSpeed;


    }

    void Camera::Update(float deltaTime) {
        processKeyboardInput(deltaTime);
    }

    void Camera::updateLocalAngles() {
        mLocalRight = glm::normalize(glm::cross(mWorldUp, mPosition - mTarget));
        mLocalUp = glm::cross(mPosition - mTarget, mLocalRight);;
    }

    glm::mat4 Camera::getView() const {
        return glm::lookAt(mPosition, mPosition + mLocalForward, mLocalUp);

        /*
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        glm::mat4 view;
        view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
        return view;
        */
    }
} // ak