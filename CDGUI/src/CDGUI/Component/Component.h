#pragma once
#include"CDGUI/Core/Core.h"
#include"glm/glm.hpp"
namespace cdgui
{
	class Component
	{
	public:
		virtual void Draw() = 0;
		virtual void SetMode(unsigned int mode) = 0;

	private:
		virtual void Update() = 0;
		virtual bool WithinScope() = 0;
	};
}