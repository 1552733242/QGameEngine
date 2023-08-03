#include "qgpch.h"
#include <QGame.h>
#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include "QGame/Platform/OpenGL/OpenGlShader.h"
class ExampleLayer :public QGame::Layer { 
public:
	ExampleLayer() :Layer("Example"), m_CameraController(1280.0f / 720.0f) 
	{
		
		std::string vertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;
	layout(location = 1) in vec4 a_Color;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	out vec3 v_Position;
	out vec4 v_Color;
	void main(){
		

		v_Position = a_Position;
		v_Color = a_Color;

		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
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
		m_Shader = QGame::Shader::Create("1", vertexSrc, fragmentSrc);
		float vertices[3 * 7]{
		-0.5f,  -0.5f,  0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  -0.5f,  0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,   0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};
		unsigned int indices[] = { 0,1,2 };
		m_VertexArray.reset(QGame::VertexArray::Create());
		QGame::Ref<QGame::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(QGame::VertexBuffer::Create(vertices, sizeof(vertices)));
		QGame::Ref<QGame::IndexBuffer>indexBuffer;
		indexBuffer.reset(QGame::IndexBuffer::Create(indices, sizeof(vertices)));
		m_SquareVA.reset(QGame::VertexArray::Create());
		QGame::BufferLayout layout = {
			{QGame::ShaderDataType::Float3, "a_Position"},
			{QGame::ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);




		std::string squreVertexSrc = R"(
	#version 330 core
	
	layout(location = 0) in vec3 a_Position;

	uniform mat4 u_ViewProjection;
	uniform mat4 u_Transform;

	out vec3 v_Position;

	void main(){
		

		v_Position = a_Position;

		gl_Position = u_ViewProjection * u_Transform * vec4(a_Position,1.0);
	}
)";
		std::string squreFragmentSrc = R"(
	#version 330 core
	in vec3 v_Position;
	layout(location = 0) out vec4 color;
	
	uniform vec3 u_Color;
	void main(){
		color = vec4(u_Color,1.0);
	}
)";

		m_SquareSD = QGame::Shader::Create("SquareSD", squreVertexSrc, squreFragmentSrc);
		m_SquareVA.reset(QGame::VertexArray::Create());
		QGame::BufferLayout squreLayout = {
		{QGame::ShaderDataType::Float3, "a_Position"},
			{QGame::ShaderDataType::Float2,"a_TextCoord"}
		};
		float  squreVertexs[] = {
		-0.5f,  -0.5f,  0.0f, 0.0f, 0.0f,
		-0.5f,   0.5f,  0.0f, 0.0f, 1.0f,
		 0.5f,   0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  -0.5f,  0.0f, 1.0f, 0.0f
		};
		unsigned int squreIndices[] = { 0,1,2, 2,3,0 };
		QGame::Ref<QGame::VertexBuffer> squreVertexBuffer;
		squreVertexBuffer.reset(QGame::VertexBuffer::Create(squreVertexs, sizeof(squreVertexs)));
		QGame::Ref<QGame::IndexBuffer> squreIndexBuffer;
		
		squreIndexBuffer.reset(QGame::IndexBuffer::Create(squreIndices, sizeof(squreIndices)));
		squreVertexBuffer->SetLayout(squreLayout);
		m_SquareVA->AddVertexBuffer(squreVertexBuffer);
		m_SquareVA->SetIndexBuffer(squreIndexBuffer);






		m_TextureSD = QGame::Shader::Create("shaders/Texture.glsl");
		m_Texture = QGame::Texture2D::Create("assets/textures/Checkerboard.png");

		m_ChernoLogoTexture = QGame::Texture2D::Create("assets/textures/ChernoLogo.png");
		

		std::dynamic_pointer_cast<QGame::OpenGLShader>(m_TextureSD)->Bind();
		std::dynamic_pointer_cast<QGame::OpenGLShader>(m_TextureSD)->UploadUinformInt("u_Texture", 0);

	}


	virtual void OnImGuiRender()override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Squre Color", glm::value_ptr(m_SqureColor));
		ImGui::End();
	}
	void OnUpdate(QGame::Timestep ts)override {
		
		//Update
		m_CameraController.OnUpdata(ts);

		//Render
		QGame::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		QGame::RendererCommand::Clear();

		
		QGame::Renderer::BeginScene(m_CameraController.GetCamera());


		std::dynamic_pointer_cast<QGame::OpenGLShader>(m_SquareSD)->Bind();
		std::dynamic_pointer_cast<QGame::OpenGLShader>(m_SquareSD)->UploadUinformFloat3("u_Color", m_SqureColor);

		//QGame::Renderer::Submit(m_Shader, m_VertexArray);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 20; j++) {
				glm::vec3 pos(i * 0.11f, j * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				QGame::Renderer::Submit(m_SquareSD, m_SquareVA, transform);
			}
		}
		//QGame::Renderer::Submit(m_SquareSD, m_SquareVA);
		m_Texture->Bind();
		QGame::Renderer::Submit(m_TextureSD, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_ChernoLogoTexture->Bind();
		QGame::Renderer::Submit(m_TextureSD, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		
		QGame::Renderer::EndScene();

	}
	void OnEvent(QGame::Event& event)override {
		m_CameraController.OnEvent(event);
	}
	
private:
	QGame::Ref<QGame::Shader>m_Shader;
	QGame::Ref<QGame::Shader>m_SquareSD;
	QGame::Ref<QGame::Shader>m_TextureSD;

	QGame::Ref<QGame::Texture2D>m_Texture;
	QGame::Ref<QGame::Texture2D>m_ChernoLogoTexture;
	


	QGame::Ref<QGame::VertexArray>m_VertexArray;
	QGame::Ref<QGame::VertexArray>m_SquareVA;

	QGame::OrthographicCameraController m_CameraController;

	
	glm::vec3 m_SqureColor = { 0.2f,0.3f,0.8f };
};


class Sanbox :public QGame::Application {
public:
	Sanbox() {
		PushLayer(new ExampleLayer());
	}
	~Sanbox() {}
};

QGame::Application* QGame::CreateApplication() {

	return new Sanbox();
}