#pragma once
#include "entity.h"

	class MovingPlatform :
	public Entity
	{
	public:
	//Конструктор Платформы
	MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H);
	
	//функция обновления платформы.
	void update(float time);

	//Диструктор
	~MovingPlatform(void);
	};
