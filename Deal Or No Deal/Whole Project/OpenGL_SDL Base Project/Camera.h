#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include "../gl/glut.h"
#include "Commons.h"
#include "QuaternionMath.h"

class Camera
{
//--------------------------------------------------------------------------------------------------
public:
	Camera(CameraType aCameraType);
	static Camera* GetInstance();

	void SetAsPerspective(Vector3D aCentre, Vector3D aLookAt, Vector3D aUp, float aNear, float aFar, float aFieldOfView, float aAspect);
	void SetAsOrtho(Vector3D aCentre, Vector3D aLookAt, Vector3D aUp, float aLeft, float aRight, float aBottom,
	float aTop, float aNear, float aFar);

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void SetAspect(float aAspect);
	void SetLeft(float aLeft);
	void SetRight(float aRight);
	void SetTop(float aTop);
	void SetBottom(float aBottom);
	void SetNear(float aNear);
	void SetFar(float aFar);
	void SetFieldOfView(float aAngle);
	void SetType(CameraType aCameraType);

	void Pitch(float aAngle);
	void Roll(float aAngle);
	void Yaw(float aAngle);

	void Zoom(float aDistance);
	void Strafe(float aDistance);
	void MoveForward(float aDistance);
//--------------------------------------------------------------------------------------------------
private:
	CameraType  m_eType;
	bool		m_bSettingsChanged;

	//Camera position.
	Vector3D    m_vPosition;

	//Camera vectors.
	Vector3D	m_vStartFacing;
	Vector3D	m_vFacing;
	Vector3D	m_vRight;
	Vector3D	m_vUp;

	//Camera viewport parameters.
	float		m_fNear;
	float		m_fFar;
	float		m_fLeft;
	float		m_fRight;
	float		m_fTop;
	float		m_fBottom;
	float		m_fHeight;
	float		m_fAspect;
	float		m_fFieldOfView;

	//Roll, Pitch & Yaw angles.
	float		m_fRollAngle;
	float		m_fPitchAngle;
	float		m_fYawAngle;

	//Solve Gimbal lock using quaternions.
	Quaternion* m_Quaternion;

	

};

#endif //CAMERA_H
