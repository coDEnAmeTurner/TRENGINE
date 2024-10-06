#pragma once

#include <stdio.h>
#include "Log.h"

//core
#include "Trengine/Core/Core.h"

//application
#include "Trengine/Core/Application.h"
#include "Trengine/Events/Event.h"
#include "Trengine/Events/ApplicationEvent.h"
#include "Trengine/Events/EventDispatcher.h"
#include "Trengine/Events/KeyEvent.h"
#include "Trengine/Events/KeyPressedEvent.h"
#include "Trengine/Events/MouseEvent.h"
#include "Trengine/Core/Layer.h"
#include "Trengine/ImGui/ImGUILayer.h"
#include "Trengine/Core/Input.h"
#include "Trengine/Core/KeyCodes.h"
#include "Trengine/Core/MouseButtonCodes.h"

//Renderer
#include "Trengine/Renderer/Buffer.h"
#include "Trengine/Renderer/VertexArray.h"
#include "Trengine/Renderer/Shader.h"
#include "Trengine/Platform/OpenGL/OpenglShader.h"
#include "Trengine/Renderer/OrthographicCamera.h"
#include "Trengine/OrthographicCameraController.h"
#include "Trengine/Renderer/Renderer.h"
#include "Trengine/Renderer/Renderer2D.h"
#include "Trengine/Renderer/RendererAPI.h"
#include "Trengine/Renderer/RenderCommand.h"
#include "Trengine/Renderer/Texture.h"
#include "Trengine/Renderer/SubTexture2D.h"

//Debug
#include "Trengine/Core/Timestep.h"
#include "Timer.h"

//entry point
#include "Trengine/Core/EntryPoint.h"