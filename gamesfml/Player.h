#pragma once
#include "entity.h"

class Player :
	public Entity
{
public:
	//конструктор класса Игрок
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H );

	//Функция управления игроком
	void control();

	//функция взаимодействия игрока с картой 
	void checkCollisionWithMap(float Dx, float Dy);

	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time);

	//деструктор класса Игрок
	~Player(void);

	//Инициализация переменных 
	enum { left, right, up, down, jump, stay, right_Top } state; //добавляем тип перечисления - состояние Игрока
	int playerScore;
	bool isShoot; //стрельба
};
