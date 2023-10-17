#pragma once
#ifndef GL_MODEL_H
#define GL_MODEL_H

#include "glhelper.h"
#include "model.h"
#include "camera.hpp"
#include "shader.h"

class gl_model
{
private:
    GLFWwindow* window;

public:
    gl_model(GLFWwindow* window)
    {
        this->window = window;
    };

	void loadModel(const std::string& path)
	{
        glEnable(GL_DEPTH_TEST);

        Shader ourShader("..\\shader\\7.1_load_model.vs", "..\\shader\\7.1_load_model.fs");
        Model ourModel(path);


        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetCursorPosCallback(window, mouse_callback);
        glfwSetScrollCallback(window, scroll_callback);

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
