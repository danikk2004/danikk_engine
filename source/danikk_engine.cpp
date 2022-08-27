#include <cstdlib>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <mutex>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <danikk_framework/danikk_framework.h>
#include <danikk_framework/path_buffer.h>
#include <danikk_framework/trace_sigsegv.h>
#include <danikk_framework/argv.h>

#include <danikk_engine/danikk_engine.h>
#include <danikk_engine/data_manager.h>
#include <danikk_engine/input.h>
#include <danikk_engine/localization.h>
#include <danikk_engine/sprite_renderer.h>

using namespace danikk_framework;
using namespace std::this_thread;
using namespace std::chrono;
using std::thread;
using std::mutex;

namespace danikk_engine
{
	using namespace internal;

    GLFWwindow* window;

    mutex interruptionMutex;
    bool graphics_is_inited = false;

	bool gl_thing_execute_requied = false;
	bool bool_begin_is_end = false;
	std::function<void()> gl_thing;

    size_t gl_version_major = 4;
    size_t gl_version_minor = 3;

    static void cursorPositionCallback(GLFWwindow* window, double x, double y)
    {
        (void)x;
        (void)y;
        (void)window;
    }

    static void errorCallback(int error, const char* description)
    {
        (void)error;
        cout << description << endl;
    }

    static void glDebugMessageCallbackFunc(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
    {
    	(void)source;
    	(void)id;
    	(void)severity;
    	(void)length;
    	(void)userParam;
        cout << "OpenGL Error type:" << type << " message: " << message << endl;
    }

    static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        (void)window;
        glViewport(0, 0, width, height);
    }

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        (void)window;
        (void)key;
        (void)scancode;
        (void)action;
        (void)mods;
    }

    static void charCallback(GLFWwindow* window, unsigned int codepoint)
    {
        (void)window;
        (void)codepoint;
    }

    static void windowRefreshCallback(GLFWwindow* window)
    {
        (void)window;
        glfwPollEvents();
    }

    static void initGraphics()
    {
        if (!glfwInit())
        {
            fatalError(localization("error/glfwinit"));
        }

        glfwSetErrorCallback(errorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_version_major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_version_minor);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        window = glfwCreateWindow(640, 480, "test", NULL, NULL);//glfwGetPrimaryMonitor()

        if (!window)
        {
            fatalError(localization("error/create_window"));
        }

        glfwMakeContextCurrent((GLFWwindow*)window);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetKeyCallback(window, keyCallback);
        glfwSetWindowRefreshCallback(window, windowRefreshCallback);
        glfwSetCharCallback(window, charCallback);
        glfwSetCursorPosCallback(window, cursorPositionCallback);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            fatalError(localization("error/gladinit"));
        }

		#define display_gl_thing(name) cout << #name << ": " << glGetString(name) << endl;
			display_gl_thing(GL_VENDOR)
			display_gl_thing(GL_VERSION)
			display_gl_thing(GL_RENDERER)
		#undef display_gl_thing

	    glDebugMessageCallback(glDebugMessageCallbackFunc, 0);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		//glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0.2f, 0.2f, 0.7f, 0);
		glfwSwapBuffers(window);
		graphics_is_inited = true;
    }

    void exit()
    {
        glfwSetWindowShouldClose(window, true);
    }

    void fatalError(const char* message)
    {
		cerr << message << endl;
		abort();
    }

    void fatalError(const String& message)
    {
    	fatalError(message.c_string());
    }

    void _glexec(std::function<void()> func)
    {
    	while(gl_thing_execute_requied)
		{
    		sleep_for(0.01ms);
		}
    	gl_thing = func;
    	gl_thing_execute_requied = true;
    	while(gl_thing_execute_requied)
		{
    		sleep_for(0.01ms);
		}
    }

    static void graphicsThreadMain()
    {
        initGraphics();
        initTextureRenderer();

        while(!bool_begin_is_end)
        {
            if(gl_thing_execute_requied)
            {
            	gl_thing();

            	gl_thing_execute_requied = false;
            }
            sleep_for(0.01ms);
        }

        while (!glfwWindowShouldClose(window))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            draw();
            glfwSwapBuffers(window);
            glfwPollEvents();
            if(gl_thing_execute_requied)
            {
            	gl_thing();

            	gl_thing_execute_requied = false;
            }
        }
    }
}

using namespace danikk_engine;

int main(int argc, char** argv)
{
	trace_sigsegv();

	#if IS_RELEASE
	    freopen("log.txt", "w", stdout);
	    freopen("error_log.txt", "w", stderr);
	#endif

    argv::init(argc, argv);

    cout << "DIR: " << getExecutableDirectory() << endl;

    initDataManager();

    thread graphicsThread(graphicsThreadMain);

    while(!graphics_is_inited)
	{
    	sleep_for(0.1ms);
	}
    begin();

    bool_begin_is_end = true;

    while (!glfwWindowShouldClose(window))
    {
        if (keyPressed(GLFW_KEY_LEFT_ALT) & keyPressed(GLFW_KEY_F4))
        {
            return EXIT_SUCCESS;
        }

        update();
    }

    graphicsThread.join();
    //glfwDestroyWindow(window);
    //glfwTerminate();
    return EXIT_SUCCESS;
}
