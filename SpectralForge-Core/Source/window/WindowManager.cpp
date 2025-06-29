#include "pch.h"
#include "WindowManager.h"
#include "WindowWindows.h"

namespace Badiya {

	//Make a #DEFINE to check if its windows then use this else do other
	Scope<WindowManager> WindowManager::Create(const WindowProps& props) {
		return CreateScope<WindowWindows>(props);
	}
}

