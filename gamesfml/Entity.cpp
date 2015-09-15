#include "Entity.h"

//����������� ������
Entity::Entity(Image &image, String Name, float X, float Y, int W, int H)
{
	x = X; //���������� X �����
	y = Y; //���������� Y �����
	w = W; //������ �����
	h = H; //������ �����
	name = Name; //��� ������� (�����, ����, ���������, ����)
	moveTimer = 0;
	speed = 0; 
	health = 100; //�������� �������
	dx = 0; //�������� ������� �� X 
	dy = 0; //�������� ������� �� Y
	life = true; //��������� ������� ��� ��� �����
	onGround = false; //������ ���������� �� ����� ��� ���
	isMove = false; 
	texture.loadFromImage(image); //�������� ����������� � ��������
	sprite.setTexture(texture); //�������� �������� � ������
	sprite.setOrigin(w / 2, h / 2);	//������� �������� ����� ������� (������ ��������� �������) �� ������ �������� ���� � ����� �������
	}//Entity

	//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	FloatRect getRect(){
		return FloatRect(x, y, w, h);//��� �-��� ����� ��� �������� ������������ 
	}//getRect()

	//���������� ������
	Entity::~Entity(void)
	{
	}//~Entity
