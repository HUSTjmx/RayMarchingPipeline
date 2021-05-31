#pragma once

#include <assert.h>
#include <iostream>
#include "Eigen/Dense"
using namespace Eigen;

template<typename T>
class JVector2{
public:
	JVector2():x(0),y(0){}

	JVector2(T xx, T yy) : x(xx), y(yy){
		assert(!HasNaNs());
	}
	
	JVector2(const JVector2<T>& v):x(v.X()),y(v.Y()){}

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y);
	}

	JVector2& operator=(const JVector2<T>& v){
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const JVector2<T>& v){
		os << "[" << v.X() << "," << v.Y() << "]";
		return os;
	}

	JVector2<T> operator+(const JVector2<T>& v)const {
		assert(!v.HasNaNs());
		return JVector2<T>(X() + v.X(), Y() + v.Y());
	}

	JVector2<T> &operator+=(const JVector2<T>& v){
		assert(!v.HasNaNs());
		x += v.X();
		y += v.Y();
		return *this;
	}

	JVector2<T> operator-(const JVector2<T>& v)const {
		assert(!v.HasNaNs());
		return JVector2<T>(X() - v.X(), Y() - v.Y());
	}

	JVector2<T>& operator-=(const JVector2<T>& v){
		assert(!v.HasNaNs());
		x -= v.X();
		y -= v.Y();
		return *this;
	}

	JVector2<T> operator*(const T f)const {
		return JVector2<T>(x * f, y * f);
	}

	JVector2<T> operator*(T (&ar)[2])const{
		return JVector2<T>(x * ar[0], y * ar[1]);
	}
	
	JVector2<T>& operator*=(const T f){
		x *= f;
		y *= f;
		return *this;
	}

	JVector2<T> operator/(const T f)const {
		assert(f != 0);
		T inv = 1.0 / f;
		return JVector2<T>(x * inv, y / inv);
	}

	JVector2<T> operator/(T(&a)[2])const {
		return JVector2<T>(x / a[0], y / a[1]);
	}

	JVector2<T>& operator/=(const T f) {
		assert(f != 0);
		x /= f;
		y /= f;
		return *this;
	}

	JVector2<T> operator-(int) const { return JVector2<T>(-x, -y); }

	T operator[](int i)const{
		assert(i >= 0 && i <= 1);
		if (i == 0)return X();
		else return Y();
	}

	T& operator[](int i){
		assert(i >= 0 && i <= 1);
		if (i == 0)return x;
		else return y;
	}

	bool operator==(const JVector2<T>& v)const
	{
		return x == v.X() && y == v.Y();
	}

	bool operator!=(const JVector2<T>& v)const
	{
		return x != v.X() || y != v.Y();
	}

	float LengthSquared()const {
		return x * x + y * y;
	}

	float Length()const {
		return std::sqrt(LengthSquared());
	}

	T X()const noexcept {
		return x;
	}

	T Y()const noexcept {
		return y;
	}

private:
	T x, y;
};

template<typename T>
class JVector3 {

public:
	JVector3():x(0),y(0),z(0){}
	
	JVector3(T xx,T yy,T zz):x(xx),y(yy),z(zz){}

	JVector3(T xx) :x(xx), y(xx), z(xx) {}

	JVector3(const JVector3<T>& v){
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
	}
	
	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	JVector3<T>& operator=(const JVector3<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const JVector3<T>& v){
		os << "[" << v.X() << "," << v.Y() << "," << v.Z() << "]";
		return os;
	}

	JVector3<T> operator+(const JVector3<T> &v) const
	{
		return JVector3<T>(x + v.X(), y + v.Y(), z + v.Z());
	}

	JVector3<T>& operator+=(const JVector3<T>& v)
	{
		x += v.X();
		y += v.Y();
		z += v.Z();
		return *this;
	}

	JVector3<T> operator-(const JVector3<T>& v) const
	{
		return JVector3<T>(x - v.X(), y - v.Y(), z - v.Z());
	}

	JVector3<T>& operator-=(const JVector3<T>& v)
	{
		x -= v.X();
		y -= v.Y();
		z -= v.Z();
		return *this;
	}

	JVector3<T> operator*(T f) const
	{
		return JVector3<T>(x * f, y * f, z * f);
	}

	JVector3<T> operator*(const JVector3<T>& v) const
	{
		return JVector3<T>(x * v.X(), y * v.Y(), z * v.Z());
	}

