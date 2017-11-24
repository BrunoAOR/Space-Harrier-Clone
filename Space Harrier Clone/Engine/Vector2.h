#ifndef H_VECTOR2
#define H_VECTOR2


class Vector2 final
{
	friend Vector2 operator- (const Vector2& v2);
	friend Vector2 operator+ (const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator- (const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator* (float num, const Vector2& v2);
	friend Vector2 operator/ (float num, const Vector2& v2);
	friend Vector2 operator* (const Vector2& v2, float num);
	friend Vector2 operator/ (const Vector2& v2, float num);
	friend bool operator== (const Vector2& lhs, const Vector2& rhs);
	friend bool operator!= (const Vector2& lhs, const Vector2& rhs);

public:
	Vector2();
	Vector2(float x, float y);

	float getLength() const;
	float getLengthSquared() const;
	Vector2 normalized() const;
	void normalize();
	void rotateCCWDegrees(float degrees);
	void rotateCCWRadians(float radians);

	Vector2& operator+= (const Vector2& rhs);
	Vector2& operator-= (const Vector2& rhs);
	Vector2& operator*= (float num);
	Vector2& operator/= (float num);

	static float distance(const Vector2& lhs, const Vector2& rhs);
	static float dot(const Vector2& lhs, const Vector2& rhs);

	float x;
	float y;
};


#endif // !H_VECTOR2
