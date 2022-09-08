#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Plane.h"
#include "Player.h"
#include "Button.h"
#include "Label.h"

const float PHYICS_TIMESTEP = 1.0f / 60.0f;

class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;

	Plane* m_pPlaneSprite{};
	Player* m_pPlayer{};

	/*X1, Y1 = position of parametric simulation object
X2, Y2 = position of iterative simulation object
t = game time, in seconds (time since play scene began)
dt = delta time, in seconds (time since last frame)
a = variable.
b = variable.
c = variable.
d = variable.*/

	float x1 = 0;
	float y1 = 0;

	float x2 = 0;
	float y2 = 0;

	float t = 0.0f;
	float dt = PHYICS_TIMESTEP;
	float frequency = 1.0f;
	float amplitude = 100.0f;
	float offsetY = 100.0f;
	float offsetX = 100.0f;

	// UI Items
	Button* m_pBackButton{};
	Button* m_pNextButton{};
	Label* m_pInstructionsLabel{};

	// Input Control
	void GetKeyboardInput();
};

#endif /* defined (__PLAY_SCENE__) */