	JVector3<T>& operator*=(T f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	JVector3<T> operator/(T f) const
	{
		assert(f != 0);
		return JVector3<T>(x / f, y / f, z / f);
	}

	JVector3<T> operator/(const JVector3<T> v)const {
		assert(!v.HasNaNs());
		return JVector3<T>(x / v.X(), y / v.Y(), z / v.Z());
	}

	JVector3<T>& operator/=(T f)
	{
		assert(f != 0);
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	bool operator==(const JVector3<T>& v)const
	{
		return x == v.X() && y == v.Y() && z == v.Z();
	}

	bool operator!=(const JVector3<T>& v)const
	{
		return x != v.X() || y != v.Y() || z != v.Z();
	}

	JVector3<T> operator-()const
	{
		return JVector3<T>(-x, -y, -z);
	}

	T operator[](int i)const {
		assert(i >= 0 && i <= 2);
		if (i == 0)return x;
		if (i == 1)return y;
		else return z;
	}

	T& operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0)return x;
		if (i == 1)return y;
		else return z;
	}

	float LengthSquared()const {
		return x * x + y * y + z * z;
	}

	float Length()const {
		return std::sqrt(LengthSquared());
	}


	T X(int i = 0)const noexcept {
		return x;
	}

	T Y(int i = 0)const noexcept {
		return y;
	}

	T Z(int i = 0)const noexcept {
		return z;
	}

	JVector2<T> XZ() const noexcept {
		return JVector2<T>(x, z);
	}

private:
	T x, y, z;
};

template<typename T>
class JVector4 {

public:
	JVector4() :x(0), y(0), z(0), w(0) {}

	JVector4(T xx, T yy, T zz, T ww) :x(xx), y(yy), z(zz), w(ww) {}

	JVector4(const JVector4<T>& v) {
		assert(v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
		w = v.W();
	}

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w);
	}

	JVector4<T>& operator=(const JVector4<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
		w = v.W();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const JVector4<T>& v) {
		os << "[" << v.X() << "," << v.Y() << "," << v.Z() << "," << v.W() << "]";
		return os;
	}

	JVector4<T> operator+(const JVector4<T>& v) const
	{
		return JVector4<T>(x + v.X(), y + v.Y(), z + v.Z(), w + v.W());
	}

	JVector4<T>& operator+=(const JVector4<T>& v)
	{
		x += v.X();
		y += v.Y();
		z += v.Z();
		w += v.W();
		return *this;
	}

	JVector4<T> operator-(const JVector4<T>& v) const
	{
		return JVector4<T>(x - v.X(), y - v.Y(), z - v.Z(), w - v.W());
	}

	JVector4<T>& operator-=(const JVector4<T>& v)
	{
		x -= v.X();
		y -= v.Y();
		z -= v.Z();
		w -= v.W();
		return *this;
	}

	JVector4<T> operator*(T f) const
	{
		return JVector4<T>(x * f, y * f, z * f, w * f);
	}

	JVector4<T>& operator*=(T f)
	{
		x *= f;
		y *= f;
		z *= f;
		w *= f;
		return *this;
	}

	JVector4<T> operator/(T f) const
	{
		assert(f != 0);
		return JVector4<T>(x / f, y / f, z / f, w / f);
	}

	JVector4<T>& operator/=(T f)
	{
		assert(f != 0);
		x /= f;
		y /= f;
		z /= f;
		w /= f;
		return *this;
	}

	bool operator==(const JVector4<T>& v)const
	{
		return x == v.X() && y == v.Y() && z == v.Z() && w == v.W();
	}

	bool operator!=(const JVector4<T>& v)const
	{
		return x != v.X() || y != v.Y() || z != v.Z() || w != v.W();
	}

	JVector4<T> operator-()const
	{
		return JVector4<T>(-x, -y, -z, -w);
	}

	T operator[](int i)const {
		assert(i >= 0 && i <= 3);
		if (i == 0)return x;
		if (i == 1)return y;
		if (i == 2)return z;
		else return w;
	}

	T& operator[](int i) {
		assert(i >= 0 && i <= 3);
		if (i == 0)return x;
		if (i == 1)return y;
		if (i == 2)return z;
		else return w;
	}

	float LengthSquared()const {
		return x * x + y * y + z * z + w * w;
	}

	float Length()const {
		return std::sqrt(LengthSquared());
	}


	T X(int i = 0)const noexcept {
		return x;
	}

	T Y(int i = 0)const noexcept {
		return y;
	}

	T Z(int i = 0)const noexcept {
		return z;
	}

	T W(int i = 0)const noexcept {
		return w;
	}

private:
	T x, y, z, w;
};


using JVector2f = JVector2<float>;
using JVector2i = JVector2<int>;
using JVector3f = JVector3<float>;
using JVector3i = JVector3<int>;
using JVector4f = JVector4<float>;
using JVector4i = JVector4<int>;

const JVector3f const_v3f(0.0f, 0.0f, 0.0f);

//点乘
template<typename T>
inline T Dot(const JVector2<T>& v1, const JVector2<T>& v2) {
	return v1.X() * v2.X() + v1.Y() * v2.Y();
}

template<typename T>
inline T AbsDot(const JVector2<T>& v1, const JVector2<T>& v2) {
	return std::abs(Dot(v1, v2));
}

