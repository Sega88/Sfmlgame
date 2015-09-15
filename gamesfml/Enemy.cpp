#include "Enemy.h"

	//Конструктор класса Враг
	Enemy::Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
	obj = lvl.GetObjects("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
	if (name == "EasyEnemy"){
	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = 0.1;
	}//Enemy
		
	//функция взаимодействия Врага с картой 
	void checkCollisionWithMap(float Dx, float Dy)
	{
	for (int i = 0; i<obj.size(); i++)//проходимся по объектам
	if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
	{
	//if (obj[i].name == "solid"){//если встретили препятствие (объект с именем solid)
		if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
		if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
		if (Dx>0)	{ x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
		if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
		//}
	}//if
	}//checkCollisionWithMap

	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time)
	{
		if (name == "EasyEnemy"){
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0){ life = false; }
		}
	}//update

	//диструктор
	Enemy::~Enemy(void)
	{
	}//~Enemy
