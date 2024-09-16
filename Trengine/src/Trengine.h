#pragma once

#include <stdio.h>
#include "Log.h"

//core
#include "Trengine/Core.h"
#include "Trengine/Application.h"
#include "Trengine/Events/Event.h"
#include "Trengine/Events/ApplicationEvent.h"
#include "Trengine/Events/EventDispatcher.h"
#include "Trengine/Events/KeyEvent.h"
#include "Trengine/Events/KeyPressedEvent.h"
#include "Trengine/Events/MouseEvent.h"
#include "Trengine/Layer.h"
#include "Trengine/ImGui/ImGUILayer.h"
#include "Trengine/Input.h"
#include "Trengine/KeyCodes.h"
#include "Trengine/MouseButtonCodes.h"
#include "Trengine/Renderer/Buffer.h"
#include "Trengine/Renderer/VertexArray.h"
#include "Trengine/Renderer/Shader.h"
#include "Trengine/Platform/OpenGL/OpenglShader.h"
#include "Trengine/Renderer/OrthographicCamera.h"
#include "Trengine/Renderer/Renderer.h"
#include "Trengine/Renderer/RendererAPI.h"
#include "Trengine/Renderer/RenderCommand.h"
#include "Trengine/Timestep.h"

//entry point
#include "Trengine/EntryPoint.h"