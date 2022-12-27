#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include<string.h>
#include<SFML/Audio.hpp>


using namespace sf;

int main(void) {
    //������ â ����
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);

    srand(time(0));
    
    long start_time = clock();
    long spent_time;



    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

    Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(Color(255, 255, 255));
    text.setPosition(0, 0);
    char info[40];
    text.setString("SCORE");

    //���
    Texture bg_texture;
    bg_texture.loadFromFile("./resources/images/1.jpg");
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setPosition(0, 0);



    //�÷��̾�
    //�簢�� â �׸���
    RectangleShape player;
    player.setSize(Vector2f(40, 40));
    player.setPosition(100, 100);
    window.draw(player);
    int player_score = 0;

    RectangleShape enemy[5];
    int enemy_life[5];
    int enemy_score = 100;      //���� ���� ������ 100���� ����
    SoundBuffer enemy_explosion_buffer;
    enemy_explosion_buffer.loadFromFile("./resources/sound/rumble.flac");
    Sound enemy_explosion_sound;
    enemy_explosion_sound.setBuffer(enemy_explosion_buffer);

    //enemy �ʱ�ȭ
    for (int i = 0; i < 5; i++) {
        enemy[i].setSize(Vector2f(70, 70));
        enemy[i].setFillColor(Color::Yellow);
        //���� �������� ������ �ȴ�. 
        enemy[i].setPosition(rand() % 300 + 300, rand() % 380);
        enemy_life[i] = 1;
    }

    //�簢�� ���� ����
    player.setFillColor(Color::Red);

    //�÷��̾� ���ǵ� 3���� �ʱ�ȭ
    int player_speed = 5;

    //�����찡 �������� �� ���� �ݺ�
    while (window.isOpen()) {

        Event event;
        while (window.pollEvent(event)) {

            //����(x)��ư�� ������  
            switch (event.type) {
            case Event::Closed:
                break;
            case Event::KeyPressed: {
                //space�� ������ �� �ѹ��� �����̵����ϱ�.
                if (event.key.code == Keyboard::Space) {
                    for (int i = 0; i < 5; i++) {
                        enemy[i].setSize(Vector2f(70, 70));
                        enemy[i].setFillColor(Color::Yellow);
                        //���� �������� ������ �ȴ�. 
                        enemy[i].setPosition(rand() % 300 + 300, rand() % 380);
                        enemy_life[i] = 1;
                    }
                }
            }
                                  break;
                                  window.close();
            }
        }
        spent_time = clock();

        //�÷��̾� ������ ����
        //else�� ���� ������ �߰����� ���� �� ���� ������ �پ���.(���õ��� ����)
        //����Ű start
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player.move(-player_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move(0, -player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(0, player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player.move(player_speed, 0);
        }//����Ű end



        //�浹 ó���� enemy�� ������� ���� �׸��ڴ�. 
        for (int i = 0; i < 5; i++) {
            if (enemy_life[i] > 0) {
                //������ �浹ó��
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
                    printf("enemy[%d]�� �浹\n", i);
                    enemy_life[i] -= 1;
                    player_score += enemy_score;
                 if (enemy_life[i] == 0) {
                     enemy_explosion_sound.play();
                }
                }
            }
   
        }


        sprintf(info,"SCORE : %d  TIME : %d", player_score,(spent_time-start_time)/1000);    //�ǽð����� ���� ����
        text.setString(info);

        //60�п� 1�ʸ��� �׷ȴ� �����ٸ� �ݺ��ϰ� �ȴ�. 
        window.clear(Color::Black);
        window.draw(bg_sprite);

        for (int i = 0; i < 5; i++)
            if (enemy_life[i] > 0)
                window.draw(enemy[i]);

        //draw�� ���߿� ȣ���� ���� �켱������ ��������. 


        window.draw(player);
        window.draw(text);

        window.display();
    }
    return 0;
}