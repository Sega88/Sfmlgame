#pragma once
#include "entity.h"

	class MovingPlatform :
	public Entity
	{
	public:
	//����������� ���������
	MovingPlatform(Image &image, String Name, Level &lvl, float X, float Y, int W, int H):Entity(image, Name, X, Y, W, H);
	
	//������� ���������� ���������.
	void update(float time);

	//����������
	~MovingPlatform(void);
	};
