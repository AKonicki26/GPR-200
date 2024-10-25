#include <stdio.h>
#include <math.h>
#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "./../../core/ak/Shader.h"
#include "ak/Texture2D.h"

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

int main() {
    printf("Initializing...\n");
    if (!glfwInit()) {
        printf("GLFW failed to init!\n");
        return 1;
    }
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Square", NULL, NULL);
    if (window == NULL) {
        printf("GLFW failed to create window\n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGL(glfwGetProcAddress)) {
        printf("GLAD failed to load GL headers\n");
        return 1;
    }

    // Vertex data
    float vertices[] = {
            // X,   Y,   Z,    R,  G,   B,    A,   TexX,  TexY
            0.5f, 0.5f, 0.0f, 1.0, 0.0, 0.0, 1.0, 1.0f, 1.0f,   // Top Right
            0.5f, -0.5f, 0.0f, 0.0, 1.0, 0.0, 1.0, 1.0f, 0.0f,  // Bottom Right
            -0.5f, -0.5f, 0.0f, 0.0, 0.0, 1.0, 1.0, 0.0f, 0.0f, // Bottom Left
            -0.5f, 0.5f, 0.0f, 0.0, 1.0, 1.0, 1.0,  0.0f, 1.0f   // Top Left
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // Color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    ak::Shader characterShader("./assets/Shaders/character.vert", "./assets/Shaders/character.frag");
    ak::Shader backgroundShader("./assets/Shaders/background.vert", "./assets/Shaders/background.frag");

    ak::Texture2D brickTexture("./assets/Textures/Bricks.png", GL_NEAREST, GL_REPEAT);
    brickTexture.Bind(GL_TEXTURE0);
    ak::Texture2D duckTexture("./assets/Textures/DuckTexture.png", GL_LINEAR, GL_REPEAT);
    duckTexture.Bind(GL_TEXTURE1);
    ak::Texture2D sharkTexture("./assets/Textures/shark.png", GL_LINEAR, GL_REPEAT);

    glEnable(GL_BLEND);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        float time = (float)glfwGetTime();
        // Clear framebuffer
        glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing happens here!

        glBindVertexArray(VAO);

        // Draw Background
        backgroundShader.use();
        backgroundShader.setValue("uTime", time);

        brickTexture.Bind(GL_TEXTURE0);
        backgroundShader.setValue("texture1", 0);
        sharkTexture.Bind(GL_TEXTURE1);
        backgroundShader.setValue("texture2", 1);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw Character
        characterShader.use();
        characterShader.setValue("uTime", time);

        duckTexture.Bind(GL_TEXTURE0);
        characterShader.setValue("_texture", 0);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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