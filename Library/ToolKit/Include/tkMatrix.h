#pragma once
#include "tkVector.h"

#define TK_POS(x, y, size) x + (y * size)

namespace tk {

#ifndef tkMATRIX
	class Matrix2 {
	public:
		Matrix2();
		Matrix2(
			float f1, float f2,
			float f3, float f4);
		~Matrix2();

		inline operator float*() { return data; }
		tk::Vector2& operator[] (int index);
		tk::Vector2 operator*(tk::Vector2 other);
		Matrix2 operator*(Matrix2 other);

		void setRotate(float angle);
		void identity();

	private:
		float* data;
	};

	class Matrix3 {
	public:
		Matrix3();
		Matrix3(
			float f1, float f2, float f3,
			float f4, float f5, float f6,
			float f7, float f8, float f9);
		~Matrix3();

		inline operator float*() { return data; }
		tk::Vector3 &operator[] (int index);
		tk::Vector3 operator*(tk::Vector3 other);
		Matrix3 operator*(Matrix3 other);
		void setRotateX(float angle);
		void setRotateY(float angle);
		void setRotateZ(float angle);
		void identity();

	private:
		float* data;
	};

	class Matrix4 {
	public:
		Matrix4();
		Matrix4(
			float f1, float f2, float f3, float f4,
			float f5, float f6, float f7, float f8,
			float f9, float f10, float f11, float f12,
			float f13, float f14, float f15, float f16);
		~Matrix4();

		inline operator float*() { return data; }
		tk::Vector4 &operator[] (int index);
		tk::Vector4 operator*(tk::Vector4 other);
		Matrix4 operator*(Matrix4 other);
		void setRotateX(float angle);
		void setRotateY(float angle);
		void setRotateZ(float angle);
		void identity();
	private:
		float* data;
	};
	
#else
	// ---- MATRIX ----
	// This class has all the Matrix2, Matrix3 and Matrix4 in it,
	// making it more effective, functional and over all easer to use.
	// But the unit test will not accept it.
	class Matrix {
	public:
		Matrix();
		Matrix(Vector row1, Vector row2);
		Matrix(Vector row1, Vector row2, Vector row3);
		Matrix(Vector row1, Vector row2, Vector row3, Vector row4);
		~Matrix();

		//inline void operator=(Vector vec) {}
		//inline void operator=(Matrix vec) {}

		inline float GetPos(const int x, const int y) { return m_matrix[x + (y * m_size)]; }
		inline float GetPos(const int index) { return m_matrix[index]; }
		inline void SetPos(const int x, const int y, float value) { m_matrix[x + (y * m_size)] = value; }
		inline int GetSize() { return m_size; }

		void Translate();
		Vector GetVector(const int index);

	private:
		int m_size;
		float* m_matrix;

		void CopyVec2(Vector& row1, Vector& row2);
		void CopyVec3(Vector& row1, Vector& row2, Vector& row3);
		void CopyVec4(Vector& row1, Vector& row2, Vector& row3, Vector& row4);
	};
#endif //tkMATRIX
}