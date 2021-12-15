#pragma once
#include "D3D.h"
#include "Model.h"
#include "Mesh.h"

/*A function that sets up a model with some starting values and a paired mesh
 *IN : Model& m, Mesh& source, const Vector3& scale, const Vector3& pos, Vector3& rot
 *OUT :
 *PRE_CONDITION : a valid model and mesh must be passed in. the inital values must also be set otherwise we may not see the object
 *POST_CONDITION :  model is assigned a mesh, along with inital scale, position and rotation*/
void Setup(Model& m, Mesh& source, const DirectX::SimpleMath::Vector3& scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

/*A function that sets up a model with some starting values and a paired mesh, to be used when importing with ASSIMP
 *IN : Model& m, Mesh& source, const Vector3& scale, const Vector3& pos, Vector3& rot
 *OUT : 
 *PRE_CONDITION : a valid model and mesh must be passed in. the inital values must also be set otherwise we may not see the object
 *POST_CONDITION :  model is assigned a mesh, along with inital scale, position and rotation*/
void Setup(Model& m, Mesh& source, float scale, const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& rot);

/*A function that gets a random position, forwards, out of view of the camera
 *IN : 
 *OUT : int position
 *PRE_CONDITION : We must have set a random seed with SRAND, otherwise it wont be random
 *POST_CONDITION :  a position is returned with a random value to be used with the x coordinate*/
int GetPosOffScreen();
/*A function that checks the distance between two objects' circle positions
 *IN : const Vector3 pos1, const Vector3 pos2, float minDist
 *OUT : bool distance < minDist
 *PRE_CONDITION : 2 valid positions must be passed in to the function with a minimum distance set
 *POST_CONDITION :  a boolean will be returned stating the distance is less than the minimum distance*/
bool CircleToCircle(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2, float minDist);