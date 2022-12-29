//1. ������ �ӵ�����,����������
//2 �Ѿ� �ý��� ����
//3.sound effect

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int speed;
	int score;
	int life;
	float x;
	float y;    //�÷��̾� ��ǥ
};

//�Ѿ�
struct Bullet {
	RectangleShape sprite;
	int is_fired;               //�߻� ����
};



struct Enemy {
	RectangleShape sprite;
	int speed;
	int life;
	int score;
	SoundBuffer explosion_buffer;
	Sound explosion_sound;
	int respawn_time;
};

struct Textures {
	Texture bg;    //��� �̹���
	Texture enemy;
	Texture gameover;     //gameover �̹���
	Texture player;    //�÷��̾� �̹���
};

//obj1 obj2 �浹���� �浹 1��ȯ �浹���ϸ� 0 ��ȯ
int is_collide(RectangleShape obj1, RectangleShape obj2) {
	return obj1.getGlobalBounds().intersects(obj2.getGlobalBounds());
}

// ��������
const int ENEMY_NUM = 10;					// enemy�� �ִ밳��
const int BULLET_NUM = 50;                 //bullet�� �ִ밳��
const int W_WIDTH = 1130, W_HEIGHT = 700;	// â�� ũ��
const int GO_WIDTH = 320, GO_HEIGHT = 240;	// ���ӿ��� �׸��� ũ��



