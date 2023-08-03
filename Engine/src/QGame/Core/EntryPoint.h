#pragma once
#ifdef  GAME_PLATFORM_WINDOWS

extern QGame::Application* QGame::CreateApplication();

int main(int argc, char** argv) {

	QGame::Log::Init();

	QG_PROFILE_BEGIN_SESSION("Startup", "QGameProfile-Startup.json");
	auto app = QGame::CreateApplication();
	QG_PROFILE_END_SESSION();
	
	QG_PROFILE_BEGIN_SESSION("Runtime", "QGameProfile-Runtime.json");
	app->Run();
	QG_PROFILE_END_SESSION();
	
	QG_PROFILE_BEGIN_SESSION("Shutdown", "QGameProfile-Shutdown.json");
	delete app;
	QG_PROFILE_END_SESSION();
}
#endif