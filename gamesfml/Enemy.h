#pragma once
#include "entity.h"

class Enemy :
	public Entity
{
public:
	
	//����������� ������ �����
	Enemy(Image &image, String Name,Level &lvl, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	
	//������� ���������� ������
	void control();

	//������� �������������� ����� � ������ 
	void checkCollisionWithMap(float Dx, float Dy);

	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time);
	
	//����������
	~Enemy(void);
};
