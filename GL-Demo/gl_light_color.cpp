#include "gl_light_color.h"


//������ӽ�
//Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
Camera camera{
    glm::vec3(1.0f, 2.0f, -6.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    90.0f,
    0.0f
};

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


//������ɫ�͹�����ɫ
glm::vec3 cubeColor = glm::vec3(1.0f, 0.5f, 0.31f);
glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

float lastX2 = gl_screenWidth / 2.0f;
float lastY2 = gl_screenHeight / 2.0f;
bool firstMouse2 = true;

void gl_light_color::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}


void gl_light_color_mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (firstMouse2)
    {
        lastX2 = xpos;
        lastY2 = ypos;
        firstMouse2 = false;
    }

    float xoffset = xpos - lastX2;
    float yoffset = lastY2 - ypos; // reversed since y-coordinates go from bottom to top

    lastX2 = xpos;
    lastY2 = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void gl_light_color_scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void gl_light_color::createLightSource()
{
    glViewport(0, 0, gl_screenWidth, gl_screenHeight);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,

      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f, -0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,

       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,

      -0.5f, -0.5f, -0.5f,
       0.5f, -0.5f, -0.5f,
       0.5f, -0.5f,  0.5f,
       0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f,  0.5f,
      -0.5f, -0.5f, -0.5f,

      -0.5f,  0.5f, -0.5f,
       0.5f,  0.5f, -0.5f,
       0.5f,  0.5f,  0.5f,
       0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f,  0.5f,
      -0.5f,  0.5f, -0.5f,
    };


    Shader cubeShader("..\\shader\\light_color\\1.colors.vs", "..\\shader\\light_color\\1.colors.fs");
    Shader lightShader("..\\shader\\light_color\\1.light_cube.vs", "..\\shader\\light_color\\1.light_cube.fs");

    //�������������������
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    //���涥������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //����Light��VAO��VBO���ֲ��䣻����Ҳ��3D������ĵƶ��󣬶�����ͬ��
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    //����ֻ��Ҫ�󶨵�VBO��������glVertexAttribPointer���ӣ����������������
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);   //VBO�������Ѿ����������������һ�У����Ѿ����ˣ���������Ϊ����Ŀ���ٴ���������   ��ܳ
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //��ÿ����Ⱦ����֮ǰ�����Ȼ���
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //�����Ʒ�/��ͼ����ʱ����ȷ��������ɫ��
        cubeShader.use();
        cubeShader.setVec3("objectColor", cubeColor);
        cubeShader.setVec3("lightColor", lightColor);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)gl_screenWidth /(float)gl_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        //��Ⱦ����VAO
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ͬ�����Ƶ�VAO
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        //�Ե�VAO��һЩ�ı�
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightShader.setMat4("model", model);

        //��Ⱦ��VAO
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}

void gl_light_color::createLightSource2()
{
    glViewport(0, 0, gl_screenWidth, gl_screenHeight);
    glEnable(GL_DEPTH_TEST);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(window, gl_light_color_mouse_callback);
    //glfwSetScrollCallback(window, gl_light_color_scroll_callback);

    float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    Shader cubeShader("..\\shader\\light_color\\2.2.basic_lighting.vs", "..\\shader\\light_color\\2.2.basic_lighting.fs");
    Shader lightShader("..\\shader\\light_color\\2.2.light_cube.vs", "..\\shader\\light_color\\2.2.light_cube.fs");


    //�������������������
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    //���涥������
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //���Ӷ�������
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //��������
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    //����Light��VAO��VBO���ֲ��䣻����Ҳ��3D������ĵƶ��󣬶�����ͬ��
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    //����ֻ��Ҫ�󶨵�VBO��������glVertexAttribPointer���ӣ����������������
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);   //VBO�������Ѿ����������������һ�У����Ѿ����ˣ���������Ϊ����Ŀ���ٴ���������   ��ܳ
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //��ÿ����Ⱦ����֮ǰ�����Ȼ���
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //�����Ʒ�/��ͼ����ʱ����ȷ��������ɫ��
        cubeShader.use();
        cubeShader.setVec3("objectColor", cubeColor);
        cubeShader.setVec3("lightColor", lightColor);

        lightPos.x = 1.0f + sin(glfwGetTime()) * 2.0f;
        lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

        cubeShader.setVec3("lightPos", lightPos);
        cubeShader.setVec3("viewPos", camera.Position);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)gl_screenWidth / (float)gl_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        //��Ⱦ����VAO
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ͬ�����Ƶ�VAO
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        //�Ե�VAO��һЩ�ı�
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightShader.setMat4("model", model);

        //��Ⱦ��VAO
        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);
}


void ::gl_light_color::loadModel(const std::string& path)
{
    glViewport(0, 0, gl_screenWidth, gl_screenHeight);

    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetCursorPosCallback(window, gl_light_color_mouse_callback);
    glfwSetScrollCallback(window, gl_light_color_scroll_callback);
    // 
    //stbi_set_flip_vertically_on_load(true);

    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("..\\shader\\7.1_load_model.vs", "..\\shader\\7.1_load_model.fs");

    // load models
    // -----------
    Model ourModel(path);

    //camera.MovementSpeed = 50.0f;

        // lighting
    glm::vec3 modelPos(0.5f, 0.0f, 0.5f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ourShader.use();


        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)gl_screenWidth/(float)gl_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);



        auto time = glfwGetTime();
        //modelPos.x = 1.0f + sin(time) * 2.0f;
        //modelPos.y = sin(time / 2.0f) * 1.0f;

        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, modelPos * (float)sin(time));
        model = glm::translate(model, glm::vec3(0.0f));

        model = glm::rotate(model, (float)time, glm::vec3(0.0, 1.0, 0.0));
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// ģ��̫���ˣ���Сһ��
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}