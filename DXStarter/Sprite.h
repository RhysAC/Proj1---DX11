#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <d3d11.h>

#include "SpriteBatch.h"
#include "D3DUtil.h"

struct RECTF
{
	float left, top, right, bottom;
	operator RECT() {
		return RECT{ (int)left,(int)top,(int)right,(int)bottom };
	}
};

class Sprite
{
public:
	Sprite()
		:mPos(0, 0), mVel(0, 0),
		depth(0), mTexRect{ 0,0,0,0 }, colour(1, 1, 1, 1),
		rotation(0), scale(1, 1), origin(0, 0), mpTex(nullptr)
	{}
	ID3D11ShaderResourceView* LoadTexture(const std::wstring& path, ID3D11Device& device);
	void SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect = RECTF{ 0,0,0,0 });
	void Draw(DirectX::SpriteBatch& batch);
	ID3D11ShaderResourceView* mpTex;
	DirectX::SimpleMath::Vector2 mPos;
	RECTF mTexRect;
	DirectX::SimpleMath::Vector2 scale;
	DirectX::SimpleMath::Vector2 mVel;
	float depth;
	DirectX::SimpleMath::Vector4 colour;
	float rotation;
	DirectX::SimpleMath::Vector2 origin;
};

