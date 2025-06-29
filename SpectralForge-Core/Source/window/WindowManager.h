#pragma once

#include "pch.h"

#include "Event.h"
#include "Graphics/OpenGLUtils.h"

namespace Badiya {

	//TODO: Move this to a separate file
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	struct WindowProps
	{
		std::string title;
		uint16_t width;
		uint16_t height;

		WindowProps(const std::string& title = "Badiya Engine",
			uint16_t width = 1600,
			uint16_t height = 900)
			:title(title), width(width), height(height)
		{
		}
	};

	class WindowManager
	{
	protected:
		WindowProps m_Data;
	public:
		WindowManager() {}
		virtual ~WindowManager() = default;

		virtual void Init() = 0;
		virtual std::string& GetWindowTitle()  { return m_Data.title; }
		virtual uint16_t GetWindowWidth() { return m_Data.width; };
		virtual uint16_t GetWindowHeight() { return m_Data.height; };


		virtual void OnUpdate() = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVsync() const = 0;
		virtual void ShutDown() = 0;

		static Scope<WindowManager> Create(const WindowProps& props = WindowProps());

	};
}


/*
	Window.Create(Title, Width, Height);
	What I dont want is 
		WindowManager windowManager(&init);

		auto window =
			windowManager.CreateAppWindow(3840, 2160, "Graphics Engine",
				nullptr, nullptr);
*/