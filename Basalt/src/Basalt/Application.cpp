#include "BEpch.h"
#include "Application.h"

#include "IInput.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/WindowEvent.h"

namespace Basalt
{
	Application* Application::instance = nullptr;
	
	Application::Application(String name)
		: applicationName(std::move(name))
	{
		instance = this;
	}

	Application::~Application() = default;

	int Application::Update()
	{
		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			EventUpdate();
		}

		if (gResult == -1)
		{
			return EXIT_FAILURE;
		}

		return msg.wParam;
	}

	String Application::GetAppName() const
	{
		return applicationName;
	}

	void Application::EventUpdate()
	{
		while(!eventBuffer.empty())
		{
			auto event = eventBuffer.front();
			BE_TRACE("Event Buffer: {0}", *event);
			EventDispatcher dispatcher(*event);
			dispatcher.Dispatch<WindowCloseEvent>([](WindowCloseEvent& closeEvent)->bool {return OnWindowClose(closeEvent); });
			eventBuffer.pop();
		}
	}

	void Application::OnEvent(const std::shared_ptr<Event>& event)
	{	
		instance->eventBuffer.push(event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		system("pause");

		if (event.GetExitCode() != 0)
			return false;
		
		return true;
	}
}
