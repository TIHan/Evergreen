#include <stdexcept>
#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include <imgui_internal.h>

using namespace std;

#include "egWindow.h"

SDL_Window* GetSDLWindow(EgWindow window)
{
	return (SDL_Window*)window.internal;
}

extern "C" {

	EG_EXPORT EgWindow egWindowCreateVulkan(const char* name)
	{
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) < 0)
			throw runtime_error("SDL initialization failed");

		auto sdlWindow = SDL_CreateWindow(name, 1024, 768, SDL_WINDOW_VULKAN | SDL_WINDOW_HIDDEN);

		SDL_HideCursor();
		SDL_SetRelativeMouseMode(SDL_TRUE);

		EgWindow window;
		window.internal = sdlWindow;
		return window;
	}

	EG_EXPORT void egWindowDestroy(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_DestroyWindow(sdlWindow);
	}

	EG_EXPORT void* egWindowGetWin32Handle(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		return (void*)SDL_GetProperty(SDL_GetWindowProperties(sdlWindow), SDL_PROP_WINDOW_WIN32_HWND_POINTER, NULL);
	}

	EG_EXPORT EgWindowDisplayMode egWindowGetDesktopDisplayMode(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);
		auto sdlDisplayMode = SDL_GetDesktopDisplayMode(SDL_GetDisplayForWindow(sdlWindow));

		EgWindowDisplayMode displayMode;
		displayMode.width = sdlDisplayMode->w;
		displayMode.height = sdlDisplayMode->h;
		displayMode.refreshRate = sdlDisplayMode->refresh_rate;

		return displayMode;
	}

	EG_EXPORT EgWindowDisplayMode egWindowGetCurrentDisplayMode(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		auto sdlDisplayMode = SDL_GetWindowFullscreenMode(sdlWindow);
		if (sdlDisplayMode == NULL)
			sdlDisplayMode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(sdlWindow));

		EgWindowDisplayMode displayMode;
		displayMode.width = sdlDisplayMode->w;
		displayMode.height = sdlDisplayMode->h;
		displayMode.refreshRate = sdlDisplayMode->refresh_rate;

		if (!egWindowIsFullscreen(window))
		{
			auto size = egWindowGetSize(window);
			displayMode.width = size.x;
			displayMode.height = size.y;
		}

		return displayMode;
	}

	EG_EXPORT void egWindowSetCurrentDisplayMode(EgWindow window, EgWindowDisplayMode displayMode)
	{
		auto sdlWindow = GetSDLWindow(window);

		auto sdlDisplayModePtr = SDL_GetWindowFullscreenMode(sdlWindow);
		if (sdlDisplayModePtr == NULL)
			sdlDisplayModePtr = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(sdlWindow));

		auto sdlDisplayMode = *sdlDisplayModePtr;

		sdlDisplayMode.w = displayMode.width;
		sdlDisplayMode.h = displayMode.height;
		sdlDisplayMode.refresh_rate = displayMode.refreshRate;

		SDL_SetWindowFullscreenMode(sdlWindow, &sdlDisplayMode);

		if (!egWindowIsFullscreen(window))
		{
			EgWindowVector2 size;
			size.x = displayMode.width;
			size.y = displayMode.height;
			egWindowSetSize(window, size);
		}
	}

	EG_EXPORT void egWindowGetDisplayModes(EgWindow window, void(*callbackDisplayMode)(EgWindowDisplayMode))
	{
		auto sdlWindow = GetSDLWindow(window);

		auto sdlCurrentDisplayMode = SDL_GetWindowFullscreenMode(sdlWindow);
		if (sdlCurrentDisplayMode == NULL)
			sdlCurrentDisplayMode = SDL_GetCurrentDisplayMode(SDL_GetDisplayForWindow(sdlWindow));;

		auto sdlDisplayModes = SDL_GetFullscreenDisplayModes(SDL_GetDisplayForWindow(sdlWindow), NULL);

		if (sdlDisplayModes != NULL)
		{
			for (int i = 0; sdlDisplayModes[i]; i++)
			{
				auto sdlDisplayMode = sdlDisplayModes[i];

				if (sdlCurrentDisplayMode->displayID == sdlDisplayMode->displayID &&
					sdlCurrentDisplayMode->pixel_density == sdlDisplayMode->pixel_density &&
					sdlCurrentDisplayMode->format == sdlDisplayMode->format)
				{
					EgWindowDisplayMode displayMode;
					displayMode.width = sdlDisplayMode->w;
					displayMode.height = sdlDisplayMode->h;
					displayMode.refreshRate = sdlDisplayMode->refresh_rate;

					callbackDisplayMode(displayMode);
				}
			}

			SDL_free(sdlDisplayModes);
		}
	}

	EG_EXPORT void egWindowShow(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_ShowWindow(sdlWindow);
	}

	EG_EXPORT void egWindowHide(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_HideWindow(sdlWindow);
	}

	EG_EXPORT void egWindowMinimize(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_MinimizeWindow(sdlWindow);
	}

	EG_EXPORT EgWindowBool egWindowIsFullscreen(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		return SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_FULLSCREEN;
	}

	EG_EXPORT void egWindowSetFullscreen(EgWindow window, EgWindowBool value)
	{
		auto sdlWindow = GetSDLWindow(window);

		if (value)
		{
			if (!egWindowIsFullscreen(window))
			{
				SDL_SetWindowFullscreen(sdlWindow, SDL_TRUE);
			}
		}
		else
		{
			if (egWindowIsFullscreen(window))
			{
				auto displayMode = egWindowGetCurrentDisplayMode(window);

				SDL_SetWindowFullscreen(sdlWindow, SDL_FALSE);

				EgWindowVector2 size;
				size.x = displayMode.width;
				size.y = displayMode.height;
				egWindowSetSize(window, size);
			}
		}
	}

	EG_EXPORT EgWindowBool egWindowIsCursorVisible(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		return SDL_CursorVisible();
	}

	EG_EXPORT void egWindowSetCursorVisible(EgWindow window, EgWindowBool value)
	{
		auto sdlWindow = GetSDLWindow(window);

		if (value)
		{
			SDL_ShowCursor();
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_HideCursor();
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}
	}

	EG_EXPORT EgWindowBool egWindowIsHidden(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		return SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_HIDDEN;
	}

	EG_EXPORT EgWindowBool egWindowIsMinimized(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		return SDL_GetWindowFlags(sdlWindow) & SDL_WINDOW_MINIMIZED;
	}

	EG_EXPORT EgWindowVector2 egWindowGetSize(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		int w;
		int h;
		SDL_GetWindowSize(sdlWindow, &w, &h);

		EgWindowVector2 size;
		size.x = w;
		size.y = h;
		return size;
	}

	EG_EXPORT void egWindowSetSize(EgWindow window, EgWindowVector2 value)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_SetWindowSize(sdlWindow, value.x, value.y);
		if (!egWindowIsFullscreen(window))
		{
			SDL_SetWindowPosition(sdlWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
		}
	}

	EG_EXPORT EgWindowVector2 egWindowGetPosition(EgWindow window)
	{
		auto sdlWindow = GetSDLWindow(window);

		int w;
		int h;
		SDL_GetWindowPosition(sdlWindow, &w, &h);

		EgWindowVector2 position;
		position.x = w;
		position.y = h;
		return position;
	}

	EG_EXPORT void egWindowSetPosition(EgWindow window, EgWindowVector2 value)
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_SetWindowPosition(sdlWindow, value.x, value.y);
	}

	EG_EXPORT void egWindowPumpEvents(
		EgWindow window, 
		EgWindowBool hasImGuiInput, 
		void(*callbackKeyEvent)(EgWindowKeyEvent), 
		void(*callbackMouseInfo)(EgWindowMouseInfo), 
		void(*callbackMouseButtonEvent)(EgWindowMouseButtonEvent), 
		void(*callbackMouseWheelEvent)(EgWindowMouseWheelEvent),
		void(*callbackGamepadAxisMotionEvent)(EgWindowGamepadAxisMotionEvent),
		void(*callbackGamepadButtonEvent)(EgWindowGamepadButtonEvent),
		void(*callbackGamepadEvent)(EgWindowGamepadEvent),
		void(*callbackQuit)(void))
	{
		auto sdlWindow = GetSDLWindow(window);

		SDL_PumpEvents();
		
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (ImGui::GetCurrentContext())
			{
				if (hasImGuiInput)
				{
					ImGui_ImplSDL3_ProcessEvent(&event);
				}
			}

			switch (event.type)
			{

			case SDL_EVENT_KEY_DOWN:
			{
				EgWindowKeyEvent keyEvent;
				keyEvent.flags = EgWindowKeyEventFlags_DOWN;
				keyEvent.key = *(EgWindowKey*)&event.key.keysym.sym;

				if (event.key.repeat > 0)
				{
					keyEvent.flags = (EgWindowKeyEventFlags)(EgWindowKeyEventFlags_DOWN | EgWindowKeyEventFlags_REPEAT);
				}

				callbackKeyEvent(keyEvent);
				break;
			}

			case SDL_EVENT_KEY_UP:
			{
				EgWindowKeyEvent keyEvent;
				keyEvent.flags = EgWindowKeyEventFlags_UP;
				keyEvent.key = *(EgWindowKey*)&event.key.keysym.sym;
				callbackKeyEvent(keyEvent);
				break;
			}

			case SDL_EVENT_MOUSE_BUTTON_DOWN:
			{
				EgWindowMouseButtonEvent mouseButtonEvent;
				mouseButtonEvent.buttonIndex = *(unsigned char*)&event.button.button;
				mouseButtonEvent.flags = EgWindowMouseButtonEventFlags_DOWN;

				auto position = EgWindowVector2();
				position.x = event.button.x;
				position.y = event.button.y;
				mouseButtonEvent.position = position;
				callbackMouseButtonEvent(mouseButtonEvent);
				break;
			}

			case SDL_EVENT_MOUSE_BUTTON_UP:
			{
				EgWindowMouseButtonEvent mouseButtonEvent;
				mouseButtonEvent.buttonIndex = *(unsigned char*)&event.button.button;
				mouseButtonEvent.flags = EgWindowMouseButtonEventFlags_UP;

				auto position = EgWindowVector2();
				position.x = event.button.x;
				position.y = event.button.y;
				mouseButtonEvent.position = position;
				callbackMouseButtonEvent(mouseButtonEvent);
				break;
			}

			case SDL_EVENT_MOUSE_WHEEL:
			{
				EgWindowMouseWheelEvent mouseWheelEvent;
				if (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL)
				{
					mouseWheelEvent.flags = EgWindowMouseWheelEventFlags_UP;
				}
				else
				{
					mouseWheelEvent.flags = EgWindowMouseWheelEventFlags_DOWN;
				}
				callbackMouseWheelEvent(mouseWheelEvent);
				break;
			}

			case SDL_EVENT_GAMEPAD_AXIS_MOTION:
			{
				EgWindowGamepadAxisMotionEvent gamepadAxisMotionEvent;
				gamepadAxisMotionEvent.gamepadId = event.gaxis.which;
				gamepadAxisMotionEvent.axisId = event.gaxis.axis;
				gamepadAxisMotionEvent.value = event.gaxis.value;
				callbackGamepadAxisMotionEvent(gamepadAxisMotionEvent);
				break;
			}

			case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
			{
				EgWindowGamepadButtonEvent gamepadButtonEvent;
				gamepadButtonEvent.gamepadId = event.gbutton.which;
				gamepadButtonEvent.flags = EgWindowGamepadButtonEventFlags_DOWN;
				gamepadButtonEvent.buttonIndex = event.gbutton.button;
				callbackGamepadButtonEvent(gamepadButtonEvent);
				break;
			}

			case SDL_EVENT_GAMEPAD_BUTTON_UP:
			{
				EgWindowGamepadButtonEvent gamepadButtonEvent;
				gamepadButtonEvent.gamepadId = event.gbutton.which;
				gamepadButtonEvent.flags = EgWindowGamepadButtonEventFlags_UP;
				gamepadButtonEvent.buttonIndex = event.gbutton.button;
				callbackGamepadButtonEvent(gamepadButtonEvent);
				break;
			}

			case SDL_EVENT_GAMEPAD_ADDED:
			{
				EgWindowGamepadEvent gamepadEvent;
				gamepadEvent.kind = EgWindowGamepadEventKind_ADDED;
				gamepadEvent.gamepadId = event.gdevice.which;
				callbackGamepadEvent(gamepadEvent);
				break;
			}

			case SDL_EVENT_GAMEPAD_REMOVED:
			{
				EgWindowGamepadEvent gamepadEvent;
				gamepadEvent.kind = EgWindowGamepadEventKind_REMOVED;
				gamepadEvent.gamepadId = event.gdevice.which;
				callbackGamepadEvent(gamepadEvent);
				break;
			}

			case SDL_EVENT_QUIT:
			{
				callbackQuit();
				break;
			}

			default:
				break;

			}
		}

		EgWindowVector2 mousePosition;
		EgWindowVector2 mouseRelativePosition;
		SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
		SDL_GetRelativeMouseState(&mouseRelativePosition.x, &mouseRelativePosition.y);
		
		EgWindowMouseInfo mouseInfo;
		mouseInfo.position = mousePosition;
		mouseInfo.relativePosition = mouseRelativePosition;
		callbackMouseInfo(mouseInfo);
	}
}