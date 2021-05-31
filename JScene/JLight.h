#include "JPoint.h"

class JLight {
public:
	JLight(): color(JVector3f(0.0f,0.0f,0.0f)){}
	JLight(const JVector3f& col) : color(col){}

	virtual JVector3f getCol(const JPoint3f& p) {
		return color;
	}
	virtual JVector3f getDir(const JPoint3f& p) {
		return JVector3f(0.0,0.0,0.0);
	}

private:
	JVector3f color;
};

class JPointLight : public JLight {
	JPointLight(const JVector3f& col, const JPoint3f& pos, float r1, float r2) :
		JLight(col), pos(pos), inRadius(r1), outRadius(r2) {}

	virtual JVector3f getCol(const JPoint3f& p) {
		return JLight::getCol(p);
	}
	
	virtual JVector3f getDir(const JPoint3f& p){
		return Normalize(p - pos);
	}

private:
	JPoint3f pos;
	float inRadius;
	float outRadius;
};

class JPunctalLight : public JLight{
public:
	JPunctalLight(const JVector3f col, JVector3f dir) :JLight(col), dir(Normalize(dir)) {}

	virtual JVector3f getDir(const JPoint3f& p)override {
		return dir;
	}
private:
	JVector3f dir;
};

class JSky : public JLight {
public:
	JSky() :sundir(JVector3f(0.0, -1.0, 0.0)) {}
	JSky(const JVector3f& sundir) : sundir(sundir) {}

	virtual JVector3f getCol(const JVector3f& rd) {
		JVector3f col = JVector3f(0.3, 0.5, 0.85);
		return col;
	}
private:
	JVector3f sundir;
};