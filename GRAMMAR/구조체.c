#include<stdio.h>
struct per {
	int hp, speed;

};
void main() {
	struct per player;
	player.hp = 5;
	player.speed = 7;

	struct per enemy;
	int enemy_hp = 2;
	int enemy_speed = 5;
	printf("�÷��̾��� ü�� %d �÷��̾� �ӵ� %d\n", player.hp, player.speed);
}