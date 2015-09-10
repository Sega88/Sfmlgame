#include <SFML/Graphics.hpp>
//#include "map.h"
#include "view.h"
#include <iostream>
//#include <sstream> для вывода текста
#include "mission.h"
#include "iostream"
#include "level.h"
#include <vector>
#include <list>
 
#include "TinyXML/tinyxml.h"
 
using namespace sf;

////////////////////////////////////Общий класс-родитель//////////////////////////
class Entity {
public:
	std::vector<Object> obj;//вектор объектов карты
	float dx, dy, x, y, speed, moveTimer;
	int w, h, health;
	bool life, isMove, onGround;
	Texture texture;
	Sprite sprite;
	String name;
	Entity(Image &image, String Name, float X, float Y, int W, int H){
		x = X; y = Y; w = W; h = H; name = Name; moveTimer = 0;
		speed = 0; health = 100; dx = 0; dy = 0;
		life = true; onGround = false; isMove = false;
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
	}
 
	FloatRect getRect(){//ф-ция получения прямоугольника. его коорд,размеры (шир,высот).
		return FloatRect(x, y, w, h);//эта ф-ция нужна для проверки столкновений 
	}

	virtual void update(float time)=0;
};
////////////////////////////////////////////////////КЛАСС ИГРОКА////////////////////////
class Player :public Entity {
public:
	enum { left, right, up, down, jump, stay, right_Top } state;
	int playerScore;
	bool isShoot;
 
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H ){
		   playerScore = 0;
		   state = stay;
		   obj = lev.GetAllObjects();
		   isShoot = 0;//инициализируем.получаем все объекты для взаимодействия персонажа с картой
		   if (name == "Player1"){
			   sprite.setTextureRect(IntRect(4, 19, w, h));
		   }
	   }
 
	   void control(){
		   if (Keyboard::isKeyPressed){
			   if (Keyboard::isKeyPressed(Keyboard::Left)) {
				   state = left; speed = 0.1;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right)) {
				   state = right; speed = 0.1;
			   }
 
			   if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
				   state = jump; dy = -0.6; onGround = false;
			   }
 
			   if (Keyboard::isKeyPressed(Keyboard::Down)) {
				   state = down;
			   }

			    if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) {
				   state = right_Top;
			   }

			   //выстрел
			     if (Keyboard::isKeyPressed(Keyboard::Space)) {
				   isShoot = true;
			   }
		   }
	   } 
 
	   
 
	   void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)//проходимся по объектам
		   if (getRect().intersects(obj[i].rect))//проверяем пересечение игрока с объектом
		   {
			   if (obj[i].name == "solid")//если встретили препятствие
			   {
				   if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				   if (Dx>0)	{ x = obj[i].rect.left - w; }
				   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			   }
		   }
	   }
	    
	   void update(float time)
	   {
		   control();
		   switch (state)
		   {
		   case right:dx = speed; break;
		   case left:dx = -speed; break;
		   case up: break;
		   case down: dx = 0; break;
		   case stay: break;
		   case right_Top: dx = speed; break; //состояние вправо вверх, просто продолжаем идти вправо
		   }
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);
		   y += dy*time;
		   checkCollisionWithMap(0, dy);
		   sprite.setPosition(x + w / 2, y + h / 2);
		   if (health <= 0){ life = false; }
		   if (!isMove){ speed = 0; }
		   setPlayerCoordinateForView(x, y);
		   if (life) { setPlayerCoordinateForView(x, y); }
		   dy = dy + 0.0015*time;
	   } 
};
 
 
 
class Enemy :public Entity{
public:
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H){
		obj = lvl.GetObjects("solid");//инициализируем.получаем нужные объекты для взаимодействия врага с картой
		if (name == "EasyEnemy"){
			sprite.setTextureRect(IntRect(0, 0, w, h));
			dx = 0.1;
		}
	}
 
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
		}
	}
 
	void update(float time)
	{
		if (name == "EasyEnemy"){
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//меняет направление примерно каждые 3 сек
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0){ life = false; }
		}
	}
};
class MovingPlatform: public Entity//класс движущейся платформы
{
public:
	MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H)
	{
	sprite.setTextureRect(IntRect(0, 0, W, H));//прямоугольник 
	dx=0.08;//изначальное ускорение по Х
	}
	void update(float time)//функция обновления платформы.
	{
	x+=dx*time;//реализация движения по горизонтали
	moveTimer+=time;//наращиваем таймер
	if(moveTimer>2000)
		{
			dx*=-1; moveTimer=0;//если прошло примерно 2 сек, то меняется направление движения платформы,а таймер обнуляется
		}//if
	sprite.setPosition(x+w/2, y+h/2);//задаем позицию спрайту
	}//update
	};//MovingPlatform

class Bullet:public Entity
{
public:
	int direction;//направление пули
	
