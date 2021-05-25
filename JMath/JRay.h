#include "JPoint.h"
#include "JConstants.h"

class JRay {
public:
	JRay() : tMax(J_Infinity) {}

	JRay(const JPoint3f& oo, const JVector3f& dd, float t_max = J_Infinity) :
		o(oo), d(dd), tMax(t_max) {}

	JPoint3f operator()(float t)const
	{
		return o + d * t;
	}

	bool HasNaNs()const {
		return o.HasNaNs() || d.HasNaNs() || std::isnan(tMax);
	}

	friend std::ostream& operator<<(std::ostream& os, const JRay& r){
		os << "[o=" << r.O() << ", d=" << r.D() << ", tMax=" << r.T_MAX() << "]";
		return os;
	}

	JPoint3f O()const{
		return o;
	}

	JVector3f D()const{
		return d;
	}

	float T_MAX() const{
		return tMax;
	}

private:
	JPoint3f o;
	JVector3f d;
	mutable float tMax;

	//todo 
	//const Medium
};
