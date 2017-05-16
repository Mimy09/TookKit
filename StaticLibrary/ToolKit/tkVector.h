// ################################################################## //
// ##							TOOL KIT						   ## //
// ##															   ## //
// ##			By Mitchell Jenkins - 2017 May 05 - AIE			   ## //
// ################################################################## //
#pragma once
#include <math.h>
#include "tkException.h"
#include "Properties.h"

// ---- Vector 2 ----
class Vector2 {
public:
	// Default Constructor
	Vector2();
	// Copy Constructors
	Vector2(float posX, float posY);
	Vector2(Vector2& other);
	// Deconstructor
	~Vector2();

	// Setting the properties of the x and y pointers values to
	// be able to used in a non-pointer way
	PROPERTY(float, x);
	GET(x) { return *_x; }
	SET(x) { *_x = value; }
	PROPERTY(float, y);
	GET(y) { return *_y; }
	SET(y) { *_y = value; }

	// Sets the internal pointers
	void SetInternal(float* xx, float* yy);

	operator float*();
	// Overloads the = operater with Vector2
	Vector2& operator=(Vector2 other);
	// Overloads the + operater with Vector2
	inline Vector2 operator+(Vector2 other) { return Add(other); }
	// Overloads the - operater with Vector2
	inline Vector2 operator-(Vector2 other) { return Sub(other); }
	// Overloads the * operater with Vector2
	inline Vector2 operator*(Vector2 other) { return Multiply(other); }
	// Overloads the * operater with float
	inline Vector2 operator*(float value) { return Multiply(value); }
	// Overloads the * operater with Vector2 on right and float on left
	friend Vector2 operator*(float value, Vector2 other) { return other * value; }

	// Overloads the += operater with Vector2
	void operator+=(Vector2 other);
	// Overloads the -= operater with Vector2
	void operator-=(Vector2 other);
	// Overloads the *= operater with float
	void operator*=(float value);
	// Overloads the == operater with Vector2
	bool operator==(Vector2 other);

	// Gets the magnitude of the vector and returns a float value
	float magnitude();
	// Gets the dot product of the vector and returns a float value
	float dot(Vector2 other);
	// Normalises the vector so no value is greater the 1
	void normalise();

private:
	// Array of floats to store all the Vector2 data
	float *_x, *_y;

	// Adds two Vector2's togther
	Vector2 Add(Vector2 other);
	// Subtracts two Vector2's togther
	Vector2 Sub(Vector2 other);
	// Multiplys two Vector2's togther
	Vector2 Multiply(Vector2 other);
	// Multiplys a Vector2 and a float value togther
	Vector2 Multiply(float value);
};

// ---- Vector 3 ----
class Vector3 {
public:
	// Default Constructor
	Vector3();
	// Copy Constructors
	Vector3(float x, float y, float z);
	Vector3(Vector3& other);
	// Deconstructor
	~Vector3();

	// Setting the properties of the x, y and z pointers values to
	// be able to used in a non-pointer way
	PROPERTY(float, x);
	GET(x) { return *_x; }
	SET(x) { *_x = value; }
	PROPERTY(float, y);
	GET(y) { return *_y; }
	SET(y) { *_y = value; }
	PROPERTY(float, z);
	GET(z) { return *_z; }
	SET(z) { *_z = value; }

	// Sets the internal pointers
	void SetInternal(float* xx, float* yy, float* zz);

	operator float*();
	// Overloads the = operater with Vector3
	Vector3& operator=(Vector3 other);
	// Overloads the + operater with Vector3
	inline Vector3 operator+(Vector3 other) { return Add(other); }
	// Overloads the - operater with Vector3
	inline Vector3 operator-(Vector3 other) { return Sub(other); }
	// Overloads the * operater with Vector3
	inline Vector3 operator*(Vector3 other) { return Multiply(other); }
	// Overloads the * operater with float
	inline Vector3 operator*(float value) { return Multiply(value); }
	// Overloads the * operater with Vector3 on right and float on left
	friend Vector3 operator*(float value, Vector3 other) { return other * value; }

