#include <SFML/Graphics.hpp>
//#include "map.h"
#include <iostream>
//#include <sstream> ��� ������ ������
#include <vector>
#include <list>
#include "view.h"
#include "mission.h"
#include "iostream"
#include "level.h"//����� ������
#include "Entity.h"//����� �������
#include "Player.h"//����� ������
#include "MovingPlatform.h"//����� ���������
#include "Bulet.h"//����� ����

#include "TinyXML/tinyxml.h"
 
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(640, 480), "Lesson 22. kychka-pc.ru");
	view.reset(FloatRect(0, 0, 640, 480));
 
	Level lvl;//������� ��������� ������ �������
	lvl.LoadFromFile("map.tmx");//��������� � ���� �����, ������ ������ � ������� ������� �� �� ����������.
 	
	Image heroImage;
	heroImage.loadFromFile("images/MilesTailsPrower.gif");
 
	Image easyEnemyImage;
	easyEnemyImage.loadFromFile("images/shamaich.png");
	easyEnemyImage.createMaskFromColor(Color(255, 0, 0));

	Image movePlatformImage;
	movePlatformImage.loadFromFile("images/MovingPlatform.png");
	
	Image BulletImage;//����������� ��� ����
	BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ �����������
	BulletImage.createMaskFromColor(Color(0, 0, 0));//����� ��� ���� �� ������� �����
	
	std::list<Entity*> entities;//������ ������, ���� ���� ������ �������.�������� ������.
	std::list<Entity*>::iterator it;//�������� ����� ��������� �� ��-��� ������
	std::list<Entity*>::iterator it2;//������ ��������.��� �������������� ����� ��������� ������

	std::vector<Object> e=lvl.GetObjects("easyEnemy");//��� ������� ����� �� tmx ����� �������� � ���� �������

	for(int i=0; i<e.size(); i++)//���������� �� ��������� ����� �������(� ������ �� ������)
		entities.push_back(new Enemy(easyEnemyImage, "EasyEnemy", lvl, e[i].rect.left, e[i].rect.top, 200, 97));//� ���������� � ������ ���� ����� ������ � �����

	Object player=lvl.GetObject("player");//������ ������ �� ����� �����.������ ���������� ������ � ������ ��� ������ ����
	 
	Player p(heroImage, "Player1", lvl, player.rect.left, player.rect.top, 40, 30);//�������� ���������� �������������� player �� ����� � ���������� ������ ������
	
	e=lvl.GetObjects("MovingPlatform");//�������� ��� ��������� � ������ 
	for(int i = 0; i < e.size(); i++)
		entities.push_back(new MovingPlatform(movePlatformImage, "MovingPlatform", lvl, e[i].rect.left, e[i].rect.top, 95,22));//���������� ��������� � ������.�������� ����������� ��� ������� ���������� ��������� (����� �� tmx �����), � ��� �� �������

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
		//������ ������ ����������
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::P) 
				{
					entities.push_back(new Bullet(BulletImage, "Bullet", lvl, p.x, p.y, 16, 16, p.state));
				}
			}

		}//while		
		
		for (it = entities.begin(); it != entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b->update(time);//�������� �-��� update ��� ���� �������� (�� ���� ��� ���, ��� ���)
			if (b->life == false)	{ it = entities.erase(it); delete b; }// ���� ���� ������ �����, �� ������� ���
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}

		
		
		for(it = entities.begin(); it!=entities.end();)//������� ��� ���������� �� ������ �� �����
		{
			Entity *b = *it;//��� ��������, ����� �� ������ (*it)->
			b -> update(time);//�������� �-��� update ��� ���� �������� (�� ��� ���, ��� ���)
			if(b->life==false)
			{
				it=entities.erase(it); delete b;//���� ���� ������ �����, �� ������� ���
			}//if 
			else it++;//� ���� �������� (����������) � ���� �������. ��� ������ �� ����� ��������� ������
		}//for

		for (it = entities.begin(); it != entities.end(); it++)//���������� �� ��-��� ������
		{	
/////////////////////////�������������� ������ � ���������////////////////////////////////////////
			if(((*it)->name == "MovingPlatform")&&((*it)->getRect().intersects(p.getRect())))//���� ����� ���������� � �������� ������ � ��� ����� ������� movingplatform
			{
			Entity *movPlat=*it;
				if((p.dy>0)||(p.onGround == false))//���� ����� ��������� ���� ���������, �.� ��� ��� ���� ������� (�� �� ��� ��������� ��� �� ���������� � ����������)
				if(p.y+p.h<movPlat->y+movPlat->h)//���� ����� ��������� ���� ���������, �.� ��� ��� ���� ������� (�� �� ��� ��������� ��� �� ���������� � ����������)
				{
				p.y = movPlat->y - p.h + 3; 
				p.x += movPlat->dx*time;
				p.dy=0;
				p.onGround = true;// �� ����������� ������ ���, ����� �� ��� �� ����� �� ���������
				}//if
			}//if	
/////////////////////////�������������� ����� � ������////////////////////////////////////////
			if ((*it)->getRect().intersects(p.getRect()))//���� ������������� ������� ������� ������������ � �������
			{
				if ((*it)->name == "EasyEnemy"){//� ��� ���� ��� ������� EasyEnemy,��..
					
					p.health -= 5; //���� ����� ����
					///////������������ ������
					if (p.dx < 0) { p.x = (*it)->x + (*it)->w;}//���� ����������� � ������ � ����� ���� ����� �� ����������� ������
					if (p.dx > 0) { p.x = (*it)->x - p.w;}//���� ����������� � ������ � ����� ���� ������ �� ����������� ������
				}//if
			}//if

/////////////////////////�������������� ����� � ����////////////////////////////////////////
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
				if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "Bullet"))//���� ����������� ��� ������� ���� � ���� 
				{
					(*it)->life = false;//�������� �����
					}//if
			}//for
/////////////////////////�������������� ������////////////////////////////////////////
			for (it2 = entities.begin(); it2 != entities.end(); it2++)
			{
				if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ ��������������
				if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� �����
				{
					(*it)->dx *= -1;//������ ����������� �������� �����
					(*it)->sprite.scale(-1, 1);//�������� ������ �� �����������
				}//if
			}//for
		}//for

		p.update(time);
		window.setView(view);
		window.clear(Color(77,83,140));
		lvl.Draw(window);//������ ����� �����
 
		
		for(it = entities.begin(); it !=entities.end(); it++)
		{
			window.draw((*it)->sprite);//������ entities ������� (������ ��� ������ �����)
		}//for
		window.draw(p.sprite);
		window.display();
	}
	return 0;
}