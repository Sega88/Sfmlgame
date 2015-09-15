#include "MovingPlatform.h"

	//Конструктор Платформы
	MovingPlatform::MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H)
	{
	sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
	dx=0.08;//изначальное ускорение по Х
	}//MovingPlatform

	//функция обновления платформы.
	void update(float time)
	{
	x+=dx*time;//реализация движения по горизонтали
	moveTimer+=time;//наращиваем таймер
	if(moveTimer>2000)
		{
			dx*=-1; moveTimer=0;//если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
		}//if
	sprite.setPosition(x+w/2, y+h/2);//перенос основной точки объекта (центра координат объекта) из левого верхнего угла в центр объекта
	}//update
	
	//Диструктор
	MovingPlatform::~MovingPlatform(void)
	{
	}//~MovingPlatform