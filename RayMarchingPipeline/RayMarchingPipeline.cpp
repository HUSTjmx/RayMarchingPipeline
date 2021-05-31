// RayMarchingPipeline.cpp: 定义应用程序的入口点。
//

#include "RayMarchingPipeline.h"
#include "JVector.h"
#include "JShape.h"
#include "JTransform.h"
#include "JShapeProcessLine.h"
#include "JIntegrator.h"
#include "JFilm.h"
#include "svpng.inc"
#include "JShader.h"

//using namespace Eigen;
using namespace std;

int main()
{
	JModel model1;
	auto shape1 = std::make_shared<JSphere>(JPoint3f(0.0, 0.0, 6.0), 0.7);
	shape1.get()->setShader(phongShader);

	auto shape2 = std::make_shared<JSphere>(JPoint3f(2.0, 2.0, 6.0), 1.0);
	shape2.get()->setShader(phongShader);

	model1.add(shape1,
		std::make_shared<JMaterial>(JVector3f(0.4,0.0,0.0),1.0),
		std::make_shared<JShapeProcessLine>(),
		0
		);
	model1.add(shape2,
		std::make_shared<JMaterial>(JVector3f(0.0, 0.6, 0.0), 1.0),
		std::make_shared<JShapeProcessLine>(),
		0
	);

	auto m1 = std::make_shared<JModel>(model1);

	/*-----------------------------------------*/
	JScene scene;
	scene.addActor(m1);

	auto dirL1 = std::make_shared<JPunctalLight>(JVector3f(0.8,0.6,0.8), JVector3f(0.0,0.0,1.0));
	scene.addLight(dirL1);

	JSample sample{};
	sample.init();
	JCamera camera(JVector3f(0.0f, 0.0f, -1.0f), JVector3f(0.0f, 0.0f, 1.0f), 0.0f);
	JIntegrator integrator(sample, camera);

	JFilm film;
	film.Do(integrator, scene);
	film.ToPPM("C:\\Users\\ZoroD\\Desktop\\2222\\Image.ppm");



}
