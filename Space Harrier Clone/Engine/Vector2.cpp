#include "Vector2.h"

#define _USE_MATH_DEFINES
#include <cmath>


Vector2::Vector2() : x(0), y(0)
{
}


Vector2::Vector2(float x, float y) : x(x), y(y)
{
}


float Vector2::getLength() const
{
	return sqrt(getLengthSquared());
}


float Vector2::getLengthSquared() const
{
	return x * x + y * y;
}


Vector2 Vector2::normalized() const
{
	float length = getLength();
	if (length == 0)
	{
		return *this;
	}
	return *this / length;
}


void Vector2::normalize()
{
	float length = getLength();
	if (length == 0)
	{
		return;
	}
	x /= length;
	y /= length;
}


void Vector2::rotateCCWDegrees(float degrees)
{
	// To rotate a vector counter-clockwise (CCW) by an angle
	// the following theorem is applied (for CCW rotation):
	// x2 = x1 * cosf(theta) - y1 * sinf(theta)
	// y2 = x1 * sinf(theta) + y1 * cosf(theta)
	rotateCCWRadians((float)M_PI / 180 * degrees);
}


void Vector2::rotateCCWRadians(float radians)
{
	// To rotate a vector counter-clockwise (CCW) by an angle
	// the following theorem is applied (for CCW rotation):
	// x2 = x1 * cosf(theta) - y1 * sinf(theta)
	// y2 = x1 * sinf(theta) + y1 * cosf(theta)
	float sinRot = sinf(radians);
	float cosRot = cosf(radians);

	float oldX = x;
	float oldY = y;

	x = oldX * cosRot - oldY * sinRot;
	y = oldX * sinRot + oldY * cosRot;
}


Vector2& Vector2::operator+=(const Vector2 & rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return *this;
}


Vector2& Vector2::operator-=(const Vector2 & rhs)
{
	this->x -= x;
	this->y -= y;
	return *this;
}


Vector2& Vector2::operator*=(float num)
{
	this->x *= num;
	this->y *= num;
	return *this;
}


Vector2& Vector2::operator/=(float num)
{
	this->x /= num;
	this->y /= num;
	return *this;
}


float Vector2::distance(const Vector2 & lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y).getLength();
}


float Vector2::dot(const Vector2 & lhs, const Vector2 & rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y);
}


Vector2 operator-(const Vector2 & v2)
{
	return Vector2(-v2.x, -v2.y);
}


Vector2 operator+(const Vector2& lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}


Vector2 operator-(const Vector2& lhs, const Vector2 & rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}


Vector2 operator*(float num, const Vector2 & v2)
{
	return Vector2(v2.x * num, v2.y * num);
}


Vector2 operator/(float num, const Vector2 & v2)
{
	return Vector2(v2.x / num, v2.y / num);
}


Vector2 operator*(const Vector2& v2, float num)
{
	return operator*(num, v2);
}


Vector2 operator/(const Vector2& v2, float num)
{
	return operator/(num, v2);
}


bool operator==(const Vector2 & lhs, const Vector2 & rhs)
{
	return (lhs.x == rhs.x && lhs.y == rhs.y);
}


bool operator!=(const Vector2 & lhs, const Vector2 & rhs)
{
	return !(lhs == rhs);
}
