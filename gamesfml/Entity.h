#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>


class Entity
{
public:
	//Инициализация переменных
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer; //скорость объекта по X, скорость объекта по Y, X координата об., Y координата об.,  
	int w, h, health; //ширина объекта, высота объекта, здоровье объекта
	bool life, isMove, onGround;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name; //Имя объекта (игрок, враг, платформа, пуля)
	//Конструктор класса
	Entity(sf::Image &image, sf::String Name, float X, float Y, int W, int H);

	//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
	FloatRect getRect();

	//виртуальная функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	virtual void update(float time)=0;

	//деструктор класса
	~Entity(void);
	
	
};//Entity


#endif