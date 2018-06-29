#pragma once
#include <math.h>

static const long double PI = 3.141592653589793238L;

struct Vec2I
{
	int x, y;

	Vec2I(){ x = 0; y = 0; }
	Vec2I(int _x, int _y){ x = _x; y = _y; }

	Vec2I operator+(const Vec2I& v)	{ return Vec2I{ this->x + v.x, this->y + v.y }; }
	Vec2I operator-(const Vec2I& v)	{ return Vec2I{ this->x - v.x, this->y - v.y }; }
	Vec2I operator*(const int i)	{ return Vec2I{ this->x * i, this->y * i }; }
	Vec2I operator/(const int i)	{ return Vec2I{ this->x / i, this->y / i }; }

	void operator+=(const Vec2I& v)	{ this->x += v.x; this->y += v.y; }
	void operator-=(const Vec2I& v)	{ this->x -= v.x; this->y -= v.y; }
	void operator*=(const int& i)	{ this->x *= i; this->y *= i; }
	void operator/=(const int& i)	{ this->x /= i; this->y /= i; }

	int LengthSqr(){ return x * x + y * y; }
	float Length(){ return sqrt((float)LengthSqr()); }

	Vec2I& Normalize()
	{
		if (Length() != 0)
		{
			float length = Length();
			x = (int)ceil(((float)x / length)); 
			y = (int)ceil(((float)y / length));
		}
		else
		{
			x = y = 0;
		}

		return *this;
	}

	Vec2I& Zero(){ x = 0; y = 0; return *this; }
	bool IsZero(){ return (x == 0 && y == 0); }
};

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