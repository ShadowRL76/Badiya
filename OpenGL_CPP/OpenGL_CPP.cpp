#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "dependencies/imgui/imgui.h"
#include "dependencies/imgui/imgui_impl_glfw.h"
#include "dependencies/imgui/imgui_impl_opengl3.h"

#include "common/shader.h"
#include "common/Camera.h"


//This is something you can’t change, it’s built in your graphics card. So (-1,-1) is the bottom left corner of your screen. 
// (1,-1) is the bottom right, and (0,1) is the middle top. So this triangle should take most of the screen.

// If w == 1, then the vector (x,y,z,1) is a position in space.
// If w == 0, then the vector(x, y, z, 0) is a direction.

int main()
{

    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Don't want the old OpenGL 


    // Open a window and create its OpenGL context
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> window(
        glfwCreateWindow(3840, 2160, "Graphics Engine", NULL, NULL),
        glfwDestroyWindow
    );

    if (window == NULL)
    {
        std::cerr << "Failed to open GLFW window.\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window.get()); // Initialize GLEW

    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW\n";
        return -1;
    }

    ImGui::CreateContext(); 
    ImGuiIO& io = ImGui::GetIO(); (void)io; 
    ImGui::GetIO().FontGlobalScale = 3.0f; 
    ImGui_ImplGlfw_InitForOpenGL(window.get(), true); 
    ImGui_ImplOpenGL3_Init("#version 330");
    Camera cam = camera(window.get()); 


    static const GLfloat gVertexBufferDataSquareOne[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    static const GLfloat gVertexBufferDataTriangle[] = {
       -1.0f, -1.0f, 0.0f,
       1.0f, -1.0f, 0.0f,
       0.0f,  1.0f, 0.0f,
    };
    static const GLfloat gVertexBufferDataSquareTwo[] = {
        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f, -1.0f, // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, // triangle 2 : end
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };

    static const GLfloat gColorBufferData[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };

    GLuint VertexArrayID{};  
    glGenVertexArrays(1, &VertexArrayID);  
    glBindVertexArray(VertexArrayID);  

    GLuint vertexBufferSquareOne{};
    glGenBuffers(1, &vertexBufferSquareOne);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferSquareOne);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferDataSquareOne), gVertexBufferDataSquareOne, GL_STATIC_DRAW);

    GLuint vertexBufferTriangle{};
    glGenBuffers(1, &vertexBufferTriangle);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferTriangle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferDataTriangle), gVertexBufferDataTriangle, GL_STATIC_DRAW);

    GLuint vertexBufferSquareTwo{};
    glGenBuffers(1, &vertexBufferSquareTwo);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferSquareTwo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gVertexBufferDataSquareTwo), gVertexBufferDataSquareTwo, GL_STATIC_DRAW);


    GLuint colorbuffer{};
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gColorBufferData), gColorBufferData, GL_STATIC_DRAW);

    GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

    glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);



    glm::vec3 translateSquareOne(-3.0f, 0.0f, 0.0f); 
    glm::vec3 translateSquareTwo(6.0f, 0.0f, 0.0f);
    glm::vec3 translateTriangle(2.0f, 0.0f, 0.0f);



    do {

        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programID);

        ImGui_ImplOpenGL3_NewFrame(); 
        ImGui_ImplGlfw_NewFrame(); 
        ImGui::NewFrame(); 





        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);
        int width, height; 

        glfwGetFramebufferSize(window.get(), &width, &height); 

        GLuint MatrixIDS = glGetUniformLocation(programID, "MVP"); 


        cam.Controls(window.get()); 
        cam.GetProjectionMatrix();
        cam.GetViewMatrix();

        // creates a model matrix. This matrix is used to position, 
        // scale, and rotate objects in the world. By default, it's the identity matrix (1.0f), 
        // which means no transformation. If you wanted to move or rotate your object, you would modify this matrix.
        glm::mat4 ModelSquareOne = glm::mat4(1.0f);
        ModelSquareOne = glm::translate(ModelSquareOne, translateSquareOne);
        glm::mat4 MVPOne = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareOne; // Combine them into the MVP matrix      

        // Get the location of the MVP uniform
        glm::mat4 ModelTriangle = glm::mat4(1.0f);
        ModelTriangle = glm::translate(ModelTriangle, translateTriangle);
        glm::mat4 MVPTwo = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelTriangle; // Combine them into the MVP matrix     

        glm::mat4 ModelSquareTwo = glm::mat4(1.0f);
        ModelSquareTwo = glm::translate(ModelSquareTwo, translateSquareTwo);
        glm::mat4 MVPThree = cam.GetProjectionMatrix() * cam.GetViewMatrix() * ModelSquareTwo; // Combine them into the MVP matrix   

        // Send the MVP matrix to the shader
        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPOne));

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferSquareOne);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size 
            GL_FLOAT,           // type 
            GL_FALSE,           // normalized?  
            0,                  // stride 
            (void*)0            // array buffer offset 
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);  // 12*3 indices starting at 0 -> 12 triangles -> 6 squares 


        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPTwo));

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferTriangle);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size 
            GL_FLOAT,           // type  
            GL_FALSE,           // normalized?   
            0,                  // stride 
            (void*)0            // array buffer offset 
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 3);  // 12*3 indices starting at 0 -> 12 triangles -> 6 squares  

        glUniformMatrix4fv(MatrixIDS, 1, GL_FALSE, glm::value_ptr(MVPThree));

        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBufferSquareTwo);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size 
            GL_FLOAT,           // type  
            GL_FALSE,           // normalized?   
            0,                  // stride 
            (void*)0            // array buffer offset 
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3);  // 12*3 indices starting at 0 -> 12 triangles -> 6 squares  


        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        ImGui::Begin("My Window");
        ImGui::Text("Hello, world!");
        ImGui::SliderFloat3("Translate Square One", &translateSquareOne.x, -20.0f, 20.0f);
        ImGui::SliderFloat3("Translate Square Two", &translateSquareTwo.x, -20.0f, 20.0f);
        ImGui::SliderFloat3("Translate Triangle", &translateTriangle.x, -20.0f, 20.0f);
        if(ImGui::Button("Reset"))
		{
			translateSquareOne = glm::vec3(-3.0f, 0.0f, 0.0f); 
			translateSquareTwo = glm::vec3(6.0f, 0.0f, 0.0f); 
			translateTriangle = glm::vec3(2.0f, 0.0f, 0.0f);
            cam.CameraReset(window.get()); 
		}
        if (ImGui::Button("Add Square"))
        {
            //Add a square Soon! Clean up code for this and add a draw new objects function!
        }
		if (ImGui::Button("Close Me"))
		{
			glfwSetWindowShouldClose(window.get(), true);
		}  


        ImGui::Text("FPS %f", ImGui::GetIO().Framerate);
        ImGui::Text("Application average %.3f", 1000.0f / ImGui::GetIO().Framerate);
        ImGui::End();



        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Swap buffers 
        glfwSwapBuffers(window.get());
        glfwPollEvents();

        //Enabled so gpu cant render inside of the cubes
        //glEnable(GL_CULL_FACE);
        //glfwSwapInterval(0); // Disable V-Sync



    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window.get(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
        glfwWindowShouldClose(window.get()) == 0);

    ImGui_ImplOpenGL3_Shutdown(); 
    ImGui_ImplGlfw_Shutdown(); 
    ImGui::DestroyContext(); 
}

