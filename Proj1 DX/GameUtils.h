#pragma once
#include "D3D.h"
#include "Model.h"
#include "Mesh.h"

void Setup(Model& m, Mesh& source, const DirectX::SimpleMath::Vector3& scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

void Setup(Model& m, Mesh& source, float scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

int GetPosOffScreen();