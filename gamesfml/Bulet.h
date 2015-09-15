#pragma once
#include "entity.h"

	class Bulet :
	public Entity
	{
	public:
	//Конструктор пули
	Bullet(Image &image, String Name, Level &lvl,float X, float Y, int W, int H, int dir):Entity(image, Name, X, Y, W, H)//всё так же, только взяли в конце состояние игрока (int dir);
	
	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time)

	//Диструктор	
	~Bulet(void);

	//Инициализация переменных 
	int direction;//направление пули
	};
