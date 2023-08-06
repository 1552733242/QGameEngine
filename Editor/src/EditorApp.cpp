#include "qgpch.h"
#include <QGame.h>
#include <QGame/Core/EntryPoint.h>
#include "EditorLayer.h"

namespace QGame {

	class Editor :public Application {
	public:
		Editor() 
		: Application("Editor") {
			PushLayer(new EditorLayer());
		}
		~Editor() {}
	};

	Application* CreateApplication() {

		return new Editor();
	}

}