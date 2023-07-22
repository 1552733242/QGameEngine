#pragma once
#include"QGame/Layer.h"
#include"QGame/Core.h"
#include"QGame/Events/KeyEvent.h"
#include"QGame/Events/MouseEvent.h"
#include"QGame/Events/AppliccationEvent.h"
namespace QGame {


	class GAME_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		bool OnMosueButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleaseEvent(MouseButtonReleaseEvent& e);
		bool OnMouseMoveEvent(MouseMoveEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleaseEvent(KeyReleaseEvent& e);
		bool OnKeyTypeEvent(KeyTypeEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private: 
		float m_Time = 0.f;


	};


}