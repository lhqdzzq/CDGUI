#pragma once

//使用cdgui
#include"CDGUI/Core/Core.h"
#include"CDGUI/Core/Application.h"
#include"CDGUI/Core/Layer.h"
#include"CDGUI/Core/Timestep.h"
#include"CDGUI/Event/KeyEvent.h"
#include"CDGUI/Event/MouseEvent.h"
#include"CDGUI/Event/ApplicationEvent.h"
//输入
#include"CDGUI/Core/Input.h"
#include"CDGUI/Core/KeyCode.h"
#include"CDGUI/Core/MouseButtonCode.h"

//渲染
#include"CDGUI/Renderer/Buffer.h"
#include"CDGUI/Renderer/Shader.h"
#include"platform/OpenGL/OpenGLShader.h"
#include"CDGUI/Renderer/VertexArray.h"
#include"CDGUI/Renderer/Texture.h"

#include"CDGUI/Renderer/RenderCommand.h"
#include"CDGUI/Renderer/Renderer.h"

#include"CDGUI/Renderer/OrthographicCamera.h"

//组件
#include"CDGUI/Component/Button.h"
#include"CDGUI/Component/Circle.h"
#include"CDGUI/Component/Scroll.h"
#include"CDGUI/Component/RadioButton.h"
#include"CDGUI/Component/CheckBox.h"

//程序入口
#include"CDGUI/Core/EntryPoint.h"