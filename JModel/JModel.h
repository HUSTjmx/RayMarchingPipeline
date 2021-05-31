#include "JMaterial.h"
#include "JShape.h"
#include "JShapeProcessLine.h"
#include "JConstants.h"
#include "JShader.h"
#include <memory>
#include <vector>

enum class PatchPattern {
	Union,
	Intersection,
	Subtraction,
	Union_sm,
	Intersection_sm,
	Subtraction_sm,
};

class JPatchFactory
{
public:
	JPatchFactory() :render_id(0), current_id(0) {}

	float Patch(float d1, float d2, float k, PatchPattern pattern)
	{
		if (current_id == 0)return d2;

		switch (pattern)
		{
		case PatchPattern::Union:
			return opUnion(d1, d2);
			break;
		case PatchPattern::Intersection:
			return opIntersection(d1, d2);
			break;
		case PatchPattern::Subtraction:
			return opSubtraction(d1, d2);
			break;
		case PatchPattern::Union_sm:
			return opSmoothUnion(d1, d2, k);
			break;
		case PatchPattern::Intersection_sm:
			return opSmoothIntersection(d1, d2, k);
			break;
		case PatchPattern::Subtraction_sm:
			return opSmoothSubtraction(d1, d2, k);
			break;
		default:
			break;
		}
	}
	
	int getRenderID() {
		return render_id;
	}

	void setCurrentID(int i){
		current_id = i;
	}

	void setRenderID(int i) {
		render_id = i;
	}

	int current_id;

private:
	/*
	* <并>
	* <并集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	*/
	float opUnion(float d1, float d2) {
		//return std::min(d1, d2);
		if (d1 <= d2)
		{
			//std::cout << current_id << std::endl;
			return d1;
		}
		else {
			//
			render_id = current_id;
			return d2;
		}
	}

	/*
	* <交集>
	* <交集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	*/
	float opIntersection(float d1, float d2) {
		//return std::max(d1, d2);
		if (d1 >= d2)
			return d1;
		else {
			render_id = current_id;
			return d2;
		}
	}

	/*
	* <差集>
	* <差集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	*/
    float opSubtraction(float d1, float d2) {
		//return std::max(-d1, d2);
		if (-d1 > d2)
			return -d1;
		else {
			render_id = current_id;
			return d2;
		}
	}

	/*
	* <并>
	* <并集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	* @param [k][平滑程度]
	*/
	float opSmoothUnion(float d1, float d2, float k) {
		float h = std::clamp(0.5f + 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
		if (h < 0.5)render_id = current_id;
		return Jmix(d2, d1, h) - k * h * (1.0f - h);
	}

	/*
	* <交集>
	* <交集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	* @param [k][平滑程度]
	*/
	float opSmoothIntersection(float d1, float d2, float k) {
		float h = std::clamp(0.5f - 0.5f * (d2 - d1) / k, 0.0f, 1.0f);
		if (h < 0.5)render_id = current_id;
		return Jmix(d2, d1, h) + k * h * (1.0f - h);
	}

	/*
	* <差集>
	* <差集两个形状>
	* @param [d1][第一个形状的SDF]
	* @param [d2][第二个形状的SDF]
	* @param [k][平滑程度]
	*/
	float opSmoothSubtraction(float d1, float d2, float k) {
		float h = std::clamp(0.5f - 0.5f * (d2 + d1) / k, 0.0f, 1.0f);
		if (h < 0.5)render_id = current_id;
		return Jmix(d2, -d1, h) + k * h * (1.0f - h);
	}

private:
	int render_id;
};

class JModel {
public:
	void add(std::shared_ptr<JShape> js, std::shared_ptr<JMaterial> mat, std::shared_ptr<JShapeProcessLine> jpl, int p, float kk = 0.0f){
		shapes.push_back(js);
		material.push_back(mat);
		proLines.push_back(jpl);
		patchPatterns.push_back(static_cast<PatchPattern>(p));
		k.push_back(kk);
	}

	float SDF(const JPoint3f p){
		float sdf = J_MaxFloat;

		if (shapes.empty())return sdf;

		renderId = 0;

		for (int i = 0;i < shapes.size();i++)
		{
			jpf.setCurrentID(i);
			float d2 = proLines[i].get()->Do(p, *(shapes[i].get()));
			//std::cout << d2 << std::endl;
			
			sdf = jpf.Patch(sdf, d2, k[i], patchPatterns[i]);
		}
		renderId = jpf.getRenderID();
		//std::cout << renderId << std::endl;
		jpf.setCurrentID(0);
		jpf.setRenderID(0);
		return sdf;
	}

	int getRenderID() {
		return renderId;
	}

	std::shared_ptr<JMaterial> getRenderMat() const{
		return material[renderId];
	}

	std::shared_ptr<JShader> getRenderShader() {
		return shapes[renderId].get()->shader;
	}

private:
	std::vector<std::shared_ptr<JShape>> shapes;
	std::vector<std::shared_ptr<JMaterial>> material;
	std::vector<std::shared_ptr<JShapeProcessLine>> proLines;
	std::vector<PatchPattern> patchPatterns;
	std::vector<float> k;

	JPatchFactory jpf;
	int renderId;
};