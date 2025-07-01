#pragma once

#include "WindowManager.h"

namespace Badiya::Window {

	class WindowsWindow : public WindowManager 
	{
	private:
		struct WindowData
		{
			std::string title;
			uint16_t width, height;
			bool VSync;
		};

		WindowData m_Data;
		GLFWwindow* m_Window;

	private:
		virtual void Init(const WindowProps& props);
		virtual void  Shutdown();
	public:
		 explicit WindowsWindow(const WindowProps& props);
		 virtual ~WindowsWindow() override;

		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		[[nodiscard]] bool IsVsync() const override { return m_Data.VSync; }
		virtual void* GetNativeWindow() const override;

		[[nodiscard]] uint16_t GetWindowWidth() const override { return m_Data.width; }
		[[nodiscard]] uint16_t GetWindowHeight() const override { return m_Data.height; }
	};
}
