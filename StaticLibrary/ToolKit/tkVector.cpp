#include "tkVector.h"

// ---- VECTOR 2 ----
Vector2::Vector2() {
	_x = new float(0);
	_y = new float(0);
}
Vector2::Vector2(float posX, float posY){
	_x = new float(0);
	_y = new float(0);
	*_x = posX; *_y = posY;
}
Vector2::Vector2(Vector2& other) {
	_x = new float(0);
	_y = new float(0);
	*_x = *other._x;  *_y = *other._y;
}
Vector2::~Vector2() {}



Vector2 Vector2::Add(Vector2 other) {
	return Vector2(x + other.x, y + other.y);
}
Vector2 Vector2::Sub(Vector2 other) {
	return Vector2(x - other.x, y - other.y);
}
Vector2 Vector2::Multiply(Vector2 other) {
	return Vector2(x * other.x, y * other.y);
}
Vector2 Vector2::Multiply(float value) {
	return Vector2(x * value, y * value);
}
void Vector2::SetInternal(float * xx, float * yy) {
	if (_x == nullptr) { _x = new float(0); }
	if (_y == nullptr) { _y = new float(0); }
	_x = xx; _y = yy;
}
Vector2::operator float*() {
	float* p = new float[2];
	p[0] = x; p[1] = y;
	return p;
}
Vector2 & Vector2::operator=(Vector2 other) {
	if (_x == nullptr) { _x = new float(); }
	if (_y == nullptr) { _y = new float(); }
	*_x = *(other._x);
	*_y = *(other._y);
	return *this;
}
void Vector2::operator+=(Vector2 other) {
	x = Add(other).x;
	y = Add(other).y;
}
void Vector2::operator-=(Vector2 other) {
	x = Sub(other).x;
	y = Sub(other).y;
}
void Vector2::operator*=(float value) {
	x = Multiply(value).x;
	y = Multiply(value).y;
}
bool Vector2::operator==(Vector2 other) {
	if (other.x == x && other.y == y) {
		return true;
	} return false;
}

float Vector2::magnitude() {
	return (float)sqrt(powf(x, 2.f) + powf(y, 2.f));
}

float Vector2::dot(Vector2 other) {
	return x*other.x + y*other.y;
}

void Vector2::normalise() {
	float mag = magnitude();
	x = x / mag; y = y / mag;
}

// ---- VECTOR 3 ----
Vector3::Vector3() {
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
}
Vector3::Vector3(float posX, float posY, float posZ){
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
	*_x = posX; *_y = posY; *_z = posZ;
}
Vector3::Vector3(Vector3& other) {
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
	*_x = *other._x;  *_y = *other._y; *_z = *other._z;
}
Vector3::~Vector3() {}

Vector3 Vector3::Add(Vector3 other) {
	return Vector3(x + other.x, y + other.y, z + other.z);
}
Vector3 Vector3::Sub(Vector3 other) {
	return Vector3(x - other.x, y - other.y, z - other.z);
}
Vector3 Vector3::Multiply(Vector3 other) {
	return Vector3(x * other.x, y * other.y, z * other.z);
}
Vector3 Vector3::Multiply(float value) {
	return Vector3(x * value, y * value, z * value);
}
void Vector3::SetInternal(float * xx, float * yy, float * zz) {
	if (_x == nullptr) { _x = new float(0); }
	if (_y == nullptr) { _y = new float(0); }
	if (_z == nullptr) { _z = new float(0); }
	_x = xx; _y = yy; _z = zz;
}
Vector3::operator float*() {
	float* p = new float[3];
	p[0] = x; p[1] = y; p[2] = z;
	return p;
}
Vector3& Vector3::operator=(Vector3 other) {
	if (_x == nullptr) { _x = new float(); }
	if (_y == nullptr) { _y = new float(); }
	if (_z == nullptr) { _z = new float(); }
	*_x = *(other._x);
	*_y = *(other._y);
	*_z = *(other._z);
	return *this;
}
void Vector3::operator+=(Vector3 other) {
	x = Add(other).x;
	y = Add(other).y;
	z = Add(other).z;
}
void Vector3::operator-=(Vector3 other) {
	x = Sub(other).x;
	y = Sub(other).y;
	z = Sub(other).z;
}
void Vector3::operator*=(Vector3 other) {
	x = Multiply(other).x;
	y = Multiply(other).y;
	z = Multiply(other).z;
}
void Vector3::operator*=(float value) {
	x = Multiply(value).x;
	y = Multiply(value).y;
	z = Multiply(value).z;
}
bool Vector3::operator==(Vector3 other) {
	if (other.x == x && other.y == y && other.z == z) {
		return true;
	} return false;
}

