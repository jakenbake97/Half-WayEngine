﻿#pragma once

#include "Basalt/Core.h"
#include "Basalt/Input.h"
#include "Basalt/Keycodes.h"

namespace Basalt
{
	class WindowsInput : public Input
	{
	protected:
		bool CheckKey(KeyCode keycode) override;

		bool CheckMouseButton(MouseCode button) override;
		Vector2Int CheckMousePosition() override;
		bool CheckMouseInWindow() override;
		
		void HandleKeyDown(KeyCode keycode) override;
		void HandleKeyUp(KeyCode keycode) override;
		void ClearInputStates() override;

		void HandleMouseButtonDown(MouseCode mouseCode) override;
		void HandleMouseButtonUp(MouseCode mouseCode) override;
		void HandleMouseMoved(int xPos, int yPos) override;
		void HandleMouseWheel(int delta) override;

		void HandleMouseEnter() override;
		void HandleMouseLeave() override;

	private:
		std::unordered_map<KeyCode, bool> keyStates;
		
		std::unordered_map<MouseCode, bool> mouseButtonStates;
		int x = 0;
		int y = 0;
		bool mouseInWindow = false;
		int accumulatedWheelDelta = 0;
	};
}
