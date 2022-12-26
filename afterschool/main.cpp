#include <stdio.h>
#include <SFML/Graphics.hpp>
#include<time.h>
#include<stdlib.h>

using namespace sf;

int main(void) {

    //640 x 480 ������ ȭ�� ����
    //��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);

    srand(time(0));


    //�׸� ����� �÷��̾�
    RectangleShape player;
    player.setSize(Vector2f(40, 40));//�÷��̾� �׸� ũ��
    player.setPosition(100, 100);//�÷��̾� �⺻ x, y��ǥ
    player.setFillColor(Color::Red);//������ �׸�
    int player_speed = 5;
    
    RectangleShape enemy[5];
    int enemy_life  [5];

    for (int i = 0; i < 5; i++) {
        enemy[i].setSize(Vector2f(70, 70));
        enemy[i].setFillColor(Color::Yellow);
        enemy_life[i] = 1;
        enemy[i].setPosition(rand()%300+300, rand()%380);
    
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
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            player.move(-player_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            player.move(player_speed, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move(0, -player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(0, player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            for (int i = 0; i < 5; i++) {
                enemy[i].setSize(Vector2f(70, 70));
                enemy[i].setFillColor(Color::Yellow);
                enemy_life[i] = 1;
                enemy[i].setPosition(rand() % 300 + 300, rand() % 380);
            }
        }



        //enemy�浹
        for (int i = 0; i < 5; i++) {
            if (enemy_life[i] > 0) {
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds())) {
                    printf("���� �浹 \n");
                    enemy_life[i] -= 1;
                }
            }
        }
        
        //ȭ���� ������ �ִ� ���� ��� �׷��� ��
        window.clear(Color::Black);
        //draw ���߿� ȣ���Ҽ��� �켱������ ������
        for (int i = 0; i < 5; i++) {
            if (enemy_life[i] > 0)
                window.draw(enemy[i]);
            window.draw(player);//player �����ֱ�(�׷��ֱ�)

            window.display();
        }
        }
    

    return 0;
}