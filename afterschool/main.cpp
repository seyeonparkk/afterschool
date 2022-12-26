#include <stdio.h>
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {

    //640 x 480 윈도우 화면 나옴
    //잠깐 떴다가 사라지는 건 return 0때문에 프로그램이 종료된 것
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);

    //네모 모양의 플레이어
    RectangleShape player;
    player.setSize(Vector2f(40, 40));//플레이어 네모 크기
    player.setPosition(100, 100);//플레이어 기본 x, y좌표
    player.setFillColor(Color::Red);//빨간색 네모
    int player_speed = 5;
    
    RectangleShape enemy;
    enemy.setSize(Vector2f(70, 70));
    enemy.setPosition(500, 300);
    enemy.setFillColor(Color::Yellow);


    //유지 시키는 방법은? -> 무한 반복
    while (window.isOpen()) //윈도우창이 열려있는 동안 계속 반복
    {
        Event event;//이벤트 생성
        while (window.pollEvent(event)) //이벤트가 발생. 이벤트가 발생해야 event 초기화가 됨
        {
            switch (event.type)
            {
                //종료(x)버튼을 누르면 Event::Closed(0) 
            case Event::Closed://정수임
                window.close();//윈도우창이 닫힘
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

        if (player.getGlobalBounds().intersects(enemy.getGlobalBounds())) {
            printf("적과 충돌 \n");
        }
        //화면이 열려져 있는 동안 계속 그려야 함
        window.clear(Color::Black);
        //draw 나중에 호출할수록 우선순위가 높아짐
        window.draw(player);//player 보여주기(그려주기)
        window.draw(enemy);
        window.display();
    }

    return 0;
}