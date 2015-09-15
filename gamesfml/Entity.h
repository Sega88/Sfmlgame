#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>


class Entity
{
public:
	//������������� ����������
	std::vector<Object> obj;//������ �������� �����
	float dx, dy, x, y, speed, moveTimer; //�������� ������� �� X, �������� ������� �� Y, X ���������� ��., Y ���������� ��.,  
	int w, h, health; //������ �������, ������ �������, �������� �������
	bool life, isMove, onGround;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name; //��� ������� (�����, ����, ���������, ����)
	//����������� ������
	Entity(sf::Image &image, sf::String Name, float X, float Y, int W, int H);

	//�-��� ��������� ��������������. ��� �����,������� (���,�����).
	FloatRect getRect();

	//����������� ������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	virtual void update(float time)=0;

	//���������� ������
	~Entity(void);
	
	
};//Entity


#endif