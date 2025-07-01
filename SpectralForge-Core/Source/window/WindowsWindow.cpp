#include "pch.h"
#include "WindowsWindow.h"
#include "Logging.h"
#include "../Assert.h"


namespace Badiya::Window {
	static uint8_t s_GLFWWindowCount{};
	WindowsWindow::WindowsWindow(const WindowProps& props) 
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.title = props.title;
		m_Data.width = props.width;
		m_Data.height = props.height;
		BDY_CORE_INFO("Window Init {0} ({1}, {2})", props.title, props.width, props.height);

		if (s_GLFWWindowCount == 0)
		{
			BDY_INFO("glfwInit");
			int success = glfwInit();
			BDY_CORE_ASSERT(success, "Could not initialize GLFW!");
			//glfwSetErrorCallback(GLFWErrorCallback);
		}
		m_Window = glfwCreateWindow(m_Data.width, m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		BDY_CORE_ASSERT(m_Window, "Failed to create GLFW window!");
		glfwMakeContextCurrent(m_Window);
		GLenum err = glewInit();
		BDY_CORE_ASSERT(err == GLEW_OK, "GLEW init failed: {}", glewGetErrorString(err));
		++s_GLFWWindowCount;

	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}


	void WindowsWindow::SetVSync(const bool enabled)
	{
		m_Data.VSync = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;
		if (s_GLFWWindowCount == 0)
		{
			BDY_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}


}


