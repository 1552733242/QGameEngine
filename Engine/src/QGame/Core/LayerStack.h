#pragma once
#include "QGame/Core/Core.h"
#include "QGame/Core/Layer.h"


#include<vector>

namespace QGame {
	
	class GAME_API LayerStack {
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* oberlay);
		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	private:
		std::vector<Layer*>m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}