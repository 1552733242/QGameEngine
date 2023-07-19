#pragma once
#ifdef  GAME_PLATFORM_WINDOWS

extern QGame::Application* QGame::CreateApplication();

int main(int argc, char** argv) {

	QGame::Log::Init();
	QG_CORE_WARN("hello!!!!");
	int a = 5;
	QG_INFO("YEs!!!! Var = {0}", a);
	auto app = QGame::CreateApplication();
	app->Run();
	delete app;
}
#endif