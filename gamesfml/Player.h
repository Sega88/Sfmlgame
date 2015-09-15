#pragma once
#include "entity.h"

class Player :
	public Entity
{
public:
	//����������� ������ �����
	Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H );

	//������� ���������� �������
	void control();

	//������� �������������� ������ � ������ 
	void checkCollisionWithMap(float Dx, float Dy);

	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time);

	//���������� ������ �����
	~Player(void);

	//������������� ���������� 
	enum { left, right, up, down, jump, stay, right_Top } state; //��������� ��� ������������ - ��������� ������
	int playerScore;
	bool isShoot; //��������
};
