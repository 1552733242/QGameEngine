#pragma once

//#include"WindowsWindow.h"
#include<QGame/Input.h>


namespace QGame {
	class  GAME_API WindowInput :public Input {
	
	protected:
		virtual bool IsKeyPressedImpl(int keycode)override;
			
		virtual bool IsMousePressedImpl(int button) override;
		virtual float GetMouseXImpl()override;
		virtual float GetMouseYImpl()override;
		virtual std::pair<float, float> GetMousePositionImpl()override;
	};


}