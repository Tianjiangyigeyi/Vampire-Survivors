#include "VsApp.h"
// #include "../common/config.cpp"
GLFWwindow *window;

double cursor_x, cursor_y;
bool LeftButtonPressed = false;
bool* Keys;
bool notice = false;
bool shouldswap = true;

std::vector<glm::vec4> areas_to_check;
int button_id = MAX_INT;

bool render_in_game = false;
extern Voice v;


// 为了满足OpenGL的C特性，它们不得不设为全局变量

VsApp::VsApp()
{
    p_viewmodel = std::make_shared<GameViewModel>();
    p_view = std::make_shared<GameView>();
}

// 由于我们只有一个窗口，省略了window层，将窗口的生成一并放入app层中
bool VsApp::Init()
{
    Keys = new bool[1024];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_RESIZABLE, false);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "vampire survivor!", nullptr, nullptr);

    // bind
    p_view->SetGamePointer(p_viewmodel->GetGamePointer());
    Attach(std::bind(&GameViewModel::SetKeys, *p_viewmodel, std::placeholders::_1));

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // OpenGL  cnfiguration
    // --------------------
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // initialize game
    // ---------------
    Utility::Init(p_viewmodel->GetGamePointer());

    return true;
}

int VsApp::Run()
{
    
    v.play(0, 1);
    // deltaTime variables
    // -------------------
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        if(shouldswap){
            // calculate delta time
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
            if (deltaTime < 1.0f / MAX_FRAME_PER_SECOND)
            {
                Sleep(1.0f / MAX_FRAME_PER_SECOND - deltaTime);
                deltaTime = 1.0f / MAX_FRAME_PER_SECOND;
            }
            else
            {
                std::cout << deltaTime << std::endl;
            }
            glfwPollEvents();
            if(render_in_game) 
                bool tmp = check_should_render(areas_to_check, cursor_x, cursor_y, LeftButtonPressed);
            if (notice == true)
            {
                Notify(Keys, deltaTime);
                notice = false;
            } 
            // update game state
            // -----------------
            p_viewmodel->Update(deltaTime);

            // render
            // ------
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            p_view->Render();
            glfwSwapBuffers(window);

        } else {
            
            shouldswap = check_should_render(areas_to_check, cursor_x, cursor_y, LeftButtonPressed);
            glfwPollEvents();

        }
 
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();
    Utility::DestroyRenderer();
    glfwTerminate();
    return 0;
}

VsApp::~VsApp()
{
    // 智能指针可以自然析构
    // delete vampireSurvivor;
    delete Keys;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = true;
        else if (action == GLFW_RELEASE)
            Keys[key] = false;
    }
    // Notify observers
    notice = true;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    glfwGetCursorPos(window, &cursor_x, &cursor_y);

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {

        LeftButtonPressed = true;
        std::cout << cursor_x << " " << cursor_y << std::endl;
    }
}

bool check_should_render(std::vector<glm::vec4> areas, double cursor_x, double cursor_y, bool button_left)
{
    int id = 0;
    for (auto area : areas)
    {
        if (cursor_x >= area.x && cursor_x <= area.x + area.z && cursor_y >= area.y && cursor_y <= area.y + area.w)
        {
            if (button_left)
            {
                button_id = id;
                return true;
            }
        }
        id ++;
    }
    button_id  = MAX_INT;
    return false;
}