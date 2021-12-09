#pragma once
#include "D3D.h"
#include "Model.h"
#include "Mesh.h"

void Setup(Model& m, Mesh& source, const DirectX::SimpleMath::Vector3& scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

void Setup(Model& m, Mesh& source, float scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

DirectX::SimpleMath::Vector3 Getdirection(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& otherPos);

DirectX::SimpleMath::Vector3 GetCurrentVel(DirectX::SimpleMath::Vector3& dir, float speed);

float LookAt(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& otherPos);