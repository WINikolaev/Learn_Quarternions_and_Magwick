// Quterion_test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <io.h>
#include <iostream>

#define M_PI       3.14159265358979323846


using namespace std;

typedef struct _str_Quternion{
	float w;
	float x;
	float y;
	float z;
};

typedef struct _str_Vector{
	float x;
	float y;
	float z;
};

float angle = 0x00;


_str_Quternion Create_Quate(_str_Vector q, float rotate_angle)
{
	float angle = (M_PI / 180);
	rotate_angle = rotate_angle* angle;
	_str_Quternion res;
	_str_Quternion normal;
	_str_Quternion create_quat;
	float length = (q.x*q.x + q.y*q.y + q.z*q.z);
	length = sqrt(length);
	normal.x = q.x / length;
	normal.y = q.y / length;
	normal.z = q.z / length;

	create_quat.w = cos(rotate_angle / 2);
	create_quat.x = normal.x * sin(rotate_angle / 2);
	create_quat.y = normal.y * sin(rotate_angle / 2);
	create_quat.z = normal.z * sin(rotate_angle / 2);
	return create_quat;

}

/// Преобразование вектора в кватерион
///	q - кватернион. v - вектор
_str_Quternion quat_mul_vector(_str_Quternion q, _str_Vector v)
{
	_str_Quternion res;
	res.w =-q.x * v.x - q.y * v.y - q.z * v.z;
	res.x = q.w * v.x + q.y * v.z - q.z * v.y;
	res.y = q.w * v.y - q.x * v.z + q.z * v.x;
	res.z = q.w * v.z + q.x * v.y - q.y * v.x;
	return res;
}

/// Умножение кватерниона на кватернион
_str_Quternion quat_mul_quat(_str_Quternion q, _str_Quternion v)
{
	_str_Quternion res;
	res.w = q.w * v.w - q.x * v.x - q.y * v.y - q.z * v.z;
	res.x = q.w * v.x + q.x * v.w + q.y * v.z - q.z * v.y;
	res.y = q.w * v.y - q.x * v.z + q.y * v.w + q.z * v.x;
	res.z = q.w * v.z + q.x * v.y - q.y * v.x + q.z * v.w;
	return res;
}


/// нормализация
_str_Quternion normaliz(_str_Quternion q)
{
	float vect_length = (q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	vect_length = sqrt(vect_length);
	float vect_inversion = 1 / vect_length;
	q.w *= vect_inversion;
	q.x *= vect_inversion;
	q.y *= vect_inversion;
	q.z *= vect_inversion;
	return q;
}

/// Инвертирование кватерниона
_str_Quternion quat_inversion(_str_Quternion q)
{
	_str_Quternion res;
	res.w = q.w;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	res = normaliz(res);
	return res;
}


int main()
{
	cout << "Hello" << endl;

	_str_Quternion q1 = quat_mul_quat({0.f,0.f,0.f,0.707f}, {0.f,0.f,0.707f,0.f});
	_str_Quternion q2 = quat_mul_quat(q1,{ 0.f,0.707f,0.f,0.f });
	_str_Quternion q3 = quat_mul_quat(q2,{ 0.f,1.f,0.f,0.f });
	
	//_str_Quternion q1 = Create_Quate({ 1, 0, 1 }, 180);
	//_str_Quternion vq = quat_mul_vector(q1, {0,0,1});
	//_str_Quternion qq = quat_mul_quat(vq, quat_inversion(q1));
	float W = q3.w;
	float X = q3.x;
	float Y = q3.y;
	float Z = q3.z;
	cout << "qq: " << "w=" << W << " x=" << X
		<< " y=" << Y << " z=" << Z << endl;

	system("pause");
    return 0;
}

