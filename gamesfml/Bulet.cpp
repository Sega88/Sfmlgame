#include "Bulet.h"

	Bulet::Bullet(Image &image, String Name, Level &lvl,float X, float Y, int W, int H, int dir):Entity(image, Name, X, Y, W, H)//всё так же, только взяли в конце состояние игрока (int dir)
	{
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
	}//bullet

	//функция "оживления" объекта класса. update - обновление. принимает в себя время SFML , вследствие чего работает бесконечно, давая персонажу движение.
	void update(float time)
	{
	switch(direction)
	{
	case 0: dx = -speed; dy=0; break;
	case 1: dx = speed; dy=0; break;
	case 2: dx = 0; dy = -speed; break;
	case 3: dx = 0; dy = -speed; break;
	case 4: dx = 0; dy = -speed; break;
	case 5: dx = 0; dy = -speed; break;
		case 6: dx = speed; dy = -speed; break;
	}//swith
	x+=dx*time;//само движение пули по х
	y+=dy*time;// по x

	if(x<=0) x=1;
	if(y<0) y=1;// задержка пули в левой стене, чтобы при проседании кадров она случайно не вылетела за предел карты и не было ошибки
	
	for(int i=0; i<obj.size(); i++)//проход по объектам solid
	{
		if (getRect().intersects(obj[i].rect))//если этот объект столкнулся с пулей,
		{
			life = false;// то пуля умирает
		}
	}//for
	sprite.setPosition(x+w/2, y+h/2);//задаем позицию спрайту
	}//update
	
	//Диструктор
	Bulet::~Bulet(void)
{
}
