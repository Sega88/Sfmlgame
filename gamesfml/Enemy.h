#pragma once
#include "entity.h"

class Enemy :
	public Entity
{
public:
	
	//конструктор класса Врага
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	
	//Функция управления Врагом
	void control();

	//функция взаимодействия Врага с картой 
	void checkCollisionWithMap(float Dx, float Dy);

	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time);
	
	//деструктор
	~Enemy(void);
};
