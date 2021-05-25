// RayMarchingPipeline.cpp: 定义应用程序的入口点。
//

#include "RayMarchingPipeline.h"
#include "JVector.h"
#include "JShape.h"
#include "JTransform.h"
#include "JShapeProcessLine.h"
#include "JIntegrator.h"

//using namespace Eigen;
using namespace std;

int main()
{
	Matrix4f m;
	JTransform tm(m);
	JPoint3f a(0.0f, 0.0f, 0.0f);
	JShape3D* s1 = new JSphere(a, 1.0);

	std::shared_ptr<ShapeDecorator> sd1 = std::make_shared<opScale>(2.);
	std::shared_ptr<ShapeDecorator> sd2 = std::make_shared<opScale>(0.5);

	JShapeProcessLine spl;
	spl.add(sd1);
	//spl.add(sd2);

	JPoint3f p(0.0f, 2.0f, 0.0f);

	float sdf = spl.Do(p, *s1);

	std::cout << sdf << " | "<< s1->sdFunc(p) << endl;

	/*-----------------------------------------*/
	JSample sample{};
	sample.init();
	JCamera camera(JVector3f(0.0f, 0.0f, -1.0f), JVector3f(0.0f, 0.0f, 1.0f), 0.0f);
	//std::cout<< sample.getSampleAuto()<< std::endl;
	
	JIntegrator integrator(sample, camera);
	std::cout<<integrator.Render(JPoint2f(3.0f, 3.0f))<<std::endl;

	std::cout << "Hello CMake." << endl;
	int c;
	cin >> c;
	return 0;
}