	// Overloads the += operater with Vector3
	inline void operator+=(Vector3 other);
	// Overloads the -= operater with Vector3
	inline void operator-=(Vector3 other);
	// Overloads the *= operater with Vector3
	inline void operator*=(Vector3 other);
	// Overloads the *= operater with float
	inline void operator*=(float value);
	// Overloads the == operater with Vector3
	bool operator==(Vector3 other);

	// Gets the magnitude of the Vector3 and returns a float value
	float magnitude();
	// Gets the dot product of the Vector3 and returns a float value
	float dot(Vector3 other);
	// Normalises the vector so no value is greater the 1
	void normalise();
	// Gets the cross product of two Vector3's and returns a new Vector3
	Vector3 cross(Vector3 other);

private:
	// Array of floats to store all the Vector3 data
	float *_x, *_y, *_z;

	// Adds two Vector3's togther
	Vector3 Add(Vector3 other);
	// Subtracts two Vector3's togther
	Vector3 Sub(Vector3 other);
	// Multiplys two Vector3's togther
	Vector3 Multiply(Vector3 other);
	// Multiplys a Vector3 and a float value togther
	Vector3 Multiply(float value);
};

// ---- Vector 4 ----
class Vector4 {
public:
	// Default Constructor
	Vector4();
	// Copy Constructors
	Vector4(float x, float y, float z, float w);
	Vector4(Vector4& other);
	// Deconstructor
	~Vector4();

	// Setting the properties of the x, y, z and w pointers values to
	// be able to used in a non-pointer way
	PROPERTY(float, x);
	GET(x) { return *_x; }
	SET(x) { *_x = value; }
	PROPERTY(float, y);
	GET(y) { return *_y; }
	SET(y) { *_y = value; }
	PROPERTY(float, z);
	GET(z) { return *_z; }
	SET(z) { *_z = value; }
	PROPERTY(float, w);
	GET(w) { return *_w; }
	SET(w) { *_w = value; }

	// Sets the internal pointers
	void SetInternal(float* xx, float* yy, float* zz, float* ww);

	operator float*();
	// Overloads the = operater with Vector4
	Vector4& operator=(Vector4 other);
	// Overloads the + operater with Vector4
	inline Vector4 operator+(Vector4 other) { return Add(other); }
	// Overloads the - operater with Vector4
	inline Vector4 operator-(Vector4 other) { return Sub(other); }
	// Overloads the * operater with Vector4
	inline Vector4 operator*(Vector4 other) { return Multiply(other); }
	// Overloads the * operater with float
	inline Vector4 operator*(float value) { return Multiply(value); }
	// Overloads the * operater with Vector4 on right and float on left
	friend Vector4 operator*(float value, Vector4 other) { return other * value; }

	// Overloads the += operater with Vector4
	inline void operator+=(Vector4 other);
	// Overloads the -= operater with Vector4
	inline void operator-=(Vector4 other);
	// Overloads the *= operater with Vector4
	inline void operator*=(Vector4 other);
	// Overloads the *= operater with float
	inline void operator*=(float value);
	// Overloads the == operater with Vector4
	bool operator==(Vector4 other);

	// Gets the magnitude of the Vector4 and returns a float value
	float magnitude();
	// Gets the dot product of the Vector4 and returns a float value
	float dot(Vector4 other);
	// Normalises the vector so no value is greater the 1
	void normalise();
	// Gets the cross product of two Vector4's and returns a new Vector4
	Vector4 cross(Vector4 other);
private:
	// Array of floats to store all the Vector4 data
	float *_x, *_y, *_z, *_w;

	// Adds two Vector4's togther
	Vector4 Add(Vector4 other);
	// Subtracts two Vector4's togther
	Vector4 Sub(Vector4 other);
	// Multiplys two Vector4's togther
	Vector4 Multiply(Vector4 other);
	// Multiplys a Vector4 and a float value togther
	Vector4 Multiply(float value);
};