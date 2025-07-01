#pragma once

#include "pch.h"

#include "Event.h"
#include "Graphics/API/OpenGLUtils.h"

namespace Badiya::Window {

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

		explicit WindowProps(std::string title = "Badiya Engine",
			const uint16_t width = 1600,
			const uint16_t height = 900)
			:title(std::move(title)), width(width), height(height)
		{
		}
	};

	class WindowManager
	{
	protected:
		WindowProps m_Data;
	public:
		WindowManager() = default;
		virtual ~WindowManager() = default;

		virtual std::string& GetWindowTitle() { return m_Data.title; }
		[[nodiscard]] virtual uint16_t GetWindowWidth()  const = 0;
		[[nodiscard]] virtual uint16_t GetWindowHeight() const = 0;


		virtual void OnUpdate() = 0;
		virtual void SetVSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVsync() const = 0;
		[[nodiscard]] virtual void* GetNativeWindow() const = 0;

		static Scope<WindowManager> Create(const WindowProps& props = WindowProps());

	};

}