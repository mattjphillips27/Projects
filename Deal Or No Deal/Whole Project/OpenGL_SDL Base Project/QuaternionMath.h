#ifndef QUARTERNION_H
#define QUARTERNION_H

#include "Commons.h"

struct Quaternion
{
	float w;
	Vector3D vec;

	Quaternion()
	{
		vec.x = 0.0f;
		vec.y = 0.0f;
		vec.z = 0.0f;
	}

	Quaternion(float startW, Vector3D startVec)
	{
		vec.x = startVec.x;
		vec.y = startVec.y;
		vec.z = startVec.z;
	}
};

class QuaternionMath
{
public:
	~QuaternionMath();

	static QuaternionMath* Instance();

	void QuaternionToMatrix(Quaternion* q, float m[4][4]);
	void MatrixToQuaternion(float m[4][4], Quaternion* q);
	void EulerToQuaternion(float roll, float pitch, float yaw, Quaternion* q);

	void Multiply(Quaternion* q1, Quaternion* q2, Quaternion* resultingQuaternion);
	void RotateVector(Quaternion* q, Vector3D* v, Vector3D* resultingVector);

private:
	QuaternionMath();

private:
	static QuaternionMath* mInstance;

};
#endif