#pragma once
#ifndef GL_MODEL_H
#define GL_MODEL_H

#include "glhelper.h"
#include "model.h"
#include "camera.hpp"
#include "shader.h"

//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


//camera
Camera camera
{
    glm::vec3(0.0f, 0.0f, 10.0f),glm::vec3(0.0f, 0.0f, -1.0f)
};

void scroll_callback2(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

class gl_model
{
private:
    GLFWwindow* window;


    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    bool firstMouse = true;

public:
    gl_model(GLFWwindow* window)
    {
        this->window = window;

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            gl_screenWidth = width;
            gl_screenHeight = height;
            glViewport(0, 0, gl_screenWidth, gl_screenHeight);
            std::cout << "size changed, width:" << width << " height:" << height << std::endl;
            glViewport(0, 0, width, height);
        });
    };


    void processInput(GLFWwindow* window)
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        std::cout << "inputEvent:" << std::endl;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }

	void loadModel(const std::string& path)
	{
        glEnable(GL_DEPTH_TEST);

        Shader ourShader("..\\shader\\7.1_load_model.vs", "..\\shader\\7.1_load_model.fs");
        Model ourModel(path);

        glfwSetScrollCallback(window, scroll_callback2);


        while (!glfwWindowShouldClose(window))
        {
            processInput(window);

            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            ourShader.use();

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)gl_screenWidth/(float)gl_screenHeight, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            ourShader.setMat4("projection", projection);
            ourShader.setMat4("view", view);

            auto time = glfwGetTime();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f));
            model = glm::rotate(model, (float)time, glm::vec3(0.0, 1.0, 0.0));
            model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// 模型太大了，缩小一点
            ourShader.setMat4("model", model);
            ourModel.Draw(ourShader);


            glfwSwapBuffers(window);
            glfwPollEvents();
        }
	};

};

#endif