float Vector3::magnitude() {
	return (float)sqrt(powf(x, 2.f) + powf(y, 2.f) + powf(z, 2.f));
}

float Vector3::dot(Vector3 other) {
	return x*other.x + y*other.y + z*other.z;
}

void Vector3::normalise() {
	float mag = magnitude();
	x = x / mag; y = y / mag; z = z / mag;
}

Vector3 Vector3::cross(Vector3 other) {
	return Vector3(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

// ---- VECTOR 4 ----
Vector4::Vector4() {
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
	_w = new float(0);
}
Vector4::Vector4(float posX, float posY, float posZ, float posW) {
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
	_w = new float(0);
	*_x = posX; *_y = posY; *_z = posZ; *_w = posW;
}
Vector4::Vector4(Vector4& other) {
	_x = new float(0);
	_y = new float(0);
	_z = new float(0);
	_w = new float(0);
	*_x = *other._x;  *_y = *other._y; *_z = *other._z; *_w = *other._w;
}
Vector4::~Vector4() {}

Vector4 Vector4::Add(Vector4 other) {
	return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
}
Vector4 Vector4::Sub(Vector4 other) {
	return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}
Vector4 Vector4::Multiply(Vector4 other) {
	return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
}
Vector4 Vector4::Multiply(float value) {
	return Vector4(x * value, y * value, z * value, w * value);
}
void Vector4::SetInternal(float * xx, float * yy, float * zz, float* ww) {
	if (_x == nullptr) { _x = new float(0); }
	if (_y == nullptr) { _y = new float(0); }
	if (_z == nullptr) { _z = new float(0); }
	if (_w == nullptr) { _w = new float(0); }
	_x = xx; _y = yy; _z = zz; _w = ww;
}
Vector4::operator float*() {
	float* p = new float[4];
	p[0] = x; p[1] = y; p[2] = z; p[3] = w;
	return p;
}
Vector4 & Vector4::operator=(Vector4 other) {
	if (_x == nullptr) { _x = new float(); }
	if (_y == nullptr) { _y = new float(); }
	if (_z == nullptr) { _z = new float(); }
	if (_w == nullptr) { _w = new float(); }
	*_x = *(other._x);
	*_y = *(other._y);
	*_z = *(other._z);
	*_w = *(other._w);
	return *this;
}
void Vector4::operator+=(Vector4 other) {
	x = Add(other).x;
	y = Add(other).y;
	z = Add(other).z;
	w = Add(other).w;
}
void Vector4::operator-=(Vector4 other) {
	x = Sub(other).x;
	y = Sub(other).y;
	z = Sub(other).z;
	w = Sub(other).w;
}
void Vector4::operator*=(Vector4 other) {
	x = Multiply(other).x;
	y = Multiply(other).y;
	z = Multiply(other).z;
	w = Multiply(other).w;
}
void Vector4::operator*=(float value) {
	x = Multiply(value).x;
	y = Multiply(value).y;
	z = Multiply(value).z;
	w = Multiply(value).w;
}
bool Vector4::operator==(Vector4 other) {
	if (other.x == x && other.y == y && other.z == z && other.w == w) {
		return true;
	} return false;
}

float Vector4::magnitude() {
	return (float)sqrt(powf(x, 2.f) + powf(y, 2.f) + powf(z, 2.f) + powf(w, 2.f));
}

float Vector4::dot(Vector4 other) {
	return x*other.x + y*other.y + z*other.z + w*other.w;
}

void Vector4::normalise() {
	float mag = magnitude();
	x = x / mag; y = y / mag; z = z / mag; w = w / mag;
}

Vector4 Vector4::cross(Vector4 other) {
	return Vector4(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x, 0);
}