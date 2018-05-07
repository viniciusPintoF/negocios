#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:


	Enemy();
	~Enemy();
	
	void load(const LoaderParams *parameters);

	void draw();

	void update();

	void clean();

};

class EnemyCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new Enemy(); }
};

#endif
