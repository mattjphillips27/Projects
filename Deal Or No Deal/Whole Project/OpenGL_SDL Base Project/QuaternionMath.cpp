#include "QuaternionMath.h"
#include <math.h>

//Initialise the instance to null.
QuaternionMath* QuaternionMath::mInstance = 0;

//--------------------------------------------------------------------------------------------------

QuaternionMath::QuaternionMath()
{
}

//--------------------------------------------------------------------------------------------------

QuaternionMath::~QuaternionMath()
{
	mInstance = 0;
}

//--------------------------------------------------------------------------------------------------

QuaternionMath* QuaternionMath::Instance()
{
	if(!mInstance)
	{
		mInstance = new QuaternionMath;
	}

	return mInstance;
}

//--------------------------------------------------------------------------------------------------

void QuaternionMath::QuaternionToMatrix(Quaternion* q, float m[4][4])
{
	float wx, wy, wz, xx, xy, xz, yy, yz, zz, x2, y2, z2;

	//Calculate coefficients used for building the matrix.
	x2 = q->vec.x + q->vec.x;
	y2 = q->vec.y + q->vec.y;
	z2 = q->vec.z + q->vec.z;

	xx = q->vec.x * x2;
	xy = q->vec.x * y2;
	xz = q->vec.x * z2;

	yy = q->vec.y * y2;
	yz = q->vec.y * z2;
	zz = q->vec.z * z2;

	wx = q->w * x2;
	wy = q->w * y2;
	wz = q->w * z2;

	//Fill in the matrix positions withe them.
	m[0][0] = 1.0f - (yy+zz);
	m[1][0] = xy-wz;
	m[2][0] = xz+wy;
	m[3][0] = 0.0f;
	m[0][1] = xy + wz;
	m[1][1] = 1.0f - (xx+zz);
	m[2][1] = yz - wx;
	m[3][1] = 0.0f;
	m[0][2] = xz-wy;
	m[1][2] = yz+wx;
	m[2][2] = 1.0f - (xx+yy);
	m[3][2] = 0.0f;
	m[0][3] = 0.0f;
	m[1][3] = 0.0f;
	m[2][3] = 0.0f;
	m[3][3] = 1.0f;
}

//--------------------------------------------------------------------------------------------------

void QuaternionMath::MatrixToQuaternion(float m[4][4], Quaternion* q)
{
	float tr, s, qq[4];
	int i, j, k;

	int nxt[3] = {1,2,0};

	//Compute the trace of the matrix.
	tr = m[0][0]+m[1][1]+m[2][2];

	//Check if the trace is positive or negative.
	if(tr > 0.0f)
	{
		s = sqrt(tr+1.0f);
		q->w = s/2.0f;
		s = 0.5f / s;
		q->vec.x = (m[1][2]-m[2][1])*s;
		q->vec.y = (m[2][0]-m[0][2])*s;
		q->vec.z = (m[0][1]-m[1][0])*s;
	}
	else
	{
		//Trace is negative.
		i = 0;
		if(m[1][1] > m[0][0])
			i=1;
		if(m[2][2] > m[i][i])
			i = 2;
		j = nxt[i];
		k = nxt[j];

		s = sqrt((m[i][i]-(m[j][j]+m[k][k]))+1.0f);
		qq[i] = s*0.5f;
		if(s != 0.0f)
			s=0.5f/s;
		qq[3] = (m[j][k]-m[k][j])*s;
		qq[j] = (m[i][j]+m[j][i])*s;
		qq[k] = (m[i][k]+m[k][i])*s;

		q->vec.x = qq[0];
		q->vec.y = qq[1];
		q->vec.z = qq[2];
		q->w	 = qq[3];
	}
}

//--------------------------------------------------------------------------------------------------

