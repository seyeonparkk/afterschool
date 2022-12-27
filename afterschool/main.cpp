#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//SoundBuffer 사용

using namespace sf;

int main(void) {

    srand(time(NULL));//랜덤 함수 사용

    //640 x 480 윈도우 화면 나옴
    //잠깐 떴다가 사라지는 건 return 0때문에 프로그램이 종료된 것
    RenderWindow window(VideoMode(640, 480), "AfterSchool");
    window.setFramerateLimit(60);//1초에 60장 보여준다. 플레이어가 빨리 가지 않도록 하기


    long start_time = clock();// 게임 시작 시간
    long spent_time;// 게임 진행 시간

    // text 폰트
    Font font;
    font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");//C드라이브에 있는 폰트 가져오기

    Text text;
    char info[40];
    text.setFont(font);//폰트 세팅
    text.setCharacterSize(24);//폰트 크기
    text.setFillColor(Color(255, 255, 255));//RGB로 흰색 표현
    text.setPosition(0, 0);//텍스트 위치 0,0

    //배경
    Texture bg_texture;
    bg_texture.loadFromFile("./resources/images/1.jpg");
    Sprite bg_sprite;
    bg_sprite.setTexture(bg_texture);
    bg_sprite.setPosition(0, 0);

    // 플레이어
    RectangleShape player;
    player.setSize(Vector2f(40, 40));//플레이어 사이즈
    player.setPosition(100, 100);//플레이어 시작 위치
    player.setFillColor(Color::Red);//플레이어 색상
    int player_speed = 7;//플레이어 속도
    int player_score = 0;//플레이어 점수


    // enemy
    const int ENEMY_NUM = 12;
    RectangleShape enemy[ENEMY_NUM];//적
    int enemy_life[ENEMY_NUM];//적의 체력
    int enemy_speed[ENEMY_NUM];
    int enemy_score = 100;//적을 잡을 때마다 얻는 점수
    SoundBuffer enemy_explosion_buffer;
    enemy_explosion_buffer.loadFromFile("./resources/sound/rumble.flac");
    Sound enemy_explosion_sound;//소리에 대한 정보를 담음
    enemy_explosion_sound.setBuffer(enemy_explosion_buffer);

    for (int i = 0; i < ENEMY_NUM; i++)
    {
        enemy[i].setSize(Vector2f(70, 70));
        enemy[i].setPosition(rand() % 300 + 300, rand() % 410);
        enemy_life[i] = 1;
        enemy[i].setFillColor(Color::Yellow);//적 색상
        enemy_speed[i] = -(rand() % 10 + 1);
    }


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
                break;
                //키보드를 눌렀을 때 
            case Event::KeyPressed:
                //case문 안에 변수를 선언할 때에는 중괄호를 쳐야 함
            {
                //space키 누르면 모든 enemy 다시 출현
                if (event.key.code == Keyboard::Space)
                {
                    for (int i = 0; i < ENEMY_NUM; i++)
                    {
                        enemy[i].setSize(Vector2f(70, 70));
                        enemy[i].setPosition(rand() % 300 + 300, rand() % 410);
                        enemy_life[i] = 1;
                        enemy[i].setFillColor(Color::Yellow);//적 색상
                    }
                }
                break;
            }
            }
        }

        spent_time = clock() - start_time;// 시간이 지남에 따라 증가

        //방향키
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            player.move(-1 * player_speed, 0);//왼쪽 이동
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            player.move(0, -1 * player_speed);//위쪽 이동
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            player.move(0, player_speed);//아래쪽 이동
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            player.move(player_speed, 0);//오른쪽 이동
        }

        //enemy와의 충돌
        //intersects : 플레이어와 적 사이에서 교집합이 있는가
        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (enemy_life[i] > 0)
            {
                // enemy와의 충돌
                if (player.getGlobalBounds().intersects(enemy[i].getGlobalBounds()))
                {
                    printf("enemy[%d]와의 충돌\n", i);
                    enemy_life[i] -= 1;//적의 생명 줄이기
                    player_score += enemy_score;

                    // TODO : 코드 refactoring 필요
                    if (enemy_life[i] == 0)
                    {
                        enemy_explosion_sound.play();
                    }
                }

                enemy[i].move(enemy_speed[i], 0);
            }

        }

        // 시작 시간은 변하지 않음
        sprintf(info, "score: %d time: %d\n", player_score, spent_time / 1000);
        text.setString(info);

        window.clear(Color::Black);//플레이어 자체 제거 (배경 지우기)
        window.draw(bg_sprite);

        for (int i = 0; i < ENEMY_NUM; i++)
        {
            if (enemy_life[i] > 0)  window.draw(enemy[i]);//적 보여주기
        }
        //화면이 열려져 있는 동안 계속 그려야 함
        //draw는 나중에 호출할수록 우선순위가 높아짐
        window.draw(player);//플레이어 보여주기(그려주기)
        window.draw(text);

        window.display();
    }

    return 0;
}