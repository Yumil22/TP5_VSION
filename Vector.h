#pragma once
struct Vector
{
	double x;
	double y;
	double z;


	Vector(double = 0, double = 0, double = 0);
	Vector(const Vector&);


	Vector& operator=(const Vector&);

	bool operator==(const Vector&) const;
	bool operator!=(const Vector&) const;

	Vector& operator+=(const Vector&);
	Vector operator+(const Vector&) const;

	Vector& operator-=(const Vector&);
	Vector operator-(const Vector&) const;
	Vector operator-() const;

	Vector& operator*=(const double);
	Vector operator*(const double) const;
	friend Vector operator*(const double, const Vector&);

	Vector& operator/=(const double);
	Vector operator/(const double)const;

	Vector operator*(const Vector&) const;
	Vector& operator*=(const Vector&);

	double Dot(const Vector&) const;

	double Length() const;
	Vector& Normalize(Vector = Vector());

	Vector& Damp(const Vector&, double, double);

	Vector& Flat();
};