#pragma once
#ifdef  GAME_PLATFORM_WINDOWS

extern QGame::Application* QGame::CreateApplication();

int main(int argc, char** argv) {

	QGame::Log::Init();
	int a = 5;
	auto app = QGame::CreateApplication();
	app->Run();
	delete app;
}
#endif