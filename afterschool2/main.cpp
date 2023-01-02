#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace sf;

const int S = 4;
const int CARD_W = 200;
const int CARD_H = 200;

struct Card {
	RectangleShape sprite;
	int id_i;
	int id_j;
	int type;
	int is_clicked;		// 현재 뒤집혀진 카드인지
	int is_cleared;		// 정답을 맞춘 카드인지
};

void swap_card(struct Card* c1, struct Card* c2)
{
	struct Card temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

int main(void)
{
	RenderWindow window(VideoMode(1200, 800), "AfterSchool2");
	window.setFramerateLimit(60);

	Vector2i mouse_pos;
	int flipped_num = 0;		// 현재 뒤집혀진 카드의 갯수

	long start_time;
	long spent_time;
	long delay_time;			// 바로 다시 ?로 뒤집혀지지 않도록 딜레이를 줌

	srand(time(0));

	Texture t[8 + 1];
	t[0].loadFromFile("./resources/images/ch0.jpg");
	t[1].loadFromFile("./resources/images/ch1.jpg");
	t[2].loadFromFile("./resources/images/ch2.jpg");
	t[3].loadFromFile("./resources/images/ch3.jpg");
	t[4].loadFromFile("./resources/images/ch4.jpg");
	t[5].loadFromFile("./resources/images/ch5.jpg");
	t[6].loadFromFile("./resources/images/ch6.jpg");
	t[7].loadFromFile("./resources/images/ch7.jpg");
	t[8].loadFromFile("./resources/images/ch8.jpg");

	Font font;
	font.loadFromFile("c:/Windows/Fonts/arial.ttf");

	Text text;
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(Color::Red);
	text.setPosition(0, 0);
	char info[40];

	struct Card compare_card;	// 첫 번째로 뒤집힌 카드
	struct Card cards[S][S];
	int n = 0;
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			cards[i][j].sprite.setSize(Vector2f(CARD_W, CARD_H));
			cards[i][j].sprite.setTexture(&t[0]);
			cards[i][j].type = 1 + n / 2;
			cards[i][j].is_clicked = 0;
			cards[i][j].is_cleared = 0;
			n++;
		}
	}

	// 카드 100번 섞기
	for (int i = 0; i < 100; i++)
	{
		swap_card(&(cards[rand() % S][rand() % S]), &(cards[rand() % S][rand() % S]));
	}

	// idx에 맞춰서 id값, 위치 조정
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < S; j++)
		{
			cards[i][j].id_i = i;
			cards[i][j].id_j = j;
			cards[i][j].sprite.setPosition(j * CARD_W, i * CARD_H);
		}
	}


	start_time = clock();
	delay_time = start_time;

	while (window.isOpen())
	{
		mouse_pos = Mouse::getPosition(window);
		spent_time = clock() - start_time;

		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window.close();
				break;
				// 한 번 누르면 한 번만 적용
				// TODO : 버튼 눌러도 적용 안되는 버그 해결하기
			case Event::MouseButtonPressed:
				if (event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < S; i++)
					{
						for (int j = 0; j < S; j++)
						{
							if (flipped_num < 2)
							{
								// 마우스 위치가 cards[i][j]의 위치에 해당한다면?
								if (cards[i][j].sprite.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
								{
									// 뒤집혀지지 않은 카드만 뒤집겠다.
									if (cards[i][j].is_clicked == 0)
									{
										cards[i][j].is_clicked = 1;
										flipped_num++;

										// 뒤집혀진 카드가 한 개라면
										if (flipped_num == 1)
										{
											compare_card = cards[i][j];
										}
										// 두 개를 뒤집었다면
										else if (flipped_num == 2)
										{
											// 두 카드가 같은 종류면
											if (compare_card.type == cards[i][j].type)
											{
												cards[i][j].is_cleared = 1;
												cards[compare_card.id_i][compare_card.id_j].is_cleared = 1;
											}
											// 두 카드가 다른 종류이면
											else
											{
												delay_time = spent_time;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < S; i++)
		{
			for (int j = 0; j < S; j++)
			{
				// 클릭이 된 상태이거나, 정답을 맞춘 카드이면
				if (cards[i][j].is_clicked == 1 || cards[i][j].is_cleared == 1)
					// 그림이 있는 스프라이트로 변경(카드를 뒤집겠다는 의미)
					cards[i][j].sprite.setTexture(&t[cards[i][j].type]);
				else
					// 카드는 ???상태
					cards[i][j].sprite.setTexture(&t[0]);
			}
		}

		// 뒤집힌 카드가 2개라면
		if (flipped_num == 2)
		{
			// 두 카드가 뒤집힌지 1초 이내라면
			if (spent_time - delay_time <= 1000)
			{
			}
			else
			{	// 다 ?상태로 만들어 버리겠다
				for (int i = 0; i < S; i++)
					for (int j = 0; j < S; j++)
						cards[i][j].is_clicked = 0;
				flipped_num = 0;
			}
		}


		sprintf(info, "%d \n", spent_time / 1000);
		text.setString(info);


		window.clear(Color::Black);
		for (int i = 0; i < S; i++)
		{
			for (int j = 0; j < S; j++)
			{
				window.draw(cards[i][j].sprite);
			}
		}

		window.draw(text);

		window.display();
	}
	return 0;
}