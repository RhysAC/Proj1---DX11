#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <d3d11.h>

#include "D3DUtil.h"

class TexCache
{
public:
	ID3D11ShaderResourceView* LoadTexture(const std::wstring& path, ID3D11Device& device);
};


