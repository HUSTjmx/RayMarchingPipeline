#pragma once
#include <fstream>
#include <iostream>
#include "JVector.h"
#include "JSetup.h"
#include "JIntegrator.h"
class JFilm {
public:
	JFilm() :width(JSetup::instance().WIDTH), height(JSetup::instance().HEIGHT) {}

	void Do(JIntegrator& ji, JScene& scene) {
		for (int i = -width / 2;i < width/2;i++) {
			std::vector<JVector3f>temp;
			for (int j = -height / 2;j < height / 2;j++) {
				JVector3f a = ji.Render(JPoint2f(i, j), scene);
				temp.push_back(a);
				//std::cout << a << std::endl;
			}
			film.push_back(temp);
		}
	}

	void ToPPM(string address){
		std::ofstream OutImage;
		OutImage.open(address);
		std::cout << "xxxx" << std::endl;
		OutImage << "P3\n" << width << ' ' << height << "\n255\n";
		for(int i=0;i<film.size();i++)
			for (int j = 0;j < film[0].size();j++) {
				float r = film[i][j].X() * 255.99;
				float g = film[i][j].Y() * 255.99;
				float b = film[i][j].Z() * 255.99;
				OutImage << (int)r << ' ' << (int)g << ' ' << (int)b << std::endl;
			}
	}

	std::vector<std::vector<JVector3f>> film;

private:
	int width;
	int height;
};