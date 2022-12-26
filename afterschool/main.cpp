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
    int player_speed = -100;

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
            player.move(player_speed,0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Up)) {
            player.move(0, -player_speed);
        }
        if (Keyboard::isKeyPressed(Keyboard::Down)) {
            player.move(0, player_speed);
       }
        //ȭ���� ������ �ִ� ���� ��� �׷��� ��
        window.clear(Color::Black);
        window.draw(player);//player �����ֱ�(�׷��ֱ�)
        window.display();
    }

    return 0;
}