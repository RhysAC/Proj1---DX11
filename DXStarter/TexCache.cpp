#include <DDSTextureLoader.h>
#include <filesystem>

#include "TexCache.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

/*ID3D11ShaderResourceView* TexCache::LoadTexture(const wstring& path, ID3D11Device& device)
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
}*/


