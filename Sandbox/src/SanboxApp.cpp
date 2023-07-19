#include <QGame.h>

class Sanbox :public QGame::Application {
public:
	Sanbox() {}
	~Sanbox() {}
};

QGame::Application* QGame::CreateApplication() {

	return new Sanbox();
}