#include<stdio.h>
#include<SFML/Graphics.hpp>

using namespace sf;
int main(void) {
	RenderWindow window(VideoMode(640, 480), "afterschool");      //윈도우창 생성

	//윈도우가 열려있을때까지 반복
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)      //닫는 버튼을 누르면 윈도우를 닫는다
				window.close();     //윈도우 닫는다
		}
	}
		
	return 0;
}