#include "Enemy.h"

	//����������� ������ ����
	Enemy::Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
	obj = lvl.GetObjects("solid");//��������������.�������� ������ ������� ��� �������������� ����� � ������
	if (name == "EasyEnemy"){
	sprite.setTextureRect(IntRect(0, 0, w, h));
	dx = 0.1;
	}//Enemy
		
	//������� �������������� ����� � ������ 
	void checkCollisionWithMap(float Dx, float Dy)
	{
	for (int i = 0; i<obj.size(); i++)//���������� �� ��������
	if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
	{
	//if (obj[i].name == "solid"){//���� ��������� ����������� (������ � ������ solid)
		if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
		if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
		if (Dx>0)	{ x = obj[i].rect.left - w;  dx = -0.1; sprite.scale(-1, 1); }
		if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; dx = 0.1; sprite.scale(-1, 1); }
		//}
	}//if
	}//checkCollisionWithMap

	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time)
	{
		if (name == "EasyEnemy"){
			//moveTimer += time;if (moveTimer>3000){ dx *= -1; moveTimer = 0; }//������ ����������� �������� ������ 3 ���
			checkCollisionWithMap(dx, 0);
			x += dx*time;
			sprite.setPosition(x + w / 2, y + h / 2);
			if (health <= 0){ life = false; }
		}
	}//update

	//����������
	Enemy::~Enemy(void)
	{
	}//~Enemy
