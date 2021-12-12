#include "GameObject.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;

void GameObject::CheckCollision(vector<GameObject*>& objects)
{
	if (objects.size() > 1)
	{
		for (size_t i = 0; i < objects.size(); ++i)
		{
			GameObject& a = *objects[i];
			if (a.active)
			{
				if (i < (objects.size() - 1))
					for (size_t ii = i + 1; ii < (objects.size()); ++ii)
					{
						GameObject& b = *objects[ii];
						if (b.active)
						{
							if (CircleToCircle(a.mModel.GetPosition(), b.mModel.GetPosition(), a.mRadius + b.mRadius))
							{
								a.colliding;
								b.colliding;
								a.Hit(b);
								b.Hit(a);
							}
						}
					}
			}
		}
	}
};