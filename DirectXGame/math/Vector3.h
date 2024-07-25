#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;
};
//const Vector3 operator+(const Vector3& num1,const Vector3& num2){
//	Vector3 result{};
//	result.x = num1.x + num2.x;
//	result.y = num1.y + num2.y;
//	result.z = num1.z + num2.z;
//	return result;
//}
//Vector3 operator+(const Vector3& v) {
//
//}
//
//const Vector3 operator+(const Vector3& vector,  float& num) {
//	Vector3 result{};
//	result.x = vector.x + num;
//	result.y = vector.y + num;
//	result.z = vector.z + num;
//	return result;
//}
//
//const Vector3& operator+=(Vector3& num1, const Vector3& num2){
//	 //TODO: return ステートメントをここに挿入します
//	num1.x += num2.x;
//	num1.y += num2.y;
//	num1.z += num2.z;
//	return num1;
//}
//
//const Vector3 operator-(const Vector3& num1, const Vector3& num2){
//	Vector3 result{};
//	result.x = num1.x +- num2.x;
//	result.y = num1.y +- num2.y;
//	result.z = num1.z +- num2.z;
//	return result;
//}
//
//const Vector3& operator-=(Vector3& num1, const Vector3& num2){
//	// TODO: return ステートメントをここに挿入します
//	num1.x -= num2.x;
//	num1.y -= num2.y;
//	num1.z -= num2.z;
//	return num1;
//}
// 
//const Vector3& operator +(Vector3& num1, const float& num2){
//	// TODO: return ステートメントをここに挿入します
//	num1.x -= num2;
//	num1.y -= num2;
//	num1.z -= num2;
//	return num1;
//}