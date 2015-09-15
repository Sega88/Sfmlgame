#include "Player.h"

	Player::Player(Image &image, String Name, Level &lev, float X, float Y, int W, int H) :Entity(image, Name, X, Y, W, H)
	{
	playerScore = 0;
	state = stay;
	obj = lev.GetAllObjects();
	isShoot = 0;//инициализируем.получаем все объекты дл€ взаимодействи€ персонажа с картой
	if (name == "Player1"){
		sprite.setTextureRect(IntRect(4, 19, w, h));
	}
	//‘ункци€ управлени€ игроком
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

			   //выстрел
			     if (Keyboard::isKeyPressed(Keyboard::Space)) {
				   isShoot = true;
			   }
		   }
	   }//control() 
	
	//функци€ взаимодействи€ игрока с картой 
	 void checkCollisionWithMap(float Dx, float Dy)
	   {
		   for (int i = 0; i<obj.size(); i++)//проходимс€ по объектам
		   if (getRect().intersects(obj[i].rect))//провер€ем пересечение игрока с объектом
		   {
			   if (obj[i].name == "solid")//если встретили преп€тствие
			   {
				   if (Dy>0)	{ y = obj[i].rect.top - h;  dy = 0; onGround = true; }
				   if (Dy<0)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				   if (Dx>0)	{ x = obj[i].rect.left - w; }
				   if (Dx<0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			   }
		   }
	   }//checkCollisionWithMap

	//функци€ "оживлени€" объекта класса. update - обновление. принимает в себ€ врем€ SFML , вследствие чего работает бесконечно, дава€ персонажу движение.
	void update(float time)
	   {
		   control();
		   switch (state)//тут делаютс€ различные действи€ в зависимости от состо€ни€
		   {
		   case right:dx = speed; break;//состо€ние идти вправо
		   case left:dx = -speed; break;//состо€ние идти влево
		   case up: break;//будет состо€ние подн€ти€ наверх (например по лестнице)
		   case down: dx = 0; break;//будет состо€ние во врем€ спуска персонажа (например по лестнице)
		   case stay: break;//здесь может быть вызов анимации
		   case right_Top: dx = speed; break; //состо€ние вправо вверх, просто продолжаем идти вправо
		   }
		   x += dx*time;
		   checkCollisionWithMap(dx, 0);//обрабатываем столкновение по ’
		   y += dy*time;
		   checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
		   sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		   if (health <= 0){ life = false; }
		   if (!isMove){ speed = 0; }
		   setPlayerCoordinateForView(x, y);
		   if (life) { setPlayerCoordinateForView(x, y); }
		   dy = dy + 0.0015*time;//делаем прит€жение к земле
	   }//update

	//ƒестуктор
	Player::~Player(void)
	{
	}
