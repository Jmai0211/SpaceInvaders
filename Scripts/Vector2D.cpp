#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int _x, int _y)
{
	x = _x;
	y = _y;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Divide(vec);
}

Vector2D& Vector2D::operator*=(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0;
	this->y = 0;

	return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2)
{
	return v1.Add(v2);
}

Vector2D& operator-(Vector2D& v1, const Vector2D& v2)
{
	return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2)
{
	return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2)
{
	return v1.Divide(v2);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}