void QuaternionMath::EulerToQuaternion(float roll, float pitch, float yaw, Quaternion* q)
{
	float cr, cp, cy, sr, sp, sy;

	//Compute all trigonometric values used to compute the quaternion.
	cr = cos(roll/2);
	cp = cos(pitch/2);
	cy = cos(yaw/2);

	sr = sin(roll/2);
	sp = sin(pitch/2);
	sy = sin(yaw/2);

	//Combine values to generate the vector and scalar for the quaternion.
	q->w	 = cp * cy * cr + sp * sy * sr;
	q->vec.x = sp * cy * cr - cp * sy * sr;
	q->vec.y = cp * sy * cr + sp * cy * sr;
	q->vec.z = cp * cy * sr - sp * sy * cr;
}

//--------------------------------------------------------------------------------------------------

void QuaternionMath::Multiply(Quaternion* q1, Quaternion* q2, Quaternion* resultingQuaternion)
{
	float a, b, c, d, e, f, g, h;

	a = (q1->w     + q1->vec.x) * (q2->w     + q2->vec.x);
	b = (q1->vec.z - q1->vec.y) * (q2->vec.y - q2->vec.z);
	c = (q1->w     - q1->vec.x) * (q2->vec.y + q2->vec.z);
	d = (q1->vec.y + q1->vec.z) * (q2->w     - q2->vec.x);
	e = (q1->vec.x + q1->vec.z) * (q2->vec.x + q2->vec.y);
	f = (q1->vec.x - q1->vec.z) * (q2->vec.x - q2->vec.y);
	g = (q1->w     + q1->vec.y) * (q2->w     - q2->vec.z);
	h = (q1->w     - q1->vec.y) * (q2->w     + q2->vec.z);

	resultingQuaternion->w	   = b + (-e - f + g + h) / 2;
	resultingQuaternion->vec.x = a - (e + f + g + h) / 2;
	resultingQuaternion->vec.y = c + (e - f + g - h) / 2;
	resultingQuaternion->vec.z = d + (e - f - g + h) / 2;
}

//--------------------------------------------------------------------------------------------------

void QuaternionMath::RotateVector(Quaternion* q, Vector3D* v, Vector3D* resultingVector)
{
/*	//Extract the vector part of the quaternion.
	Vector3D u(q->vec.x, q->vec.y, q->vec.z);

	//Extract the scalar part of the quaternion.
	float s = q->w;

	//Do the calculations.
	float dot = (u.x*v->x)+(u.y*v->y)*(u.z*v->z);
	Vector3D cross( (u.y*v->z)-(u.z*v->y),	
					(u.z*v->x)-(u.x*v->z),
					(u.x*v->y)-(u.y*v->x) );

	resultingVector->x = 2.0f*dot*u.x+(s*s-dot)*v->x+2.0f*s*cross.x;
	resultingVector->y = 2.0f*dot*u.y+(s*s-dot)*v->y+2.0f*s*cross.y;
	resultingVector->z = 2.0f*dot*u.z+(s*s-dot)*v->z+2.0f*s*cross.z;
	*/

	float x = q->vec.x+q->vec.x;
	float y  = q->vec.y+q->vec.y;
	float z   = q->vec.z+q->vec.z;
	float num11 = q->w * x;
	float num10 = q->w * y;
	float num9  = q->w * z;
	float num8  = q->vec.x * x; 
	float num7  = q->vec.x * y;
	float num6  = q->vec.x * z;
	float num5  = q->vec.y * y;
	float num4  = q->vec.y * z;
	float num3  = q->vec.z * z;

	resultingVector->x = ((v->x*((1.0f-num5)-num3))+(v->y*(num7-num9)))+(v->z*(num6+num10));
	resultingVector->y = ((v->x*(num7+num9))+(v->y*((1.0f-num8)-num3)))+(v->z*(num4-num11));
	resultingVector->z = ((v->x*(num6-num10))+(v->y*(num4+num11)))+(v->z*((1.0f-num8)-num5));
}


//--------------------------------------------------------------------------------------------------