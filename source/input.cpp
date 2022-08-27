#include <GLFW/glfw3.h>

namespace danikk_engine
{
	extern GLFWwindow* window;

	bool keyPressed(int Key)
	{
        return glfwGetKey(window, Key) == GLFW_PRESS;
	}
}
