#pragma once
#include "entity.h"

	class Bulet :
	public Entity
	{
	public:
	//����������� ����
	Bullet(Image &image, String Name, Level &lvl,float X, float Y, int W, int H, int dir):Entity(image, Name, X, Y, W, H)//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir);
	
	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time)

	//����������	
	~Bulet(void);

	//������������� ���������� 
	int direction;//����������� ����
	};
