#include "pch.h"
#include "WindowManager.h"
#include "WindowsWindow.h"

namespace Badiya::Window {

	//Make a #DEFINE to check if its windows then use this else do other
	Scope<WindowManager> WindowManager::Create(const WindowProps& props) {
		return CreateScope<WindowsWindow>(props);
	}
}

