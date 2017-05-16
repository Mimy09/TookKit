// ################################################################## //
// ##							TOOL KIT						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 May 05 - AIE			   ## //
// ################################################################## //
#pragma once
#include "tkVector.h"

#define TK_POS(x, y, size) x + (y * size)

// -------------------------- MATRIX 2 -------------------------- //
class Matrix2 {
public:
	// Default Constructor
	Matrix2();
	// Copy Constructor
	Matrix2(
		float f1, float f2,
		float f3, float f4);
	// Deconstructor
	~Matrix2();
	
	
	inline operator float*() { return data; }
	// Overloaded subscript operator
	Vector2& operator[] (int index);
	// Overloaded multiplication operator with Vector2
	Vector2 operator*(Vector2 other);
	// Overloaded multiplication operator with Matrix2
	Matrix2 operator*(Matrix2 other);

	// Sets the rotation of the vector
	void setRotate(float angle);

	// Sets the Matrix2 back to an Identity Matrix
	// [ 1 : 0 ]
	// [ 0 : 1 ]
	void identity();

private:
	// Array of floats to store all the Matrix2 data
	float* data;
};

// -------------------------- MATRIX 3 -------------------------- //
class Matrix3 {
public:
	// Default Constructor
	Matrix3();
	// Copy Constructor
	Matrix3(
		float f1, float f2, float f3,
		float f4, float f5, float f6,
		float f7, float f8, float f9);
	// Deconstructor
	~Matrix3();

	inline operator float*() { return data; }
	// Overloaded subscript operator
	Vector3 &operator[] (int index);
	// Overloaded multiplication operator with Vector3
	Vector3 operator*(Vector3 other);
	// Overloaded multiplication operator with Matrix3
	Matrix3 operator*(Matrix3 other);

	// Sets the rotation of the Vector3 on X axis
	void setRotateX(float angle);
	// Sets the rotation of the Vector3 on Y axis
	void setRotateY(float angle);
	// Sets the rotation of the Vector3 on Z axis
	void setRotateZ(float angle);

	// Sets the Matrix3 back to an Identity Matrix
	// [ 1 : 0 : 0 ]
	// [ 0 : 1 : 0 ]
	// [ 0 : 0 : 1 ]
	void identity();

private:
	// Array of floats to store all the Matrix3 data
	float* data;
};

// -------------------------- MATRIX 4 -------------------------- //
class Matrix4 {
public:
	// Default Constructor
	Matrix4();
	// Copy Constructor
	Matrix4(
		float f1, float f2, float f3, float f4,
		float f5, float f6, float f7, float f8,
		float f9, float f10, float f11, float f12,
		float f13, float f14, float f15, float f16);
	// Deconstructor
	~Matrix4();

	inline operator float*() { return data; }
	// Overloaded subscript operator
	Vector4 &operator[] (int index);
	// Overloaded multiplication operator with Vector4
	Vector4 operator*(Vector4 other);
	// Overloaded multiplication operator with Matrix4
	Matrix4 operator*(Matrix4 other);

	// Sets the rotation of the Vector4 on X axis
	void setRotateX(float angle);
	// Sets the rotation of the Vector4 on Y axis
	void setRotateY(float angle);
	// Sets the rotation of the Vector4 on Z axis
	void setRotateZ(float angle);
	
	// Sets the Matrix4 back to an Identity Matrix
	// [ 1 : 0 : 0 : 0 ]
	// [ 0 : 1 : 0 : 0 ]
	// [ 0 : 0 : 1 : 0 ]
	// [ 0 : 0 : 0 : 1 ]
	void identity();

private:
	// Array of floats to store all the Matrix4 data
	float* data;
};