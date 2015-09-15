#include "Entity.h"

//Конструктор класса
Entity::Entity(Image &image, String Name, float X, float Y, int W, int H)
{
	x = X; //координата X тайла
	y = Y; //координата Y тайла
	w = W; //ширина тайла
	h = H; //высота тайла
	name = Name; //имя объекта (игрок, враг, платформа, пуля)
	moveTimer = 0;
	speed = 0; 
	health = 100; //здоровье объекта
	dx = 0; //скорость объекта по X 
	dy = 0; //скорость объекта по Y
	life = true; //состояние объекта жив или мертв
	onGround = false; //объект находиться на земле или нет
	isMove = false; 
	texture.loadFromImage(image); //загрузка изображения в текстуру
	sprite.setTexture(texture); //загрузка текстуры в спрайт
	sprite.setOrigin(w / 2, h / 2);	//перенос основной точки объекта (центра координат объекта) из левого верхнего угла в центр объекта
	}//Entity

	//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	FloatRect getRect(){
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}//getRect()

	//Деструктор класса
	Entity::~Entity(void)
	{
	}//~Entity
