#include "Camera.h"
#include "Constants.h"
#include "QuaternionMath.h"
#include <math.h>
#include <iostream>
using namespace std;

//Camera
const float kLookAtOffset = 10.0f;
const float kAngleToTurn = 0.5f;
const float kMoveDistance = 10.0f;

static Camera* instance = 0;



//-----------------------------------------------------------------------------

Camera::Camera(CameraType aCameraType)
{
	if (instance == 0)
	{
		m_eType = aCameraType;
		m_bSettingsChanged = false;

		m_vPosition = Vector3D(0.0f, 0.0f, 0.0f);
		m_vFacing = Vector3D(0.0f, 0.0f, -1.0f);
		m_vUp = Vector3D(0.0f, 1.0f, 0.0f);
		m_vRight = Vector3D(1.0f, 0.0f, 10.0f);

		m_fRollAngle = 0.0f;
		m_fPitchAngle = 0.0f;
		m_fYawAngle = 0.0f;

		m_Quaternion = new Quaternion();

		instance = this;
	}
}

//-----------------------------------------------------------------------------

Camera* Camera::GetInstance()
{
	if (instance == 0)
	{
		instance = new Camera(CAMERA_ORTHO);
	}

	return instance;
}

//-----------------------------------------------------------------------------

void Camera::SetAspect(float aAspect)
{
	m_bSettingsChanged = true;
	m_fAspect = aAspect;
}

//-----------------------------------------------------------------------------

void Camera::SetLeft(float aLeft)
{
	m_bSettingsChanged = true;
	m_fLeft = aLeft;
}

//-----------------------------------------------------------------------------

void Camera::SetRight(float aRight)
{
	m_bSettingsChanged = true;
	m_fRight = aRight;
}

//-----------------------------------------------------------------------------

void Camera::SetTop(float aTop)
{
	m_bSettingsChanged = true;
	m_fTop = aTop;
}

//-----------------------------------------------------------------------------

void Camera::SetBottom(float aBottom)
{
	m_bSettingsChanged = true;
	m_fBottom = aBottom;
}

//-----------------------------------------------------------------------------

void Camera::SetNear(float aNear)
{
	m_bSettingsChanged = true;
	m_fNear = aNear;
}

//-----------------------------------------------------------------------------

void Camera::SetFar(float aFar)
{
	m_bSettingsChanged = true;
	m_fFar = aFar;
}

//-----------------------------------------------------------------------------

void Camera::SetFieldOfView(float aAngle)
{
	if (m_eType == CAMERA_PERSPECTIVE)
	{
		m_bSettingsChanged = true;
		m_fFieldOfView = aAngle;
	}
}

//-----------------------------------------------------------------------------

void Camera::SetType(CameraType aCameraType)
{
	m_eType = aCameraType;
}

//-----------------------------------------------------------------------------

void Camera::Render()
{
	if (m_bSettingsChanged)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		if (m_eType == CAMERA_ORTHO)
		{
			glOrtho(m_fLeft, m_fRight, m_fBottom, m_fTop, m_fNear, m_fFar);
		}
		else
		{
			gluPerspective(m_fFieldOfView, m_fAspect, m_fNear, m_fFar);
		}

		m_bSettingsChanged = false;
		glMatrixMode(GL_MODELVIEW);
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(m_vPosition.x, m_vPosition.y, m_vPosition.z);
	glRotatef(m_fYawAngle, 0, 1, 0);
	glRotatef(m_fPitchAngle, 1, 0, 0);
	glRotatef(m_fRollAngle, 0, 0, 1);

	//glRotatef(10.0f, m_vFacing.x, m_vFacing.y, m_vFacing.z);
}

//-----------------------------------------------------------------------------

