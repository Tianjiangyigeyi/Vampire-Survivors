#include "VsApp.h"

// 为了满足OpenGL的C特性，它们也不得不设为全局变量
Game *vampireSurvivor;
GLFWwindow *window;

VsApp::VsApp()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "vampire survivor!", nullptr, nullptr);
    vampireSurvivor = new Game(SCREEN_WIDTH, SCREEN_HEIGHT);
}

// 由于我们只有一个窗口，省略了window层，将窗口的生成一并放入app层中
bool VsApp::Init()
{
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL  cnfiguration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    vampireSurvivor->Init();

    return true;
}

int VsApp::Run()
{
    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        if (deltaTime < 1.0f / 45.0f)
        {
            Sleep(1.0f / 45.0f - deltaTime);
            deltaTime = 1.0f / 45.0f;
        }
        else
        {
            std::cout << deltaTime << std::endl;
        }
        // std::cout << deltaTime << std::endl;
        glfwPollEvents();

        // manage user input
        // -----------------
        vampireSurvivor->ProcessInput(deltaTime);

        // update game state
        // -----------------
        vampireSurvivor->Update(deltaTime);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        vampireSurvivor->Render();

        glfwSwapBuffers(window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    glfwTerminate();
    return 0;
}

VsApp::~VsApp()
{
    delete vampireSurvivor;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            vampireSurvivor->Keys[key] = true;
        else if (action == GLFW_RELEASE)
            vampireSurvivor->Keys[key] = false;
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}