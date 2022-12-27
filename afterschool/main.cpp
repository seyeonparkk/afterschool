#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//SoundBuffer ���

using namespace sf;

int main(void) {

    srand(time(NULL));//���� �Լ� ���

    //640 x 480 ������ ȭ�� ����
    //��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);//1�ʿ� 60�� �����ش�. �÷��̾ ���� ���� �ʵ��� �ϱ�


    long start_time = clock();// ���� ���� �ð�
    long spent_time;// ���� ���� �ð�

    // text ��Ʈ
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");//C����̺꿡 �ִ� ��Ʈ ��������

    Text text;
    char info[40];
    text.setFont(font);//��Ʈ ����
    text.setCharacterSize(24);//��Ʈ ũ��
    text.setFillColor(Color(255, 255, 255));//RGB�� ��� ǥ��
    text.setPosition(0, 0);//�ؽ�Ʈ ��ġ 0,0

    //���
    Texture bg_texture;
    bg_texture.loadFromFile("./resources/images/1.jpg");
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setPosition(0, 0);

    // �÷��̾�
    RectangleShape player;
    player.setSize(Vector2f(40, 40));//�÷��̾� ������
    player.setPosition(100, 100);//�÷��̾� ���� ��ġ
    player.setFillColor(Color::Red);//�÷��̾� ����
    int player_speed = 7;//�÷��̾� �ӵ�
    int player_score = 0;//�÷��̾� ����


    // enemy
    const int ENEMY_NUM = 12;
    RectangleShape enemy[ENEMY_NUM];//��
    int enemy_life[ENEMY_NUM];//���� ü��
    int enemy_speed[ENEMY_NUM];
    int enemy_score = 100;//���� ���� ������ ��� ����
    SoundBuffer enemy_explosion_buffer;
    enemy_explosion_buffer.loadFromFile("./resources/sound/rumble.flac");
    Sound enemy_explosion_sound;//�Ҹ��� ���� ������ ����
    enemy_explosion_sound.setBuffer(enemy_explosion_buffer);

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].setSize(Vector2f(70, 70));
        enemy[i].setPosition(rand() % 300 + 300, rand() % 410);
        enemy_life[i] = 1;
        enemy[i].setFillColor(Color::Yellow);//�� ����
        enemy_speed[i] = -(rand() % 10 + 1);
    }


    //���� ��Ű�� �����? -> ���� �ݺ�
    while (window.isOpen()) //������â�� �����ִ� ���� ��� �ݺ�
    {
        Event event;//�̺�Ʈ ����
        while (window.pollEvent(event)) //�̺�Ʈ�� �߻�. �̺�Ʈ�� �߻��ؾ� event �ʱ�ȭ�� ��
        {
            switch (event.type)
            {
                //����(x)��ư�� ������ Event::Closed(0) 
            case Event::Closed://������
                window.close();//������â�� ����
                break;
                //Ű���带 ������ �� 
            case Event::KeyPressed:
                //case�� �ȿ� ������ ������ ������ �߰�ȣ�� �ľ� ��
            {
                //spaceŰ ������ ��� enemy �ٽ� ����
                if (event.key.code == Keyboard::Space)
                {
                    for (int i = 0; i < ENEMY_NUM; i++)
                    {
                        enemy[i].setSize(Vector2f(70, 70));
                        enemy[i].setPosition(rand() % 300 + 300, rand() % 410);
                        enemy_life[i] = 1;
                        enemy[i].setFillColor(Color::Yellow);//�� ����
                    }
                }
                break;
            }
            }
        }

        spent_time = clock() - start_time;// �ð��� ������ ���� ����

        //����Ű
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player.move(-1 * player_speed, 0);//���� �̵�
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player.move(0, -1 * player_speed);//���� �̵�
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player.move(0, player_speed);//�Ʒ��� �̵�
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player.move(player_speed, 0);//������ �̵�
        }

        //enemy���� �浹
        //intersects : �÷��̾�� �� ���̿��� �������� �ִ°�
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (enemy_life[i] > 0)
            {
                // enemy���� �浹
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
                {
                    printf("enemy[%d]���� �浹\n", i);
                    enemy_life[i] -= 1;//���� ���� ���̱�
                    player_score += enemy_score;

                    // TODO : �ڵ� refactoring �ʿ�
                    if (enemy_life[i] == 0)
                    {
                        enemy_explosion_sound.play();
                    }
                }

                enemy[i].move(enemy_speed[i], 0);
            }

        }

        // ���� �ð��� ������ ����
        sprintf(info, "score: %d time: %d\n", player_score, spent_time / 1000);
        text.setString(info);

        window.clear(Color::Black);//�÷��̾� ��ü ���� (��� �����)
        window.draw(bg_sprite);

        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (enemy_life[i] > 0)  window.draw(enemy[i]);//�� �����ֱ�
        }
        //ȭ���� ������ �ִ� ���� ��� �׷��� ��
        //draw�� ���߿� ȣ���Ҽ��� �켱������ ������
        window.draw(player);//�÷��̾� �����ֱ�(�׷��ֱ�)
        window.draw(text);

        window.display();
    }

    return 0;
}