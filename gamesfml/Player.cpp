#include "Player.h"

	Player::Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
	playerScore = 0;
	state = stay;
	obj = lev.GetAllObjects();
	isShoot = 0;//��������������.�������� ��� ������� ��� �������������� ��������� � ������
	if (name == "Player1"){
		sprite.setTextureRect(IntRect(4, 19, w, h));
	}
	//������� ���������� �������
	void control(){
		   if (Keyboard::isKeyPressed){
			   if (Keyboard::isKeyPressed(Keyboard::Left)) {
				   state = left; speed = 0.1;
			   }
			   if (Keyboard::isKeyPressed(Keyboard::Right)) {
				   state = right; speed = 0.1;
			   }
 
			   if ((Keyboard::isKeyPressed(Keyboard::Up)) && (onGround)) {
				   state = jump; dy = -0.6; onGround = false;
			   }
 
			   if (Keyboard::isKeyPressed(Keyboard::Down)) {
				   state = down;
			   }

			    if ((Keyboard::isKeyPressed(Keyboard::Right)) && (Keyboard::isKeyPressed(Keyboard::Up))) {
				   state = right_Top;
			   }

			   //�������
			     if (Keyboard::isKeyPressed(Keyboard::Space)) {
				   isShoot = true;
			   }
		   }
	   }//control() 
	
	//������� �������������� ������ � ������ 
	 void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)//���������� �� ��������
		   if (getRect().intersects(obj[i].rect))//��������� ����������� ������ � ��������
		   {
			   if (obj[i].name == "solid")//���� ��������� �����������
			   {
				   if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				   if (Dx>0)	{ x = obj[i].rect.left - w; }
				   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			   }
		   }
	   }//checkCollisionWithMap

	//������� "���������" ������� ������. update - ����������. ��������� � ���� ����� SFML , ���������� ���� �������� ����������, ����� ��������� ��������.
	void update(float time)
	   {
		   control();
		   switch (state)//��� �������� ��������� �������� � ����������� �� ���������
		   {
		   case right:dx = speed; break;//��������� ���� ������
		   case left:dx = -speed; break;//��������� ���� �����
		   case up: break;//����� ��������� �������� ������ (�������� �� ��������)
		   case down: dx = 0; break;//����� ��������� �� ����� ������ ��������� (�������� �� ��������)
		   case stay: break;//����� ����� ���� ����� ��������
		   case right_Top: dx = speed; break; //��������� ������ �����, ������ ���������� ���� ������
		   }
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);//������������ ������������ �� �
		   y += dy*time;
		   checkCollisionWithMap(0, dy);//������������ ������������ �� Y
		   sprite.setPosition(x + w / 2, y + h / 2); //������ ������� ������� � ����� ��� ������
		   if (health <= 0){ life = false; }
		   if (!isMove){ speed = 0; }
		   setPlayerCoordinateForView(x, y);
		   if (life) { setPlayerCoordinateForView(x, y); }
		   dy = dy + 0.0015*time;//������ ���������� � �����
	   }//update

	//���������
	Player::~Player(void)
	{
	}
