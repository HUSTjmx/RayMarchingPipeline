#pragma once

class JSetup {
public:

	static JSetup& instance() {
		static JSetup* instance = new JSetup();
		return *instance;
	}

	float WIDTH = 400.0f;
    float HEIGHT = 400.0f;

	float PIXEL_SIZE[2] = { 1.f / WIDTH,1.f / HEIGHT };

	int MAX_STEP = 200;

	float RAY_MAX = 80.0;

	float ambient = 0.04;


private:
	constexpr JSetup(){}
};