#include<stdio.h>
#include<SFML/Graphics.hpp>

using namespace sf;
int main(void) {
	RenderWindow window(VideoMode(640, 480), "afterschool");      //������â ����

	//�����찡 �������������� �ݺ�
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)      //�ݴ� ��ư�� ������ �����츦 �ݴ´�
				window.close();     //������ �ݴ´�
		}
	}
		
	return 0;
}