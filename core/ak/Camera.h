#include <glm/glm.hpp>

#include "GLFW/glfw3.h"

#ifndef CAMERA_H
#define CAMERA_H



namespace ak {

class Camera {
public:
    Camera();
    explicit Camera(const glm::vec3 initialPosition) : mPosition(initialPosition) { updateLocalAngles(); }
    void Update(float deltaTime);
    void updateLocalAngles();
    glm::mat4 getView() const;
    void setWindow(GLFWwindow* window) { mWindow = window; }

private:
    glm::vec3 mPosition = glm::vec3(0, 0, 3.0f);
    glm::vec3 mTarget = glm::vec3(0, 0, -1.0f);
    glm::vec3 mWorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::vec3 mLocalRight;
    glm::vec3 mLocalUp;
    glm::vec3 mLocalForward = mTarget;

    void processKeyboardInput(float deltaTime);
    void processMouseInput();

    GLFWwindow* mWindow;

    float mSpeed = 0.05f;
};

} // ak

#endif //CAMERA_H
