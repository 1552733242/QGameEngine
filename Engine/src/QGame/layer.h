#pragma once

#include"QGame/Core.h"
#include"QGame/Core/Timestep.h"
#include"QGame/Events/Event.h"


namespace QGame {

	class GAME_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();
		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnImGuiRender() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		inline const std::string& GetName()const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};



}