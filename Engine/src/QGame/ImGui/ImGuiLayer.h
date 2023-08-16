#pragma once
#include "QGame/Core/Layer.h"
#include "QGame/Core/Core.h"
#include "QGame/Events/KeyEvent.h"
#include "QGame/Events/MouseEvent.h"
#include "QGame/Events/ApplicationEvent.h"

namespace QGame {


	class GAME_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnEvent(Event& event) override;
		virtual void OnImGuiRender()override;
		void Begin();
		void End();

		void SetBlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemColors();
	private: 
		bool m_BlockEvents = true;
		float m_Time = 0.f;


	};


}