template<typename T>
inline T Dot(const JVector3<T>& v1, const JVector3<T>& v2) {
	return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z();
}

template<typename T>
inline T AbsDot(const JVector3<T>& v1, const JVector3<T>& v2) {
	return std::abs(Dot(v1, v2));
}

template<typename T>
inline T Dot(const JVector4<T>& v1, const JVector4<T>& v2) {
	return v1.X() * v2.X() + v1.Y() * v2.Y() + v1.Z() * v2.Z() + v1.W() * v2.W();
}

template<typename T>
inline T AbsDot(const JVector4<T>& v1, const JVector4<T>& v2) {
	return std::abs(Dot(v1, v2));
}

namespace JMX {
	//叉乘
	template<typename T>
	inline JVector3<T> Cross(const JVector2<T>& v1, const JVector2<T>& v2)
	{
		double v1x = v1.X(), v1y = v1.Y();
		double v2x = v2.X(), v2y = v2.Y();
		double z = v1x * v2y - v2x * v1y;
		return JVector3<T>(0, 0, z);
	}

	template<typename T>
	inline JVector3<T> Cross(const JVector3<T>& v1, const JVector3<T>& v2) {
		double v1x = v1.X(), v1y = v1.Y(), v1z = v1.Z();
		double v2x = v2.X(), v2y = v2.Y(), v2z = v2.Z();
		return JVector3<T>((v1y * v2z) - (v1z * v2y),
			(v1z * v2x) - (v1x * v2z),
			(v1x * v2y) - (v1y * v2x));
	}
}


//正则化
template<typename T>
inline JVector2<T> Normalize(const JVector2<T>& v) {
	return v / v.Length();
}

template<typename T>
inline JVector3<T> Normalize(const JVector3<T>& v) {
	return v / v.Length();
}

template<typename T>
inline JVector4<T> Normalize(const JVector4<T>& v) {
	return v / v.Length();
}


//最大、小成分
template<typename T>
T MinComponent(const JVector3<T>& v)
{
	return std::min(v.X(), std::min(v.Y(), v.Z()));
}

template<typename T>
T MaxComponent(const JVector3<T>& v)
{
	return std::max(v.X(), std::max(v.Y(), v.Z()));
}

//最大，最小
template<typename T>
JVector3<T> Min(const JVector3<T>& v, float i) {
	return JVector3<T>(std::min(v.X(), i), std::min(v.Y(), i), std::min(v.Z(), i));
}

template<typename T>
JVector3<T> Max(const JVector3<T>& v, float i) {
	return JVector3<T>(std::max(v.X(), i), std::max(v.Y(), i), std::max(v.Z(), i));
}

template<typename T>
JVector2<T> Min(const JVector2<T>& v, float i) {
	return JVector2<T>(std::min(v.X(), i), std::min(v.Y(), i));
}

template<typename T>
JVector2<T> Max(const JVector2<T>& v, float i) {
	return JVector2<T>(std::max(v.X(), i), std::max(v.Y(), i));
}



//向量重排
template<typename T>
JVector2<T> Permute(const JVector2<T> &v, int x, int y) {
	return JVector2<T>(v[x], v[y]);
}

template<typename T>
JVector3<T> Permute(const JVector3<T> &v, int x, int y, int z) {
	return JVector3<T>(v[x], v[y], v[z]);
}


template<typename T>
JVector4<T> Permute(const JVector4<T> &v, int x, int y, int z, int w) {
	return JVector4<T>(v[x], v[y], v[z], v[w]);
}

//abs
template<typename T>
JVector2<T> Abs(const JVector2<T>& v)
{
	return JVector2<T>(std::abs(v.X()), std::abs(v.Y()));
}

template<typename T>
JVector3<T> Abs(const JVector3<T>& v)
{
	return JVector3<T>(std::abs(v.X()), std::abs(v.Y()), std::abs(v.Z()));
}

//Pow
template<typename T>
JVector3<T> Pow(const JVector3<T>& v, T f) {
	return JVector3<T>(std::pow(v.X(), f), std::pow(v.Y(), f), std::pow(v.Z(), f));
}

//length
template<typename T>
float Length(const JVector3<T>& v) {
	return v.Length();
}

template<typename T>
float Length(const JVector2<T>& v) {
	return v.Length();
}

//JVector、Eigen Vector 相互转换
JVector3f Ev2Jv(const Vector3f& v) {
	return JVector3f(v[0], v[1], v[2]);
}

Vector3f Jv2Ev(const JVector3f& v) {
	return Vector3f(v[0], v[1], v[2]);
}

//对于法线
template<typename T>
inline JVector3<T> Faceforward(const JVector3<T>& n, const JVector3<T>& v)
{
	return (Dot(n, v) < 0.f) ? -n, n;
}

