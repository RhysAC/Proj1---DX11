#include "Utils.h"
#include "D3D.h"

using namespace std;

//handy rectangle definer
struct RECTF
{
	float left, top, right, bottom;
	operator RECT() {
		return RECT{ (int)left,(int)top,(int)right,(int)bottom };
	}
};