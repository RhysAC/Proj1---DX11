#include "GameUtils.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Setup(Model& m, Mesh& source, const Vector3& scale, const Vector3& pos, const Vector3& rot)
{
	m.Initialise(source);
	m.GetScale() = scale;
	m.GetPosition() = pos;
	m.GetRotation() = rot;
}

void Setup(Model& m, Mesh& source, float scale, const Vector3& pos, const Vector3& rot)
{
	Setup(m, source, Vector3(scale, scale, scale), pos, rot);
}

Vector3 Getdirection(Vector3& pos, Vector3& otherPos)
{
	Vector3 aimDir = otherPos - pos;
	// N = V / Sqrt(V.x^2 + V.z^2)
	aimDir.Normalize();
	return aimDir;
}

Vector3 GetCurrentVel(Vector3& dir, float speed)
{
	Vector3 currentVel;
	currentVel = dir * speed;
	return currentVel;
}

float LookAt(Vector3& pos, Vector3& otherPos)
{
	float dx = pos.x - otherPos.x;
	float dz = pos.z - otherPos.z;

	float rotation = (atan2(dz, dx)) * 180 / PI ;
	return rotation;
}