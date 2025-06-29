#pragma once

#include "WindowManager.h"

namespace Badiya{

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
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();	
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow() = default;

		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		bool IsVsync() const override { return m_Data.VSync; }

		uint16_t GetWindowWidth() override { return m_Data.width; };
		uint16_t GetWindowHeight() override { return m_Data.height; };


	};
}