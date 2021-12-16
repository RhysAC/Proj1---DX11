#pragma once
#include "GameObject.h"
#include "Bullet.h"
class Player : public GameObject
{
public:
	//default constructor
	Player(){}
	/*A function to initialise certain data for the Player
	*IN : Bullet bullet, Mesh sm
	*OUT :
	*PRE_CONDITION : A valid bullet and mesh must have been initialised
	*POST_CONDITION : The pBullet pointer with reference the passed in bullet and the mesh will be assigned to the player model */
	void Init(Bullet& bullet, Mesh& sm);
	/* A function to Update the logic for the Player
	*IN : float dTime
	*OUT :
	*PRE_CONDITION : dTime time must have been set
	*POST_CONDITION : The player will update it's logic */
	void Update(float dTime);
	// Render the player model to the screen
	void Render();
	/* A function to fire a bullet from the players current location
	*IN : Vector3 pos, Vector3 aimDir
	*OUT :
	*PRE_CONDITION : both the passed in vectors must be valid and the player must be active in the scene
	*POST_CONDITION : A bullet will spawn at the player's location and move accordingly */
	void FireBullet(DirectX::SimpleMath::Vector3& pos, DirectX::SimpleMath::Vector3& aimDirNorm);
	// Deal a given amount of damage to the player's health
	void TakeDamage(int damage);
	// A small function that runs when the player is not playing, showing a small idle 'animation'
	void MenuIdle(float dTime);
	// Reset the player's health and position 
	void ResetPlayer();
	// Mouse and key input
	MouseAndKeys sMKIn;
private:
	// Pointer to the bullet object
	Bullet* pBullet = nullptr;
	/* A function that changes data dependent upon the User's input
	*IN : float dTime
	*OUT :
	*PRE_CONDITION : A valid dTime must be passed in. We must be getting input
	*POST_CONDITION : The player will move and fire bullets according to the user input*/
	void HandleInput(float dTime);
};

