#include"qgpch.h"
#include<QGame.h>
#include"QGame/ImGui/ImGuiLayer.h"
class ExampleLayer :public QGame::Layer {
public:
	ExampleLayer() :Layer("Example") {

	}
	void OnUpdate()override {
	
	}
	void OnEvent(QGame::Event& event)override {
	
	}
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