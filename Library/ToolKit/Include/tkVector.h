#pragma once
#include <math.h>
#include "tkException.h"
#include "Properties.h"

namespace tk {

#ifndef tkVECTOR
	// ---- Vector 2 ----
	class Vector2 {
	public:
		Vector2();
		Vector2(float posX, float posY);
		Vector2(Vector2& other);
		~Vector2();

		PROPERTY(float, x);
		GET(x) { return *_x; }
		SET(x) { *_x = value; }

		PROPERTY(float, y);
		GET(y) { return *_y; }
		SET(y) { *_y = value; }

		void SetInternal(float* xx, float* yy);

		operator float*();
		float& operator[](int index);
		Vector2& operator=(Vector2 other);
		inline Vector2 operator+(Vector2 other) { return Add(other); }
		inline Vector2 operator-(Vector2 other) { return Sub(other); }
		inline Vector2 operator*(Vector2 other) { return Multiply(other); }
		inline Vector2 operator*(float value) { return Multiply(value); }
		friend Vector2 operator*(float value, Vector2 other) { return other * value; }
		void operator+=(Vector2 other);
		void operator-=(Vector2 other);
		void operator*=(float value);
		bool operator==(Vector2 other);

		float magnitude();
		float dot(Vector2 other);
		void normalise();

	private:
		float *_x, *_y;

		Vector2 Add(Vector2 other);
		Vector2 Sub(Vector2 other);
		Vector2 Multiply(Vector2 other);
		Vector2 Multiply(float value);
	};

	// ---- Vector 3 ----
	class Vector3 {
	public:

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(Vector3& other);
		~Vector3();

		PROPERTY(float, x);
		GET(x) { return *_x; }
		SET(x) { *_x = value; }

		PROPERTY(float, y);
		GET(y) { return *_y; }
		SET(y) { *_y = value; }

		PROPERTY(float, z);
		GET(z) { return *_z; }
		SET(z) { *_z = value; }

		void SetInternal(float* xx, float* yy, float* zz);

		float& operator[](int index);
		operator float*();
		Vector3& operator=(Vector3 other);
		inline Vector3 operator+(Vector3 other) { return Add(other); }
		inline Vector3 operator-(Vector3 other) { return Sub(other); }
		inline Vector3 operator*(Vector3 other) { return Multiply(other); }
		inline Vector3 operator*(float value) { return Multiply(value); }
		friend Vector3 operator*(float value, Vector3 other) { return other * value; }
		inline void operator+=(Vector3 other);
		inline void operator-=(Vector3 other);
		inline void operator*=(Vector3 other);
		inline void operator*=(float value);
		bool operator==(Vector3 other);

		float magnitude();
		float dot(Vector3 other);
		void normalise();
		Vector3 cross(Vector3 other);

	private:
		float *_x, *_y, *_z;
		Vector3 Add(Vector3 other);
		Vector3 Sub(Vector3 other);
		Vector3 Multiply(Vector3 other);
		Vector3 Multiply(float value);
	};

	// ---- Vector 4 ----
	class Vector4 {
	public:
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(Vector4& other);
		~Vector4();

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

		void SetInternal(float* xx, float* yy, float* zz, float* ww);

		float & operator[](int index);
		operator float*();
		Vector4& operator=(Vector4 other);
		inline Vector4 operator+(Vector4 other) { return Add(other); }
		inline Vector4 operator-(Vector4 other) { return Sub(other); }
		inline Vector4 operator*(Vector4 other) { return Multiply(other); }
		inline Vector4 operator*(float value) { return Multiply(value); }
		friend Vector4 operator*(float value, Vector4 other) { return other * value; }
		inline void operator+=(Vector4 other);
		inline void operator-=(Vector4 other);
		inline void operator*=(Vector4 other);
		inline void operator*=(float value);

		bool operator==(Vector4 other);

		float magnitude();
		float dot(Vector4 other);
		void normalise();
		Vector4 cross(Vector4 other);

	private:
		float *_x, *_y, *_z, *_w;
		Vector4 Add(Vector4 other);
		Vector4 Sub(Vector4 other);
		Vector4 Multiply(Vector4 other);
		Vector4 Multiply(float value);
	};
#else
	class Vector {
	public:
		float x, y, z, w;

		Vector();
		Vector(int size);
		Vector(float x, float y);
		Vector(float x, float y, float z);
		Vector(float x, float y, float z, float w);
		~Vector();

		inline int GetSize() { return m_size; }
		float GetPos(int index);

		Vector Normalize();
		Vector Cross(Vector other);
		float Dot(Vector other);
		float Magnitude();

		inline void operator=(Vector other) { Copy(other); }
		inline Vector operator*(float value);
		inline friend Vector operator*(const Vector& other, const float& value) { return Vector(); }
		Vector operator*(Vector other);
		Vector operator/(Vector other);
		Vector operator+(Vector other);
		Vector operator-(Vector other);

		void operator*=(float value);
		void operator*=(Vector other);
		void operator/=(Vector other);
		void operator+=(Vector other);
		void operator-=(Vector other);


	private:
		int m_size;

		void Copy(Vector other);
		void Copy(float x, float y);
		void Copy(float x, float y, float z);
		void Copy(float x, float y, float z, float w);

	};
#endif
}