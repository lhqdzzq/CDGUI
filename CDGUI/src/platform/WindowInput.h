#pragma once
#include"CDGUI/Core/Input.h"

namespace cdgui
{
	class WindowInput :
		public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode);
		virtual bool IsMouseButtonPressedImpl(int button);
		virtual std::pair<float, float> GetMousePositionImpl();
		virtual float GetMouseXImpl();
		virtual float GetMouseYImpl();
	protected:
		bool m_IsMouseLeftButtonPressed = false;
	};
}

