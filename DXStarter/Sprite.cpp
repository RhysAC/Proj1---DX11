#include "CommonStates.h"
#include <DDSTextureLoader.h>

#include "Sprite.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void Sprite::SetTex(ID3D11ShaderResourceView& tex, const RECTF& texRect)
{
	mpTex = &tex;
	mTexRect = texRect;
}

void Sprite::Draw(SpriteBatch& batch)
{
	batch.Draw(mpTex, mPos, &(RECT)mTexRect, colour, rotation, origin, scale, DirectX::SpriteEffects::SpriteEffects_None, depth);
}

ID3D11ShaderResourceView* Sprite::LoadTexture(const wstring& path, ID3D11Device& device)
{
	DDS_ALPHA_MODE alpha;
	ID3D11ShaderResourceView* pT = nullptr;
	if (CreateDDSTextureFromFile(&device, path.c_str(), nullptr, &pT, 0, &alpha) != S_OK)
	{
		WDBOUT(L"Cannot load " << path << L"\n");
		assert(false);
		return nullptr;
	}
	assert(pT);
	return pT;
}


