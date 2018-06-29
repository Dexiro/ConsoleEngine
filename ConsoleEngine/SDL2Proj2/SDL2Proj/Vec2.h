#pragma once
#include <math.h>

static const long double PI = 3.141592653589793238L;

struct Vec2
{
	float x, y;

	Vec2(){ x = 0.0f; y = 0.0f; }
	Vec2(float _x, float _y){ x = _x; y = _y; }

	Vec2 operator+(const Vec2& v)	{ return Vec2{ this->x + v.x, this->y + v.y }; }
	Vec2 operator-(const Vec2& v)	{ return Vec2{ this->x - v.x, this->y - v.y }; }
	Vec2 operator*(const float f)	{ return Vec2{ this->x * f, this->y * f }; }
	Vec2 operator/(const float f)	{ return Vec2{ this->x / f, this->y / f }; }

	void operator+=(const Vec2& v)	{ this->x += v.x; this->y += v.y; }
	void operator-=(const Vec2& v)	{ this->x -= v.x; this->y -= v.y; }
	void operator*=(const float& f)	{ this->x *= f; this->y *= f; }
	void operator/=(const float& f)	{ this->x /= f; this->y /= f; }

	float LengthSqr(){ return x * x + y * y; }
	float Length(){ return sqrt( LengthSqr() ); }
	
	float Sqr(float f){ return f*f; }
	float DistanceSqr(const Vec2 & v){ return Sqr(x - v.x) + Sqr(y - v.y); }
	float Distance(const Vec2 & v){ return sqrt( DistanceSqr(v) ); }
	
	static float DegToRad(float deg){ return deg * PI / 180; }
	static float RadToDeg(float rad){ return rad * 180 / PI; }

	void Rotate(const float& angle)
	{
		float theta = DegToRad(angle);
		float cs = cos(theta);
		float sn = sin(theta);

		float px = x * cs - y * sn;
		float py = x * sn + y * cs;

		x = px;
		y = py;
	}

	void Zero(){ x = 0.0f; y = 0.0f; }

	Vec2& Normalize()
	{
		if (Length() != 0)
		{
			float length = Length();
			x /= length; y /= length;
		}
		else
		{
			x = y = 0;
		}

		return *this;
	}

};