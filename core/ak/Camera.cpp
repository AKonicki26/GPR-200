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

        auto getKeyPressed = [&](int key) -> bool {
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
        glm::vec3 front;
        front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        front.y = sin(glm::radians(mPitch));
        front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
        mLocalForward = glm::normalize(front);

        mLocalRight = glm::normalize(glm::cross(mLocalForward, mWorldUp));
        mLocalUp = glm::cross(mLocalRight, mLocalForward);
    }

    glm::mat4 Camera::getView() const {
        return glm::lookAt(mPosition, mPosition + mLocalForward, mLocalUp);
    }

    void Camera::processMouseMovement(double xOffset, double yOffset) {
        xOffset *= CAMERA_SENSITIVITY;
        yOffset *= CAMERA_SENSITIVITY;
        mYaw += xOffset;
        mPitch += yOffset;

        if (mPitch > 89.0f)
            mPitch = 89.0f;
        if (mPitch < -89.0f)
            mPitch = -89.0f;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateLocalAngles();
    }

    void Camera::processMouseScroll(double yOffset) {
        mZoom -= (float)yOffset;
        if (mZoom < MAX_ZOOM)
            mZoom = MAX_ZOOM;
        if (mZoom > MIN_ZOOM)
            mZoom = MIN_ZOOM;
    }
} // ak