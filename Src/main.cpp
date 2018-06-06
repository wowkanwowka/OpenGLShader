#include <Src/ShaderClass/ShaderClass.h>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const size_t SCREEN_WIDTH = 800;

const size_t SCREEN_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window, float* r, float* g, float* b);

void PrepareSetOfVertices(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, float* vertices, unsigned int* indices,
                     int thesizeofvertices, int thesizeofindices);

void DrawSetOfVertices(unsigned int* VAO, unsigned int* shaderProgram);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My First Window", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "no window this time\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)(glfwGetProcAddress))) {
        std::cout << "No glad this time\n";
        return -1;
    }
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


//    float vertices[] = {
//            -0.5f, -0.5f, 0.0f, // left
//            0.5f, -0.5f, 0.0f, // right
//            0.0f,  0.5f, 0.0f  // top
//    };

//    float vertices[] = {
//            0.5f,  0.5f, 0.0f,  // top right
//            0.5f, -0.5f, 0.0f,  // bottom right
//            -0.5f, -0.5f, 0.0f,  // bottom left
//            -0.5f,  0.5f, 0.0f
//    };

    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            -0.25f, -0.0f, 0.0f,
            0.0f, -0.5f, 0.0f,

            0.25f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
//
//    float vertices1[] = {
//            0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
//            0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f
//    };
//
    unsigned int indices[] = {
            0, 1, 2,   // first triangle
            2, 3, 4
    };
    unsigned int VBO, VAO, EBO;
//    unsigned int VBO1, VAO1;
//    unsigned int shaderProgramFirst, shaderProgramSecond, shaderProgramThird;
//
//
    ShaderClass shader("../ShadersSourceFiles/FirstStep.vs", "../ShadersSourceFiles/FirstStep.fs");
    try {
        shader.Compile();
        shader.Link();
    } catch (std::runtime_error& err) {
        std::cerr << err.what() << '\n';
    }
    PrepareSetOfVertices(&VAO, &VBO, &EBO, vertices, indices, sizeof(vertices), sizeof(indices));
//    PrepareTriangleVAOInterpolated(&VAO1, &VBO1, vertices1, sizeof(vertices1));

    //PrepareTriangleVAO(&VAO, &VBO, vertices, sizeof(vertices));
    float r, g, b;
    r = 1.0;
    g = 1.0;
    b = 1.0;
    while (!glfwWindowShouldClose(window)) {

        processInput(window, &r, &g, &b);

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        DrawSetOfVertices(&VAO, &shader.GetId());
        shader.Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        DrawTriangle(&VAO1, &shaderProgramSecond);
//
//        DrawTriangle(&VAO1, &shaderProgramThird);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteVertexArrays(1, &VAO1);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteBuffers(1, &VBO1);
//    glDeleteProgram(shaderProgramFirst);
//    glDeleteProgram(shaderProgramSecond);
    glfwTerminate();
    return 0;
}

//void DrawSetOfVertices(unsigned int* VAO, unsigned int* shaderProgram) {
////    glUseProgram(*shaderProgram);
//    glBindVertexArray(*VAO);
//    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//}

void PrepareSetOfVertices(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO, float* vertices, unsigned int* indices,
                          int thesizeofvertices, int thesizeofindices) {

    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, thesizeofvertices, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, thesizeofindices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window, float* r, float* g, float* b) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    } else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        *r = 0.3;
        *g = 0.5;
        *b = 0.7;
    } else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        *r = 1.0;
        *g = 1.0;
        *b = 1.0;
    } else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        *r = 1.0;
        *g = 0.1;
        *b = 0.1;
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        *r = 0.3;
        *g = 0.5;
        *b = 0.7;
    }
}



