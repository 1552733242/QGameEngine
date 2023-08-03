#pragma once
#include "QGame/Core/Layer.h"
#include "QGame/Core/Core.h"
#include "QGame/Events/KeyEvent.h"
#include "QGame/Events/MouseEvent.h"
#include "QGame/Events/AppliccationEvent.h"

namespace QGame {


	class GAME_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach()override;
		virtual void OnDetach()override;
		virtual void OnImGuiRender()override;
		void Begin();
		void End();

	private: 
		float m_Time = 0.f;


	};


}