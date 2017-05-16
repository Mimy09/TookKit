#include "tkMatrix.h"

// ---- MATRIX 2 ----
Matrix2::Matrix2() {
	data = new float[4];
	for (int i = 0; i < 4; i++) {
		data[i] = 0;
	}
}
Matrix2::Matrix2(
	float f1, float f2,
	float f3, float f4) {
	data = new float[4];
	data[0] = f1; data[1] = f2;
	data[2] = f3; data[3] = f4;
}
Matrix2::~Matrix2() {
}

Vector2 &Matrix2::operator[](int index) {
	return Vector2(
		data[0 + (index * 2)],
		data[1 + (index * 2)]
	);
}

Vector2 Matrix2::operator*(Vector2 other) {
	return Vector2(
		other.x * data[0] + other.y * data[2],
		other.x * data[1] + other.y * data[3]
	);
}

Matrix2 Matrix2::operator*(Matrix2 other) {
	Matrix2 mat2;
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 2; x++) {
			for (int i = 0; i < 2; i++) {
				mat2.data[x + (y * 2)] += data[x + (i * 2)] * other.data[i + (y * 2)];
			}
		}
	}
	return mat2;
}

void Matrix2::setRotate(float angle) {
	data[0] = (float)cos(angle); data[1] = (float)sin(angle);
	data[2] = (float)-sin(angle); data[3] = (float)cos(angle);
}

void Matrix2::identity() {
	data[0] = 1; data[1] = 0;
	data[2] = 0; data[3] = 1;
}

// ---- MATRIX 3 ----
Matrix3::Matrix3() {
	data = new float[9];
	for (int i = 0; i < 9; i++) {
		data[i] = 0;
	}
}
Matrix3::Matrix3(
	float f1, float f2, float f3,
	float f4, float f5, float f6,
	float f7, float f8, float f9) {
	data = new float[9];
	data[0] = f1; data[1] = f2; data[2] = f3;
	data[3] = f4; data[4] = f5; data[5] = f6;
	data[6] = f7; data[7] = f8; data[8] = f9;
}
Matrix3::~Matrix3() {
		
}

Vector3& Matrix3::operator[](int index) {
	Vector3* temp = new Vector3();
	temp->SetInternal(
		&data[TK_POS(0, index, 3)],
		&data[TK_POS(1, index, 3)],
		&data[TK_POS(2, index, 3)]
	); return *temp;
}

Vector3 Matrix3::operator*(Vector3 other) {
	return Vector3(
		other.x * data[0] + other.y * data[3] + other.z * data[6],
		other.x * data[1] + other.y * data[4] + other.z * data[7],
		other.x * data[2] + other.y * data[5] + other.z * data[8]
	);
}

Matrix3 Matrix3::operator*(Matrix3 other) {
	Matrix3 mat3;
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			for (int i = 0; i < 3; i++) {
				mat3.data[x + (y * 3)] += data[x + (i * 3)] * other.data[i + (y * 3)];
			}
		}
	}
	return mat3;
}

void Matrix3::setRotateX(float angle) {
	identity();
	data[4] = (float)cos(angle); data[5] = (float)sin(angle);
	data[7] = (float)-sin(angle); data[8] = (float)cos(angle);
}

void Matrix3::setRotateY(float angle) {
	identity();
	data[0] = (float)cos(angle); data[2] = (float)-sin(angle);
	data[6] = (float)sin(angle); data[8] = (float)cos(angle);
}

void Matrix3::setRotateZ(float angle) {
	identity();
	data[0] = (float)cos(angle); data[1] = (float)sin(angle);
	data[3] = (float)-sin(angle); data[4] = (float)cos(angle);
}

void Matrix3::identity() {
	data[0] = 1; data[1] = 0; data[2] = 0;
	data[3] = 0; data[4] = 1; data[5] = 0;
	data[6] = 0; data[7] = 0; data[8] = 1;
}

// ---- MATRIX 4 ----
Matrix4::Matrix4() {
	data = new float[16];
	for (int i = 0; i < 16; i++) {
		data[i] = 0;
	}
}
Matrix4::Matrix4(
	float f1, float f2, float f3, float f4,
	float f5, float f6, float f7, float f8,
	float f9, float f10, float f11, float f12,
	float f13, float f14, float f15, float f16) {
	data = new float[16];
	data[0] = f1; data[1] = f2; data[2] = f3; data[3] = f4;
	data[4] = f5; data[5] = f6; data[6] = f7; data[7] = f8;
	data[8] = f9; data[9] = f10; data[10] = f11; data[11] = f12;
	data[12] = f13; data[13] = f14; data[14] = f15; data[15] = f16;
}
Matrix4::~Matrix4() {
}

Vector4& Matrix4::operator[](int index) {
	Vector4* temp = new Vector4();
	temp->SetInternal(
		&data[TK_POS(0, index, 4)],
		&data[TK_POS(1, index, 4)],
		&data[TK_POS(2, index, 4)],
		&data[TK_POS(3, index, 4)]
	); return *temp;
}

Vector4 Matrix4::operator*(Vector4 other) {
	return Vector4(
		other.x * data[0] + other.y * data[4] + other.z * data[8] + other.w * data[12],
		other.x * data[1] + other.y * data[5] + other.z * data[9] + other.w * data[13],
		other.x * data[2] + other.y * data[6] + other.z * data[10] + other.w * data[14],
		other.x * data[3] + other.y * data[7] + other.z * data[11] + other.w * data[15]
	);
}

Matrix4 Matrix4::operator*(Matrix4 other) {
	Matrix4 mat4;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			for (int i = 0; i < 4; i++) {
				mat4.data[x + (y * 4)] += data[x + (i * 4)] * other.data[i + (y * 4)];
			}
		}
	}
	return mat4;
}

void Matrix4::setRotateX(float angle) {
	identity();
	data[5] = (float)cos(angle); data[6] = (float)sin(angle);
	data[9] = (float)-sin(angle); data[10] = (float)cos(angle);
}

void Matrix4::setRotateY(float angle) {
	identity();
	data[0] = (float)cos(angle); data[2] = (float)-sin(angle);
	data[8] = (float)sin(angle); data[10] = (float)cos(angle);
}

void Matrix4::setRotateZ(float angle) {
	identity();
	data[0] = (float)cos(angle); data[1] = (float)sin(angle);
	data[4] = (float)-sin(angle); data[5] = (float)cos(angle);
}

void Matrix4::identity() {
	data[0] = 1; data[1] = 0; data[2] = 0; data[3] = 0;
	data[4] = 0; data[5] = 1; data[6] = 0; data[7] = 0;
	data[8] = 0; data[9] = 0; data[10] = 1; data[11] = 0;
	data[12] = 0; data[13] = 0; data[14] = 0; data[15] = 1;
}