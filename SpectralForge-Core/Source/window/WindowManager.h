#pragma once

#include "pch.h"

#include "Event.h"
#include "Graphics/OpenGLUtils.h"

namespace Badiya {
	struct WindowProps
	{
		std::string title;
		uint16_t width;
		uint16_t height;
		GLFWmonitor* monitor;
		GLFWwindow* share;

		WindowProps(const std::string& title = "Badiya Engine",
			uint16_t width = 1600,
			uint16_t height = 900,
			GLFWmonitor* monitor = nullptr,
			GLFWwindow* share = nullptr)
				:title(title), width(width),height(height),monitor(monitor),share(share)
		{
		}

	};


	/**
	 * @class WindowManager
	 * @brief A class responsible for managing GLFW windows, including creation and cleanup.
	 */
	class WindowManager {
	private:
		/**
		 * @brief Pointer to an OpenGL initialization object.
		 * Used to manage OpenGL settings and ensure proper initialization.
		 */
		OpenGLInit* p_init{};
		static WindowManager* instance;

	public:

		/*
		using EventCallBackFn = std::function<void(Event&)>;

		virtual ~WindowManager() = default;
		virtual void OnUpdate() = 0;

		virtual uint16_t GetWidth() = 0;
		virtual uint16_t GetHeight() = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallBackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		[[nodiscard]] virtual void* GetNativeWindow() const = 0;

		static std::unique_ptr<WindowManager> Create(const WindowProps& props)
		{
			const auto init = std::make_unique<OpenGLInit>();
			return std::make_unique<WindowManager>(init.get());
		}
		*/

		/**
		 * @brief Constructor for the WindowManager class.
		 * Initializes the OpenGLInit object to manage OpenGL context.
		 * @param p_init A pointer to an OpenGLInit object.
		 */
		WindowManager(OpenGLInit* p_init) : p_init(p_init) {}

		void Init();

		/**
		 * @brief Creates a new GLFW window with the specified parameters.
		 * Uses a unique pointer to automatically manage memory and ensure cleanup.
		 * @param width The width of the window in pixels.
		 * @param height The height of the window in pixels.
		 * @param title The title of the window.
		 * @param monitor The monitor to use for fullscreen mode, or NULL for windowed mode.
		 * @param share Another window whose OpenGL context to share resources with, or NULL for no sharing.
		 * @return A unique pointer to the created GLFWwindow, automatically cleaned up when out of scope.
		 */
		std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)>
			CreateAppWindow(const int width, const int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	};

}