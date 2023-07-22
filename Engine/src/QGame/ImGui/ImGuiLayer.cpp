#include"qgpch.h"
#include"ImGuiLayer.h"
#include"QGame/Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include"QGame/Appliccation.h"
#include"GLFW/glfw3.h"

namespace QGame {

	ImGuiLayer::ImGuiLayer():Layer("ImGuiLayer") {

	}
	ImGuiLayer::~ImGuiLayer() {

	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();


		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.f ? (time - m_Time) : (1.0f, 60.f);
		m_Time = time;
		static bool show = true;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
		ImGui::ShowDemoWindow(&show);
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnMosueButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleaseEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleaseEvent));
		dispatcher.Dispatch<MouseMoveEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnMouseMoveEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyTypeEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnKeyTypeEvent));
		dispatcher.Dispatch<KeyPressedEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleaseEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnKeyReleaseEvent));
		dispatcher.Dispatch<WindowResizeEvent>(QG_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	
	}

	bool ImGuiLayer::OnMosueButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e)
	{
		
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{

		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false; 
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypeEvent(KeyTypeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)(keycode));//»ñÈ¡ÊäÈë×Ö·û
		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		QG_CORE_INFO("{0} {1}", e.GetWidth(), e.GetHeight());
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}




}