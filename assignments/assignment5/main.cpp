#include <stdio.h>
#include <math.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "./../../core/ak/Shader.h"
#include "ak/Camera.h"
#include "ak/Texture2D.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#define NUMBER_OF_CUBES 12


const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;
const float FOV = 45.0f;

void mouse_callback( GLFWwindow* window, double xpos, double ypos);
void scroll_callback( GLFWwindow* window, double xoffset, double yoffset);

float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

ak::Camera camera;

glm::vec3 lightPos = glm::vec3(0.0f, 0.5f, 0.0f);
glm::vec3 lightColor;
float ambientLight = 0.5;
float diffuseLight = 0.25;
float specularLight = 0.75;
float shininess = 34;

#define MIN_SHININESS 2
#define MAX_SHININESS 1024

void renderUiWindows();

const std::string ASSETS_PATH = "./assets/";
const std::string SHADER_PATH = ASSETS_PATH + "Shaders/";
const std::string TEXTURE_PATH = ASSETS_PATH + "Textures/";

int main() {
    assert(NUMBER_OF_CUBES > 0);
    assert((int)NUMBER_OF_CUBES == NUMBER_OF_CUBES);
    printf("Initializing...\n");
    if (!glfwInit()) {
        printf("GLFW failed to init!\n");
        return 1;
    }
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Square", NULL, NULL);
    if (window == nullptr) {
        printf("GLFW failed to create window\n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD failed to load GL headers\n");
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();

    camera = ak::Camera(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Vertex data
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    unsigned int VAO, VBO, EBO;

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Generate and bind EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attributes
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    /*
    // Color
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

*/
    // Texture Coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);


    ak::Shader basicCubeShader("./assets/Shaders/vertexShader.vert", "./assets/Shaders/fragShader.frag");
    ak::Shader lightShader((SHADER_PATH + "lightShader.vert.glsl").c_str(), (SHADER_PATH + "fragShader.frag.glsl").c_str());

    ak::Texture2D brickTexture("./assets/Textures/Bricks.png", GL_NEAREST, GL_REPEAT);
    ak::Texture2D sharkTexture("./assets/Textures/shark.png", GL_LINEAR, GL_REPEAT);

    std::random_device rd;
    std::mt19937 gen(rd());
    auto getRandomCubePosition = [&gen](float minPos, float maxPos) -> glm::vec3 {
        std::uniform_real_distribution<float> dist(minPos, maxPos);
        return glm::vec3(dist(gen), dist(gen), dist(gen));
    };

    glm::vec3 cubePositions[NUMBER_OF_CUBES];
    for (int i = 0; i < NUMBER_OF_CUBES; i++) {
        cubePositions[i] = getRandomCubePosition(-2,8);
    }

    float lastFrameTime = 0;
    float deltaTime = 0;

    glfwSetCursorPosCallback(camera.getWindow(), mouse_callback);
    glfwSetScrollCallback(camera.getWindow(), scroll_callback);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        cubePositions[0] = lightPos;

        //Clear framebuffer
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        auto time = (float)glfwGetTime();
        deltaTime = time - lastFrameTime;
        lastFrameTime = time;

        camera.Update(deltaTime);

        glm::mat4 view = camera.getView();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.getZoom()), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 1000.0f);

        // Draw the light source cube
        lightShader.use();

        lightShader.setValue("view", view);
        lightShader.setValue("uTime", time);
        lightShader.setValue("projection", projection);

        lightShader.setValue("ambientStrength", ambientLight);
        lightShader.setValue("diffuseStrength", diffuseLight);
        lightShader.setValue("specularStrength", specularLight);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
        model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        lightShader.setValue("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // Draw the rest of the cubes
        basicCubeShader.use();

        brickTexture.Bind(GL_TEXTURE0);
        basicCubeShader.setValue("texture1", 0);
        sharkTexture.Bind(GL_TEXTURE1);
        basicCubeShader.setValue("texture2", 1);

        basicCubeShader.setValue("view", view);
        basicCubeShader.setValue("uTime", time);
        basicCubeShader.setValue("projection", projection);

        for (int i = 1; i < std::end(cubePositions) - std::begin(cubePositions); ++i) {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            basicCubeShader.setValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        renderUiWindows();

        glfwSwapBuffers(window);
    }

    // Clean up resources (optional, but good practice)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    printf("Shutting down...\n");
    glfwTerminate();
    return 0;
}

// Stolen directly from the Camera class version of the code documentation
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.processMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.processMouseScroll(static_cast<float>(yoffset));
}

void renderUiWindows() {
    ImGui_ImplGlfw_NewFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Settings");

    ImGui::DragFloat3("Light Position", &lightPos.x, 0.1f);
    ImGui::ColorEdit3("Light Color", &lightColor.r);
    ImGui::SliderFloat("Ambient", &ambientLight, 0.0f, 1.0f);
    ImGui::SliderFloat("Diffuse", &diffuseLight, 0.0f, 1.0f);
    ImGui::SliderFloat("Specular", &specularLight, 0.0f, 1.0f);
    ImGui::SliderFloat("Shininess", &shininess, MIN_SHININESS, MAX_SHININESS);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}