int main(void)
{
	struct Textures t;
	t.bg.loadFromFile("./resources/images/1.jpg");
	t.gameover.loadFromFile("./resources/images/2.jpg.png");
	t.player.loadFromFile("./resources/images/face.png");
	t.enemy.loadFromFile("./resources/images/hehe.png");

	// ����â ����
	RenderWindow window(VideoMode(W_WIDTH, W_HEIGHT), "AfterSchool");
	window.setFramerateLimit(60);

	srand(time(0));

	long start_time = clock();	// ���� ���۽ð�
	long spent_time;			// ���� ����ð�
	int is_gameover = 0;

	// BGM
	SoundBuffer BGM_buffer;
	BGM_buffer.loadFromFile("./resources/sound/funbgm032014(fun).wav");
	Sound BGM_sound;
	BGM_sound.setBuffer(BGM_buffer);
	BGM_sound.setLoop(1);		// BGM ���ѹݺ�
	BGM_sound.play();

	// text
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(30);		// ����ũ�� ����
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(0, 0);
	char info[40];

	// ���
	Texture t_bg;
	t_bg.loadFromFile("./resources/images/1.jpg");
	Sprite bg_sprite;
	bg_sprite.setTexture(t_bg);
	bg_sprite.setPosition(0, 0);

	// gameover
	Sprite gameover_sprite;
	
	gameover_sprite.setTexture(t.gameover);
	gameover_sprite.setPosition((W_WIDTH - GO_WIDTH) / 2.6, (W_HEIGHT - GO_HEIGHT) / 2);

	// �÷��̾�
	struct Player player;
	player.sprite.setTexture(&t.player);
	player.sprite.setSize(Vector2f(110, 158));
	player.sprite.setPosition(100, 100);
	player.x = player.sprite.getPosition().x;
	player.y = player.sprite.getPosition().y;
	player.speed = 5;
	player.score = 0;
	player.life = 10;

	//�Ѿ�
	int bullet_speed = 20;
	int bullet_idx = 0;

	struct Bullet bullet [BULLET_NUM];
	for (int i = 0; i < BULLET_NUM; i++) {
		bullet[i].sprite.setSize(Vector2f(10, 10));
		bullet[i].sprite.setPosition(player.x + 50, player.y + 15);            //�ӽ� �׽�Ʈ
		bullet[i].is_fired = 0;
	}
	
	

	// ��(enemy)
	struct Enemy enemy[ENEMY_NUM];

	// enemy �ʱ�ȭ
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		// TODO : ������ ��ȿ������ �ڵ��̹Ƿ� ���߿� refactoring
		enemy[i].explosion_buffer.loadFromFile("./resources/sound/rumble.flac");
		enemy[i].explosion_sound.setBuffer(enemy[i].explosion_buffer);
		enemy[i].score = 100;
		enemy[i].respawn_time = 8;

		enemy[i].sprite.setTexture(&t.enemy);
		enemy[i].sprite.setSize(Vector2f(70, 70));
		enemy[i].sprite.setScale(-1, 1);
		enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
		enemy[i].life = 1;
		enemy[i].speed = -(rand() % 10 + 1);
	}


	// ������ �������� ������ �ݺ�
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// ����(x) ��ư�� ������ Event::Closed(0)
			case Event::Closed:
				window.close();		// ������ �ݴ´�
				break;
				// Ű���带 ������ ��(���� �������� ����)
			case Event::KeyPressed:
			{
				// �����̽� Ű ������ ��� enemy �ٽ� ����
				/*if (event.key.code == Keyboard::Space)
				{
					for (int i = 0; i < ENEMY_NUM; i++)
					{
						enemy[i].sprite.setSize(Vector2f(70, 70));
						enemy[i].sprite.setFillColor(Color::Yellow);
						enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
						enemy[i].life = 1;
						enemy[i].speed = -(rand() % 10 + 1);
					}
				}*/
				break;
			}

			}
		}

		spent_time = clock() - start_time;
		player.x = player.sprite.getPosition().x;
		player.y = player.sprite.getPosition().y;


		//play ������Ʈ
		// ����Ű start
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			player.sprite.move(-player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.move(player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.sprite.move(0, -player.speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.sprite.move(0, player.speed);
		}	// ����Ű end


		//player�̵����� ����
		//TODO : ������ �Ʒ��� ������ �ǵ���� ��ġ��
		if (player.x < 0)
			player.sprite.setPosition(0, player.y);
		else if (player.x > W_WIDTH-110)
			player.sprite.setPosition(W_WIDTH-110, player.y);

		if (player.y < 0)
			player.sprite.setPosition(player.x, 0);
		else if (player.y > W_HEIGHT-158)
			player.sprite.setPosition(player.x, W_HEIGHT-158);
		
		


		//�Ѿ˹߻�
		printf("bullet_idx %d\n", bullet_idx);
		if (Keyboard::isKeyPressed(Keyboard::Space)) {
			//�Ѿ��� �߻�Ǿ����� �ʴٸ�
			if (!bullet[bullet_idx].is_fired) {
				bullet[bullet_idx].sprite.setPosition(player.x + 50, player.y + 15);
				bullet[bullet_idx].is_fired = 1;
				bullet_idx++;    //���� �Ѿ��� �߻��� �� �ֵ���
			}
			
		}
		for (int i = 0; i < BULLET_NUM; i++) {
			//�Ѿ��� ��� �ѹ� �߻�Ǵ� ���׸� �����ϱ�
			if (bullet[i].is_fired) {
				bullet[i].sprite.move(bullet_speed, 0);
				if (bullet[i].sprite.getPosition().x > W_WIDTH)
					bullet[i].is_fired = 0;
			}
		}

		for (int i = 0; i < ENEMY_NUM; i++)
		{
			// 10�ʸ��� enemy�� ��
			if (spent_time % (1000 * enemy[i].respawn_time) < 1000 / 60 + 1)
			{
				enemy[i].sprite.setSize(Vector2f(70, 70));

				enemy[i].sprite.setPosition(rand() % 300 + W_WIDTH * 0.9, rand() % 380);
				enemy[i].life = 1;
				// 10�ʸ��� enemy�� �ӵ�+1
				enemy[i].speed = -(rand() % 10 + 1 + (spent_time / 1000 / enemy[i].respawn_time));
			}

			if (enemy[i].life > 0)
			{
				//player, enemy���� �浹
				if (is_collide(player.sprite,enemy[i].sprite))
				{
					
					enemy[i].life -= 1;
					player.score += enemy[i].score;

					// TODO : �ڵ� refactoring �ʿ�
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
				}
				// ���� ���� ���� �����Ϸ��� ����
				else if (enemy[i].sprite.getPosition().x < 0)
				{
					player.life -= 1;
					enemy[i].life = 0;
				}

				//�Ѿ˰� enemy�� �浹
				for (int j = 0; j < BULLET_NUM; j++) {
					if (is_collide(bullet[j].sprite, enemy[i].sprite))
					{
						if (bullet[j].is_fired) {
							enemy[i].life -= 1;
							player.score += enemy[i].score;

							// TODO : �ڵ� refactoring �ʿ�
							if (enemy[i].life == 0)
							{
								enemy[i].explosion_sound.play();
							}
							bullet[j].is_fired = 0;
						}
						enemy[i].sprite.move(enemy[i].speed, 0);
					}
				}
			}
						}
						
				

		

		//���ӻ��� ������Ʈ
		if (player.life <= 0)
		{
			is_gameover = 1;
		}


		sprintf(info, "life:%d score:%d time:%d"
			, player.life, player.score, spent_time / 1000);
		text.setString(info);

		window.clear(Color::Black);
		window.draw(bg_sprite);

		// draw�� ���߿� ȣ���Ҽ��� �켱������ ������
		for (int i = 0; i < ENEMY_NUM; i++)
			if (enemy[i].life > 0)
				window.draw(enemy[i].sprite);
		window.draw(player.sprite);
		window.draw(text);
		for (int i = 0; i < BULLET_NUM; i++) {
			if (bullet[i].is_fired)
				window.draw(bullet[i].sprite);
		}
		

		if (is_gameover)
		{
			window.draw(gameover_sprite);
			// TODO : ������ ���ߴ� ���� ������ ��
		}

		window.display();
	}

	return 0;
}