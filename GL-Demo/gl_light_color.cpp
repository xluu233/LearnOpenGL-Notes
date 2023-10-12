#include "gl_light_color.h"


//摄像机视角
//Camera camera{ glm::vec3(0.0f, 0.0f, 3.0f) };
Camera camera{
    glm::vec3(1.0f, 2.0f, -6.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    90.0f,
    0.0f
};

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


//物体颜色和光照颜色
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

    //创建被照物体的正方体
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    //缓存顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //连接顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);



    //配置Light的VAO（VBO保持不变；对于也是3D立方体的灯对象，顶点相同）
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    //我们只需要绑定到VBO（将其与glVertexAttribPointer链接），无需填充它即可
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);   //VBO的数据已经包含了我们所需的一切（它已经绑定了，但是我们为教育目的再次这样做）   ？艹
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        //在每次渲染迭代之前清除深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //设置制服/绘图对象时，请确保激活着色器
        cubeShader.use();
        cubeShader.setVec3("objectColor", cubeColor);
        cubeShader.setVec3("lightColor", lightColor);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)gl_screenWidth /(float)gl_screenHeight, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model(1.0f);
        cubeShader.setMat4("projection", projection);
        cubeShader.setMat4("view", view);
        cubeShader.setMat4("model", model);

        //渲染物体VAO
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 同样绘制灯VAO
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        //对灯VAO做一些改变
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightShader.setMat4("model", model);

        //渲染灯VAO
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


    //创建被照物体的正方体
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(cubeVAO);

    //缓存顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //连接顶点数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //法线数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



    //配置Light的VAO（VBO保持不变；对于也是3D立方体的灯对象，顶点相同）
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    //我们只需要绑定到VBO（将其与glVertexAttribPointer链接），无需填充它即可
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);   //VBO的数据已经包含了我们所需的一切（它已经绑定了，但是我们为教育目的再次这样做）   ？艹
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
        //在每次渲染迭代之前清除深度缓冲
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //设置制服/绘图对象时，请确保激活着色器
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

        //渲染物体VAO
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 同样绘制灯VAO
        lightShader.use();
        lightShader.setMat4("projection", projection);
        lightShader.setMat4("view", view);
        //对灯VAO做一些改变
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightShader.setMat4("model", model);

        //渲染灯VAO
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
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// 模型太大了，缩小一点
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}