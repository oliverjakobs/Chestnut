#pragma once

#include "Chestnut/Api.h"

// From glfw3.h
#define CHST_KEY_SPACE              32
#define CHST_KEY_APOSTROPHE         39  /* ' */
#define CHST_KEY_COMMA              44  /* , */
#define CHST_KEY_MINUS              45  /* - */
#define CHST_KEY_PERIOD             46  /* . */
#define CHST_KEY_SLASH              47  /* / */
#define CHST_KEY_0                  48
#define CHST_KEY_1                  49
#define CHST_KEY_2                  50
#define CHST_KEY_3                  51
#define CHST_KEY_4                  52
#define CHST_KEY_5                  53
#define CHST_KEY_6                  54
#define CHST_KEY_7                  55
#define CHST_KEY_8                  56
#define CHST_KEY_9                  57
#define CHST_KEY_SEMICOLON          59  /* ; */
#define CHST_KEY_EQUAL              61  /* = */
#define CHST_KEY_A                  65
#define CHST_KEY_B                  66
#define CHST_KEY_C                  67
#define CHST_KEY_D                  68
#define CHST_KEY_E                  69
#define CHST_KEY_F                  70
#define CHST_KEY_G                  71
#define CHST_KEY_H                  72
#define CHST_KEY_I                  73
#define CHST_KEY_J                  74
#define CHST_KEY_K                  75
#define CHST_KEY_L                  76
#define CHST_KEY_M                  77
#define CHST_KEY_N                  78
#define CHST_KEY_O                  79
#define CHST_KEY_P                  80
#define CHST_KEY_Q                  81
#define CHST_KEY_R                  82
#define CHST_KEY_S                  83
#define CHST_KEY_T                  84
#define CHST_KEY_U                  85
#define CHST_KEY_V                  86
#define CHST_KEY_W                  87
#define CHST_KEY_X                  88
#define CHST_KEY_Y                  89
#define CHST_KEY_Z                  90
#define CHST_KEY_LEFT_BRACKET       91  /* [ */
#define CHST_KEY_BACKSLASH          92  /* \ */
#define CHST_KEY_RIGHT_BRACKET      93  /* ] */
#define CHST_KEY_GRAVE_ACCENT       96  /* ` */
#define CHST_KEY_WORLD_1            161 /* non-US #1 */
#define CHST_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define CHST_KEY_ESCAPE             256
#define CHST_KEY_ENTER              257
#define CHST_KEY_TAB                258
#define CHST_KEY_BACKSPACE          259
#define CHST_KEY_INSERT             260
#define CHST_KEY_DELETE             261
#define CHST_KEY_RIGHT              262
#define CHST_KEY_LEFT               263
#define CHST_KEY_DOWN               264
#define CHST_KEY_UP                 265
#define CHST_KEY_PAGE_UP            266
#define CHST_KEY_PAGE_DOWN          267
#define CHST_KEY_HOME               268
#define CHST_KEY_END                269
#define CHST_KEY_CAPS_LOCK          280
#define CHST_KEY_SCROLL_LOCK        281
#define CHST_KEY_NUM_LOCK           282
#define CHST_KEY_PRINT_SCREEN       283
#define CHST_KEY_PAUSE              284
#define CHST_KEY_F1                 290
#define CHST_KEY_F2                 291
#define CHST_KEY_F3                 292
#define CHST_KEY_F4                 293
#define CHST_KEY_F5                 294
#define CHST_KEY_F6                 295
#define CHST_KEY_F7                 296
#define CHST_KEY_F8                 297
#define CHST_KEY_F9                 298
#define CHST_KEY_F10                299
#define CHST_KEY_F11                300
#define CHST_KEY_F12                301
#define CHST_KEY_F13                302
#define CHST_KEY_F14                303
#define CHST_KEY_F15                304
#define CHST_KEY_F16                305
#define CHST_KEY_F17                306
#define CHST_KEY_F18                307
#define CHST_KEY_F19                308
#define CHST_KEY_F20                309
#define CHST_KEY_F21                310
#define CHST_KEY_F22                311
#define CHST_KEY_F23                312
#define CHST_KEY_F24                313
#define CHST_KEY_F25                314
#define CHST_KEY_KP_0               320
#define CHST_KEY_KP_1               321
#define CHST_KEY_KP_2               322
#define CHST_KEY_KP_3               323
#define CHST_KEY_KP_4               324
#define CHST_KEY_KP_5               325
#define CHST_KEY_KP_6               326
#define CHST_KEY_KP_7               327
#define CHST_KEY_KP_8               328
#define CHST_KEY_KP_9               329
#define CHST_KEY_KP_DECIMAL         330
#define CHST_KEY_KP_DIVIDE          331
#define CHST_KEY_KP_MULTIPLY        332
#define CHST_KEY_KP_SUBTRACT        333
#define CHST_KEY_KP_ADD             334
#define CHST_KEY_KP_ENTER           335
#define CHST_KEY_KP_EQUAL           336
#define CHST_KEY_LEFT_SHIFT         340
#define CHST_KEY_LEFT_CONTROL       341
#define CHST_KEY_LEFT_ALT           342
#define CHST_KEY_LEFT_SUPER         343
#define CHST_KEY_RIGHT_SHIFT        344
#define CHST_KEY_RIGHT_CONTROL      345
#define CHST_KEY_RIGHT_ALT          346
#define CHST_KEY_RIGHT_SUPER        347
#define CHST_KEY_MENU               348

// Mouse Buttons
#define CHST_MOUSE_BUTTON_1         0
#define CHST_MOUSE_BUTTON_2         1
#define CHST_MOUSE_BUTTON_3         2
#define CHST_MOUSE_BUTTON_4         3
#define CHST_MOUSE_BUTTON_5         4
#define CHST_MOUSE_BUTTON_6         5
#define CHST_MOUSE_BUTTON_7         6
#define CHST_MOUSE_BUTTON_8         7
#define CHST_MOUSE_BUTTON_LAST      CHST_MOUSE_BUTTON_8
#define CHST_MOUSE_BUTTON_LEFT      CHST_MOUSE_BUTTON_1
#define CHST_MOUSE_BUTTON_RIGHT     CHST_MOUSE_BUTTON_2
#define CHST_MOUSE_BUTTON_MIDDLE    CHST_MOUSE_BUTTON_3

namespace chst
{
	class CHST_API Input
	{
	public:
		inline static bool IsKeyPressed(int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};
}