void Camera::Update(float deltaTime, SDL_Event e)
{

	

	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
			/*case SDLK_a:
				Yaw(-kAngleToTurn);
				break;

			case SDLK_d:
				Yaw(kAngleToTurn);
				break;

			case SDLK_s:
				Pitch(-kAngleToTurn);
				break;

			case SDLK_w:
				Pitch(kAngleToTurn);
				break;

			case SDLK_q:
				Roll(-kAngleToTurn);
				break;

			case SDLK_e:
				Roll(kAngleToTurn);
				break;

			case SDLK_k:
				MoveForward(kMoveDistance);
				break;

			case SDLK_i:
				MoveForward(-kMoveDistance);
				break;

			case SDLK_j:
				Strafe(kMoveDistance);
				break;

			case SDLK_l:
				Strafe(-kMoveDistance);
				break;		*/

			
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			Zoom(-kMoveDistance);
		}
		if (e.button.button == SDL_BUTTON_RIGHT)
		{
			Zoom(kMoveDistance);
		}
	}
}

//-----------------------------------------------------------------------------

void Camera::SetAsPerspective(Vector3D aCentrePos, Vector3D aLookAtPos, Vector3D aUpVec, float aNear, float aFar, float aFieldOfView, float aAspect)
{
	instance->SetType(CAMERA_PERSPECTIVE);

	instance->SetNear(aNear);
	instance->SetFar(aFar);
	instance->SetFieldOfView(aFieldOfView);
	instance->SetAspect(aAspect);

	m_vPosition = aCentrePos;

	//Calculate and Normalize the facing vector.
	m_vFacing = Vector3D((aLookAtPos.x - aCentrePos.x), (aLookAtPos.y - aCentrePos.y), (aLookAtPos.z - aCentrePos.z));
	float magnitude = sqrt((m_vFacing.x*m_vFacing.x) + (m_vFacing.y*m_vFacing.y) + (m_vFacing.z*m_vFacing.z));
	m_vFacing = Vector3D((m_vFacing.x / magnitude), (m_vFacing.y / magnitude), (m_vFacing.z / magnitude));
	m_vStartFacing = m_vFacing;

	//Set the up vector.
	m_vUp = aUpVec;

	//Cross product to calculate the right vector.
	m_vRight = Vector3D((m_vFacing.y*m_vUp.z) - (m_vFacing.z*m_vUp.y),
		(m_vFacing.z*m_vUp.x) - (m_vFacing.x*m_vUp.z),
		(m_vFacing.x*m_vUp.y) - (m_vFacing.y*m_vUp.x));

}

//-----------------------------------------------------------------------------

void Camera::SetAsOrtho(Vector3D aCentre, Vector3D aLookAt, Vector3D aUp, float aLeft, float aRight, float aBottom, float aTop, float aNear, float aFar)
{
	instance->SetType(CAMERA_ORTHO);

	instance->SetLeft(aLeft);
	instance->SetRight(aRight);
	instance->SetTop(aTop);
	instance->SetBottom(aBottom);
	instance->SetNear(aNear);
	instance->SetFar(aFar);

	m_vPosition = aCentre;
	m_vFacing = Vector3D((aCentre.x - aLookAt.x), (aCentre.y - aLookAt.y), (aCentre.z - aLookAt.z));
	m_vUp = aUp;
	m_vRight = Vector3D((m_vFacing.y*m_vUp.z) - (m_vFacing.z*m_vUp.y),	//Cross product to calculate the right vector.
		(m_vFacing.z*m_vUp.x) - (m_vFacing.x*m_vUp.z),
		(m_vFacing.x*m_vUp.y) - (m_vFacing.y*m_vUp.x));

}

//-----------------------------------------------------------------------------

void Camera::Pitch(float aAngle)
{
	m_fPitchAngle += aAngle;
	
}

//-----------------------------------------------------------------------------

void Camera::Roll(float aAngle)
{
	m_fRollAngle += aAngle;
}

//-----------------------------------------------------------------------------

void Camera::Yaw(float aAngle)
{
	m_fYawAngle += aAngle;
}


//-----------------------------------------------------------------------------

void Camera::Zoom(float aDistance)
{
	m_vPosition.z -= aDistance;
}

//-----------------------------------------------------------------------------

void Camera::Strafe(float aDistance)
{
	m_vPosition.x += aDistance;
}

//-----------------------------------------------------------------------------

void Camera::MoveForward(float aDistance)
{
	m_vPosition.y += aDistance;
}

//-----------------------------------------------------------------------------