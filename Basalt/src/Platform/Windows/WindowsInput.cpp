﻿#include "BEpch.h"
#include "WindowsInput.h"

#include "Basalt/Application.h"
#include "Basalt/Events/KeyboardEvent.h"
#include "Basalt/Events/MouseEvent.h"

namespace Basalt
{
	Scope<Input> Input::instance = std::make_unique<WindowsInput>();

	void WindowsInput::HandleKeyDown(const KeyCode keycode)
	{
		keyStates[keycode] = true;
		const auto keyDown = std::make_shared<KeyPressedEvent>(keycode, 0);
		Application::OnEvent(keyDown);
	}

	void WindowsInput::HandleKeyUp(const KeyCode keycode)
	{
		keyStates[keycode] = false;
		const auto keyUp = std::make_shared<KeyReleasedEvent>(keycode);
		Application::OnEvent(keyUp);
	}

	void WindowsInput::ClearInputStates()
	{
		keyStates.clear();
	}

	void WindowsInput::HandleMouseButtonDown(MouseCode mouseCode)
	{
		mouseButtonStates[mouseCode] = true;
		const auto mouseDown = std::make_shared<MouseButtonPressedEvent>(mouseCode);
		Application::OnEvent(mouseDown);
	}

	void WindowsInput::HandleMouseButtonUp(MouseCode mouseCode)
	{
		mouseButtonStates[mouseCode] = false;
		const auto mouseUp = std::make_shared<MouseButtonReleasedEvent>(mouseCode);
		Application::OnEvent(mouseUp);
	}

	void WindowsInput::HandleMouseMoved(const Vector2Int position)
	{
		pos = position;
		const auto mouseMoved = std::make_shared<MouseMovedEvent>(pos);
		Application::OnEvent(mouseMoved);
	}

	void WindowsInput::HandleMouseWheel(const int delta)
	{
		accumulatedWheelDelta += delta;

		while (accumulatedWheelDelta >= WHEEL_DELTA)
		{
			const auto mouseWheel = std::make_shared<MouseScrolledEvent>(accumulatedWheelDelta);
			Application::OnEvent(mouseWheel);
			accumulatedWheelDelta -= WHEEL_DELTA;
		}
		while (accumulatedWheelDelta <= -WHEEL_DELTA)
		{
			const auto mouseWheel = std::make_shared<MouseScrolledEvent>(accumulatedWheelDelta);
			Application::OnEvent(mouseWheel);
			accumulatedWheelDelta += WHEEL_DELTA;
		}
	}

	void WindowsInput::HandleMouseEnter()
	{
		mouseInWindow = true;
		const auto mouseEnter = std::make_shared<MouseEnterEvent>(pos);
		Application::OnEvent(mouseEnter);
	}

	void WindowsInput::HandleMouseLeave()
	{
		mouseInWindow = false;
		const auto mouseLeave = std::make_shared<MouseLeaveEvent>(pos);
		Application::OnEvent(mouseLeave);
	}

	bool WindowsInput::CheckKey(const KeyCode keycode)
	{
		return keyStates[keycode];
	}

	bool WindowsInput::CheckMouseButton(const MouseCode button)
	{
		return mouseButtonStates[button];
	}

	Vector2Int WindowsInput::CheckMousePosition()
	{
		return pos;
	}

	bool WindowsInput::CheckMouseInWindow()
	{
		return mouseInWindow;
	}
}
