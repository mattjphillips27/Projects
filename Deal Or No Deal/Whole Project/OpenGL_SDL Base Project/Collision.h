#ifndef COLLISION_H
#define COLLISION_H
#pragma once
// Collision - library of functions and classes for collision detection
#include "Commons.h"


class Sphere {
public:
	Sphere(Vector3D c, float r) 
	{
		centre = c; 
		radius = r; 
		collided = false; 
	}

	float GetBoundingRadius() const { return radius; }
	Vector3D GetCentre()  { return centre;  }
	void Update(Vector3D newPos) { centre = newPos;  }
	void SetCollided(bool c) { collided = c;  }
	bool GetCollided()  { return collided;  }
private:
	Vector3D centre;
	float radius;
	bool collided;
};

class Collision {
public:
	static bool SphereSphereCollision(Sphere *s1, Sphere *s2)
	{
		Vector3D centre1 = s1->GetCentre();
		Vector3D centre2 = s2->GetCentre();
		float dx = centre2.x - centre1.x;
		float dy = centre2.y - centre1.y;
		float dz = centre2.z - centre1.z;

		float dSquared = dx*dx + dy*dy + dz *dz;

		float sumOfBoundingRadii = s1->GetBoundingRadius() + s2->GetBoundingRadius();

		float hasCollided = false;
		if (dSquared < (sumOfBoundingRadii * sumOfBoundingRadii))
		{
			s1->SetCollided(true);
			s2->SetCollided(true);
			return true;
		}
		return false;
	}
};
#endif
