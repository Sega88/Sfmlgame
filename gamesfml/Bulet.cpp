#include "Bulet.h"

	Bulet::Bullet(Image &image, String Name, Level &lvl,float X, float Y, int W, int H, int dir):Entity(image, Name, X, Y, W, H)//�� ��� ��, ������ ����� � ����� ��������� ������ (int dir)
	{
		obj = lvl.GetObjects("solid");//�������������� .�������� ������ ������� ��� �������������� ���� � ������
		x = X;
		y = Y;
		direction = dir;
		speed = 0.8;
		w = h = 16;
		life = true;
	}//bullet

	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
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
	x+=dx*time;//���� �������� ���� �� �
	y+=dy*time;// �� x

	if(x<=0) x=1;
	if(y<0) y=1;// �������� ���� � ����� �����, ����� ��� ���������� ������ ��� �������� �� �������� �� ������ ����� � �� ���� ������
	
	for(int i=0; i<obj.size(); i++)//������ �� �������� solid
	{
		if (getRect().intersects(obj[i].rect))//���� ���� ������ ���������� � �����,
		{
			life = false;// �� ���� �������
		}
	}//for
	sprite.setPosition(x+w/2, y+h/2);//������ ������� �������
	}//update
	
	//����������
	Bulet::~Bulet(void)
{
}
