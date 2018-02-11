/*
** EPITECH PROJECT, 2017
** My Hunter
** File description:
** Yup
*/

#include "../include/my.h"
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av)
{
	sfVideoMode mode = {800, 600, 32};
	sfRenderWindow *window;
	sfTexture *trump;
	sfTexture *sombrero;
	sfTexture *texture;
	sfTexture *cactus;
	sfTexture *cactus_copy;
	sfSprite *sprite;
	sfSprite *sprite_trump;
	sfSprite *sprite_cactus;
	sfSprite *sprite_cactus_copy;
	sfSprite *sprite_sombrero;
	sfIntRect rect_trump;
	sfIntRect rect_sombrero;
	sfMusic *ugandan_cluk;
	sfMusic *do_you_know_da_wae;
	sfClock *clock;
	sfTime time;
	sfEvent event;
	sfVector2f position_trump;
	sfVector2f position_cactus;
	sfVector2f position_cactus_copy;
	sfVector2f position_sombrero;
	float seconds;
	float vitesse_trump = 1;
	int i = 0;
	int j = 0;
	int score = 0;
	int index = 0;
	int timer = 0;
	int timerz = 0;

	my_printf("\n");
	while (index < ac) {
		if (av[index][0] == '-') {
			if (av[index][1] == 'h') {
				my_printf("\n\nInfinite runner created with CSFML.\n\nUSAGE\n\t./my_runner\n\n\nOPTIONS\n\t-h\t\t\tprints the game man and then launch the game\n\n\nUSER INTERACTIONS\n\tSPACE KEY\t\tjump.\n\n\n");
			}
		}
		index = index + 1;
	}
	index = 0;
	window = sfRenderWindow_create(mode, "My Runner", sfResize | sfClose, NULL);
	texture = sfTexture_createFromFile("assets/background.png", NULL);
	cactus = sfTexture_createFromFile("assets/cactus.png", NULL);
	cactus_copy = sfTexture_createFromFile("assets/cactus.png", NULL);
	trump = sfTexture_createFromFile("assets/trump_run.png", NULL);
	sombrero = sfTexture_createFromFile("assets/sombrero.png", NULL);
	ugandan_cluk = sfMusic_createFromFile("assets/ugandan_cluk.ogg");
	do_you_know_da_wae = sfMusic_createFromFile("assets/do_you_know_da_wae.ogg");
	if (!window || !texture || !cactus || !cactus_copy || !trump ||
		!sombrero || !ugandan_cluk || !do_you_know_da_wae) {
		return (0);
	}
	sprite = sfSprite_create();
	sprite_trump = sfSprite_create();
	sprite_cactus = sfSprite_create();
	sprite_cactus_copy = sfSprite_create();
	sprite_sombrero = sfSprite_create();
	clock = sfClock_create();
	position_trump.x = 100;
	position_trump.y = 425;
	position_cactus.x = 610;
	position_cactus.y = 290;
	position_cactus_copy.x = 1010;
	position_cactus_copy.y = 290;
	position_sombrero.x = 610;
	position_sombrero.y = 400;
	rect_trump.top = 110;
	rect_trump.left = 0;
	rect_trump.width = 110;
	rect_trump.height = 100;
	rect_sombrero.top = 0;
	rect_sombrero.left = 0;
	rect_sombrero.width = 110;
	rect_sombrero.height = 110;
	sfSprite_setTexture(sprite, texture, sfTrue);
	sfSprite_setTexture(sprite_cactus, cactus, sfTrue);
	sfSprite_setTexture(sprite_cactus_copy, cactus_copy, sfTrue);
	sfSprite_setTexture(sprite_trump, trump, sfTrue);
	sfSprite_setTexture(sprite_sombrero, sombrero, sfTrue);
	sfMusic_setLoop(ugandan_cluk, sfTrue);
	sfMusic_setLoop(do_you_know_da_wae, sfTrue);
	sfRenderWindow_setFramerateLimit(window, 30);
	sfRenderWindow_setMouseCursorVisible(window, sfFalse);
	sfMusic_play(ugandan_cluk);
	sfMusic_play(do_you_know_da_wae);
	while (sfRenderWindow_isOpen(window)) {
		time = sfClock_getElapsedTime(clock);
		seconds = time.microseconds / 1000000.0;
		position_cactus.x = position_cactus.x - vitesse_trump * 2;
		position_cactus_copy.x = position_cactus_copy.x - vitesse_trump * 2;
		position_sombrero.x = position_sombrero.x - (vitesse_trump * 1.5);
		if (seconds > 0.2) {
			i = i + 1;
			j = j + 1;
			rect_trump.left = rect_trump.left + 100;
			rect_sombrero.left = rect_sombrero.left + 110;
			if (i == 3) {
				rect_trump.left = 0;
				i = 0;
			}
			if (j == 2) {
				rect_sombrero.left = 0;
				j = 0;
			}
			sfSprite_setTextureRect(sprite_trump, rect_trump);
			sfSprite_setTextureRect(sprite_sombrero, rect_sombrero);
			sfClock_restart(clock);
		}
		if (position_sombrero.x <= -100) {
			position_sombrero.x = 710;
		}
		if (position_cactus.x <= -100) {
			position_cactus.x = 710;
		}
		if (position_cactus_copy.x <= -100) {
			position_cactus_copy.x = 710;
		}
		if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue) {
			if (position_trump.y > 300) {
				position_trump.y -= 15;
			}
			vitesse_trump = vitesse_trump + 0.05;
			score = score - 2;
		}
		if (sfKeyboard_isKeyPressed(sfKeySpace) == sfFalse) {
			if (position_trump.y <= 425) {
				position_trump.y += 10;
			}
		}
		score = score + 1;
		index = index + 1;
		if (index == 10) {
			my_printf("\t\t\t\t\tScore : %d\n\n", score);
			index = 0;
		}
		timer = timer + 1;
		if (timer == 30) {
			timerz = timerz + 1;
			timer = 0;
		}
		if ((position_trump.x <= position_sombrero.x + 110 &&
			position_trump.x >= position_sombrero.x - 20) && 
			(position_trump.y >= position_sombrero.y - 20 &&
		 	position_trump.y <= position_sombrero.y + 110)) {
			score = score - 50;
		}
		while (sfRenderWindow_pollEvent(window, &event)) {
			if (event.type == sfEvtClosed ||
			 sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue ||
			 score < 0) {
				sfMusic_stop(ugandan_cluk);
				sfMusic_stop(do_you_know_da_wae);
				sfRenderWindow_close(window);
				my_printf("\t\t\t\t\tGAME OVER\n");
			}
		}
		sfSprite_setPosition(sprite_trump, position_trump);
		sfSprite_setPosition(sprite_cactus, position_cactus);
		sfSprite_setPosition(sprite_cactus_copy, position_cactus_copy);
		sfSprite_setPosition(sprite_sombrero, position_sombrero);
		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_drawSprite(window, sprite, NULL);
		sfRenderWindow_drawSprite(window, sprite_cactus, NULL);
		sfRenderWindow_drawSprite(window, sprite_cactus_copy, NULL);
		sfRenderWindow_drawSprite(window, sprite_trump, NULL);
		sfRenderWindow_drawSprite(window, sprite_sombrero, NULL);
		sfRenderWindow_display(window);
	}
	my_printf("\t\t\t\t\tFinal score : %d\n\t\t\t\t\tdone in %d seconds.\n\n", score, timerz);
	sfSprite_destroy(sprite);
	sfMusic_destroy(ugandan_cluk);
	sfMusic_destroy(do_you_know_da_wae);
	sfRenderWindow_destroy(window);
	return (0);
}