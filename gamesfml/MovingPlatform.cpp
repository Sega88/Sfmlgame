#include "MovingPlatform.h"

	//����������� ���������
	MovingPlatform::MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H)
	{
	sprite.setTextureRect(IntRect(0, 0, W, H));//������������� 
	dx=0.08;//����������� ��������� �� �
	}//MovingPlatform

	//������� ���������� ���������.
	void update(float time)
	{
	x+=dx*time;//���������� �������� �� �����������
	moveTimer+=time;//���������� ������
	if(moveTimer>2000)
		{
			dx*=-1; moveTimer=0;//���� ������ �������� 2 ���, �� �������� ����������� �������� ���������,� ������ ����������
		}//if
	sprite.setPosition(x+w/2, y+h/2);//������� �������� ����� ������� (������ ��������� �������) �� ������ �������� ���� � ����� �������
	}//update
	
	//����������
	MovingPlatform::~MovingPlatform(void)
	{
	}//~MovingPlatform