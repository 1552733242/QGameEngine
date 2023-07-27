#include"qgpch.h"

#include "Appliccation.h"
#include "Input.h"
#include "QGame/Renderer/Renderer.h"

namespace QGame {
	
	Application* Application::s_Instance = nullptr;


	Application::Application() :m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
		GAME_CORE_ASSERT(!s_Instance, "Application already exit");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(QG_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);



		float vertices[3 * 7]{
			-0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f,  -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,   0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};				  
		unsigned int indices[] = { 0,1,2 };
		m_VertexArray.reset(VertexArray::Create());
		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		std::shared_ptr<IndexBuffer>indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(vertices)));
		m_SquareVA.reset(VertexArray::Create());
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		


		std::string vertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;

	out vec3 v_Position;
	out vec4 v_Color;
	void main(){
		

		v_Position = a_Position;
		v_Color = a_Color;

		gl_Position = u_ViewProjection * vec4(a_Position,1.0);
	}
)";
		std::string fragmentSrc = R"(
	#version 330 core
	in vec3 v_Position;
	in vec4 v_Color;
	layout(location = 0) out vec4 color;
	
	void main(){
		color = v_Color;
	}


)";


		m_Shader = std::make_unique<Shader>(vertexSrc, fragmentSrc);


	}

	Application::~Application()	
	{
	}

	void Application::Run()
	{
	
		while (m_Running) {
			
			RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });

			RendererCommand::Clear();


			Renderer::BeginScene(m_Camera);

			m_Shader->Bind();
			m_Shader->UploadUniformMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
			Renderer::Submit(m_VertexArray);



			Renderer::EndScene();




			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(QG_BIND_EVENT_FN(Application::OnWindowClose));
		
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e) {
			
		m_Running = false;
		
		return true;
	}


	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


}




