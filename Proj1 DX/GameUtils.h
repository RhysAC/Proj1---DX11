#pragma once
#include "D3D.h"
#include "Model.h"
#include "Mesh.h"

void Setup(Model& m, Mesh& source, const DirectX::SimpleMath::Vector3& scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

void Setup(Model& m, Mesh& source, float scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

int GetPosOffScreen();

/*A function that checks the distance between two objects' circle positions
 *IN : const Vector2f& pos1, const Vector2f& pos2, float minDist
 *OUT : bool distance < minDist
 *PRE_CONDITION : 2 valid positions must be passed in to the function with a minimum distance set
 *POST_CONDITION :  a boolean will be returned stating the distance is less than the minimum distance*/
bool CircleToCircle(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2, float minDist);