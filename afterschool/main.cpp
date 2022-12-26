#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

    //640 x 480 ������ ȭ�� ����
    //��� ���ٰ� ������� �� return 0������ ���α׷��� ����� ��
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);

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
        enemy[i].setPosition(500, 100*i);
        enemy_life[i] = 1;
        enemy[i].setFillColor(Color::Yellow);
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