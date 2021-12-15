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

int GetPosOffScreen() 
{
	//Get random value between -4 and + 4
	int pos = - 4 + rand() % 8;
	return pos;
}

bool CircleToCircle(const Vector3& pos1, const Vector3& pos2, float minDist)
{
	float dist = (pos1.x - pos2.x) * (pos1.x - pos2.x) +
		(pos1.z - pos2.z) * (pos1.z - pos2.z);
	dist = sqrtf(dist);
	return dist <= minDist;
}