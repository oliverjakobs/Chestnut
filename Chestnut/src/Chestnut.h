#pragma once

// For use by Chestnut applications

#include "Chestnut/Core/Application.h"
#include "Chestnut/Core/Layer.h"

#include "Chestnut/Core/Timestep.h"

// ---Input---------------------------
#include "Chestnut/Input/Input.h"
#include "Chestnut/Input/KeyCodes.h"
#include "Chestnut/Input/OrthographicCameraController.h"

#include "Chestnut/ImGui/ImGuiRenderer.h"

// ---Renderer------------------------
#include "Chestnut/Graphics/Renderer.h"

#include "Chestnut/Graphics/Buffer.h"
#include "Chestnut/Graphics/Shader.h"
#include "Chestnut/Graphics/Texture.h"
#include "Chestnut/Graphics/VertexArray.h"

#include "Chestnut/Graphics/OrthographicCamera.h"

// ---Utility-------------------------
#include "Chestnut/Utility/Obelisk.h"
#include "Chestnut/Utility/Debugger.h"

// -----------------------------------


// ---Entry Point---------------------
#ifdef CHST_ENTRY_POINT
#include "Chestnut/Core/EntryPoint.h"
#endif
// -----------------------------------