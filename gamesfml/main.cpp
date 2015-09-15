#include <SFML/Graphics.hpp>
//#include "map.h"
#include <iostream>
//#include <sstream> для вывода текста
#include <vector>
#include <list>
#include "view.h"
#include "mission.h"
#include "iostream"
#include "level.h"//класс уровня
#include "Entity.h"//класс объекта
#include "Player.h"//класс игрока
#include "MovingPlatform.h"//класс платформы
#include "Bulet.h"//класс пули

#include "TinyXML/tinyxml.h"
 
using namespace sf;

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