	Bullet(Image &image, String Name, Level &lvl,float X, float Y, int W, int H, int dir):Entity(image, Name, X, Y, W, H)//всё так же, только взяли в конце состояние игрока (int dir)
	{
		obj = lvl.GetObjects("solid");//инициализируем .получаем нужные объекты для взаимодействия пули с картой
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
	}//bullet

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
};//class Bullet
int main()
{
	RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
	view.reset(FloatRect(0, 0, 640, 480));
 
	Level lvl;//создали экземпляр класса уровень
	lvl.LoadFromFile("map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.
 	
	Image heroImage;
	heroImage.loadFromFile("images/MilesTailsPrower.gif");
 
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));

	Image movePlatformImage;
	movePlatformImage.loadFromFile("images/MovingPlatform.png");
	
	Image BulletImage;//изображение для пули
	BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения
	BulletImage.createMaskFromColor(Color(0, 0, 0));//маска для пули по черному цвету
	
	std::list<Entity*> entities;//создаю список, сюда буду кидать объекты.например врагов.
	std::list<Entity*>::iterator it;//итератор чтобы проходить по эл-там списка
	std::list<Entity*>::iterator it2;//второй итератор.для взаимодействия между объектами списка

	std::vector<Object> e=lvl.GetObjects("easyEnemy");//все объекты врага на tmx карте хранятся в этом векторе

	for(int i=0; i<e.size(); i++)//проходимся по элементам этого вектора(а именно по врагам)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));//и закидываем в список всех наших врагов с карты

	Object player=lvl.GetObject("player");//объект игрока на нашей карте.задаем координаты игроку в начале при помощи него
	 
	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);//передаем координаты прямоугольника player из карты в координаты нашего игрока
	
	e=lvl.GetObjects("MovingPlatform");//забираем все платформы в вектор 
	for(int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(movePlatformImage, "MovingPlatform", lvl, e[i].rect.left, e[i].rect.top, 95,22));//закидываем платформу в список.передаем изображение имя уровень координаты появления (взяли из tmx карты), а так же размеры

	Clock clock;
	while (window.isOpen())
	{
 
		float time = clock.getElapsedTime().asMicroseconds();
 
		clock.restart();
		time = time / 800;
		
		Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed)||(Keyboard::isKeyPressed(Keyboard::Escape)))
				window.close();	
		if(p.isShoot==true)
		{
		p.isShoot=false;
		entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state));
		}//if
		//второй варант стрельнуть
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P) 
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state));
				}
			}

		}//while		
		
		for (it = entities.begin(); it != entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив)
			if (b->life == false)	{ it = entities.erase(it); delete b; }// если этот объект мертв, то удаляем его
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}

		
		
		for(it = entities.begin(); it!=entities.end();)//говорим что проходимся от начала до конца
		{
			Entity *b = *it;//для удобства, чтобы не писать (*it)->
			b -> update(time);//вызываем ф-цию update для всех объектов (по для тех, кто жив)
			if(b->life==false)
			{
				it=entities.erase(it); delete b;//если этот объект мертв, то удаляем его
			}//if 
			else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка
		}//for

		for (it = entities.begin(); it != entities.end(); it++)//проходимся по эл-там списка
		{	
/////////////////////////Взаимодействие игрока и платформы////////////////////////////////////////
			if(((*it)->name == "MovingPlatform")&&((*it)->getRect().intersects(p.getRect())))//если игрок столкнулся с объектом списка и имя этого объекта movingplatform
			{
			Entity *movPlat=*it;
				if((p.dy>0)||(p.onGround == false))//если игрок находится выше платформы, т.е это его ноги минимум (тк мы уже проверяли что он столкнулся с платформой)
				if(p.y+p.h<movPlat->y+movPlat->h)//если игрок находится выше платформы, т.е это его ноги минимум (тк мы уже проверяли что он столкнулся с платформой)
				{
				p.y = movPlat->y - p.h + 3; 
				p.x += movPlat->dx*time;
				p.dy=0;
				p.onGround = true;// то выталкиваем игрока так, чтобы он как бы стоял на платформе
				}//if
			}//if	
/////////////////////////Взаимодействие врага и игрока////////////////////////////////////////
			if ((*it)->getRect().intersects(p.getRect()))//если прямоугольник спрайта объекта пересекается с игроком
			{
				if ((*it)->name == "EasyEnemy"){//и при этом имя объекта EasyEnemy,то..
					
					p.health -= 5; //враг нанес урон
					///////выталкивание игрока
					if (p.dx < 0) { p.x = (*it)->x + (*it)->w;}//если столкнулись с врагом и игрок идет влево то выталкиваем игрока
					if (p.dx > 0) { p.x = (*it)->x - p.w;}//если столкнулись с врагом и игрок идет вправо то выталкиваем игрока
				}//if
			}//if

/////////////////////////Взаимодействие врага и пули////////////////////////////////////////
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
				if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))//если столкнулись два объекта пуля и враг 
				{
					(*it)->life = false;//убийство врага
					}//if
			}//for
/////////////////////////Взаимодействие врагов////////////////////////////////////////
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники
				if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//если столкнулись два объекта и они враги
				{
					(*it)->dx *= -1;//меняем направление движения врага
					(*it)->sprite.scale(-1, 1);//отражаем спрайт по горизонтали
				}//if
			}//for
		}//for

		p.update(time);
		window.setView(view);
		window.clear(Color(77,83,140));
		lvl.Draw(window);//рисуем новую карту
 
		
		for(it = entities.begin(); it !=entities.end(); it++)
		{
			window.draw((*it)->sprite);//рисуем entities объекты (сейчас это только враги)
		}//for
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}