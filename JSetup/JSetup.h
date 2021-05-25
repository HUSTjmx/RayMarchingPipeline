class JSetup {
public:

	static JSetup& instance() {
		static JSetup* instance = new JSetup();
		return *instance;
	}

	float WIDTH = 1200.0f;
    float HEIGHT = 800.0f;

	float PIXEL_SIZE[2] = { 1.f / WIDTH,1.f / HEIGHT };


private:
	constexpr JSetup(){}
};