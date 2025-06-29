#include "pch.h"
#include "WindowsWindow.h"

namespace Badiya {
	void WindowsWindow::Init(const WindowProps& props)
	{
	}
	void WindowsWindow::Shutdown()
	{

	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{

	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
}