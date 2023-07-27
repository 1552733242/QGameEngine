#include"qgpch.h"
#include"RendererCommand.h"
#include"QGame/Platform/OpenGL/OpenGLRendererAPI.h"
namespace QGame {
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;
}