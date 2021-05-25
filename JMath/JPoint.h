#pragma once
#include <iostream>
#include "JVector.h"

template<typename T>
class JPoint2 {
public:
	JPoint2() :x(0), y(0) {}

	JPoint2(T xx, T yy) : x(xx), y(yy) {
		assert(!HasNaNs());
	}

	JPoint2(const JPoint2<T>& v) :x(v.X()), y(v.Y()) {}

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y);
	}

	JPoint2& operator=(const JPoint2<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const JPoint2<T>& v) {
		os << "[" << v.X() << "," << v.Y() << "]";
		return os;
	}

	JPoint2<T> operator+(const JPoint2<T>& v)const {
		ASSERT(!v.HasNaNs());
		return JPoint2<T>(X() + v.X(), Y() + v.Y());
	}

	JPoint2<T> operator+(const JVector2<T>& v)const {
		assert(!v.HasNaNs());
		return JPoint2<T>(X() + v.X(), Y() + v.Y());
	}

	JPoint2<T>& operator+=(const JPoint2<T>& v) {
		assert(!v.HasNaNs());
		x += v.X();
		y += v.Y();
		return *this;
	}

	JVector2<T> operator-(const JPoint2<T>& v)const {
		assert(!v.HasNaNs());
		return JVector2<T>(X() - v.X(), Y() - v.Y());
	}

	JPoint2<T>& operator-=(const JVector2<T>& v) {
		assert(!v.HasNaNs());
		x -= v.X();
		y -= v.Y();
		return *this;
	}

	JPoint2<T> operator*(const T f)const {
		return JPoint2<T>(x * f, y * f);
	}

	JPoint2<T> operator*(T (&a)[2])const {
		return JPoint2<T>(x * a[0], y * a[1]);
	}

	JPoint2<T>& operator*=(const T f) {
		x *= f;
		y *= f;
		return *this;
	}

	JPoint2<T> operator/(const T f)const {
		assert(f != 0);
		return JPoint2<T>(x / f, y / f);
	}

	JPoint2<T> operator/(T(&a)[2])const {
		return JPoint2<T>(x / a[0], y / a[1]);
	}

	JPoint2<T>& operator/=(const T f) {
		assert(f != 0);
		x /= f;
		y /= f;
		return *this;
	}

	JPoint2<T> operator-() const { return JPoint2<T>(-x, -y); }

	T operator[](int i)const {
		assert(i >= 0 && i <= 1);
		if (i == 0)return X();
		else return Y();
	}

	T& operator[](int i) {
		assert(i >= 0 && i <= 1);
		if (i == 0)return x;
		else return y;
	}

	bool operator==(const JPoint2<T>& v)const
	{
		return x == v.X() && y == v.Y();
	}

	bool operator!=(const JPoint2<T>& v)const
	{
		return x != v.X() || y != v.Y();
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
class JPoint3 {

public:
	JPoint3() :x(0), y(0), z(0) {}

	JPoint3(T xx, T yy, T zz) :x(xx), y(yy), z(zz) {}

	JPoint3(const JPoint3<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
	}

	JPoint3(const JVector3<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
	}

	bool HasNaNs() const {
		return std::isnan(x) || std::isnan(y) || std::isnan(z);
	}

	JPoint3<T>& operator=(const JPoint3<T>& v) {
		assert(!v.HasNaNs());
		x = v.X();
		y = v.Y();
		z = v.Z();
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const JPoint3<T>& v) {
		os << "[" << v.X() << "," << v.Y() << "," << v.Z() << "]";
		return os;
	}

	JPoint3<T> operator+(const JPoint3<T>& v) const
	{
		return JPoint3<T>(x + v.X(), y + v.Y(), z + v.Y());
	}

	JPoint3<T> operator+(const JVector3<T>& v) const
	{
		return JPoint3<T>(x + v.X(), y + v.Y(), z + v.Y());
	}

	JPoint3<T>& operator+=(const JPoint3<T>& v)
	{
		x += v.X();
		y += v.Y();
		z += v.Z();
		return *this;
	}

	JVector3<T> operator-(const JPoint3<T>& v) const
	{
		return JVector3<T>(x - v.X(), y - v.Y(), z - v.Y());
	}

	JPoint3<T>& operator-=(const JVector3<T>& v)
	{
		x -= v.X();
		y -= v.Y();
		z -= v.Z();
		return *this;
	}

	JPoint3<T> operator*(T f) const
	{
		return JPoint3<T>(x * f, y * f, z * f);
	}

	JPoint3<T>& operator*=(T f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	JPoint3<T> operator/(T f) const
	{
		assert(f != 0);
		return JPoint3<T>(x / f, y / f, z / f);
	}

	JPoint3<T>& operator/=(T f)
	{
		assert(f != 0);
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	bool operator==(const JPoint3<T>& v)const
	{
		return x == v.X() && y == v.Y() && z == v.Z();
	}

	bool operator!=(const JPoint3<T>& v)const
	{
		return x != v.X() || y != v.Y() || z != v.Z();
	}

	JPoint3<T> operator-()const
	{
		return JPoint3<T>(-x, -y, -z);
	}

	T operator[](int i)const {
		assert(i >= 0 && i <= 2);
		if (i == 0)return X();
		if (i == 1)return Y();
		else return Z();
	}

	T& operator[](int i) {
		assert(i >= 0 && i <= 2);
		if (i == 0)return X();
		if (i == 1)return Y();
		else return Z();
	}

	T X()const noexcept {
		return x;
	}

	T Y()const noexcept {
		return y;
	}

	T Z()const noexcept {
		return z;
	}

	JPoint2<T> XY()const noexcept {
		return JPoint2<T>(X(), Y());
	}

	JPoint2<T> XZ()const noexcept {
		return JPoint2<T>(X(), Z());
	}

private:
	T x, y, z;
};

using JPoint2f = JPoint2<float>;
using JPoint2i = JPoint2<int>;
using JPoint3f = JPoint3<float>;
using JPoint3i = JPoint3<int>;


template<typename T>
JPoint3<T> Lerp(float t, const JPoint3<T>& p1, const JPoint3<T>& p2) {
	return (1 - t) * p1 + t * p2;
}

template<typename T>
JPoint3<T> Floor(const JPoint3<T>& p)
{
	return JPoint3<T>(std::floor(p.X()), std::floor(p.Y()), std::floor(p.Z()));
}

template<typename T>
JPoint3<T> Ceil(const JPoint3<T>& p)
{
	return JPoint3<T>(std::Ceil(p.X()), std::Ceil(p.Y()), std::Ceil(p.Z()));
}

template<typename T>
JPoint3<T> Abs(const JPoint3<T>& p)
{
	return JPoint3<T>(std::abs(p.X()), std::abs(p.Y()), std::abs(p.Z()));
}

template<typename T>
JPoint3<T> Permute(const JPoint3<T>v, int x, int y, int z) {
	return JPoint3<T>(v[x], v[y], v[z]);
}

//×ª»¯º¯Êý
template<typename T>
JPoint3<T> V2P(const JVector3<T>& v)
{
	return JPoint3<T>(v);
}

template<typename T>
JVector3<T> P2V(const JPoint3<T>& p)
{
	return JVector3<T>(p.X(), p.Y(), p.Z());
}

template<typename T>
JPoint2<T> V2P(const JVector2<T>& v)
{
	return JPoint2<T>(v.X(), v.Y());
}

template<typename T>
JVector2<T> P2V(const JPoint2<T>& p)
{
	return JVector2<T>(p.X(), p.Y());
}

