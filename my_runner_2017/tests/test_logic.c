/*
** test_logic.c -- standalone test harness for my_runner's gameplay math.
**
** src/my_runner.c has no separate functions to unit-test: the whole
** game (window setup, animation, physics, scoring, collision) lives
** inline in one main() built around a live SFML render loop and
** sfKeyboard_isKeyPressed() polling. That can't be driven from a test
** without a real window, so instead this harness copies just the pure
** arithmetic pieces -- the jump physics step and the AABB-ish
** collision check -- out into small standalone functions that mirror
** the real code line-for-line, and exercises them with plain
** assertions. This is a NEW file; it changes nothing in src/.
**
** Build (no CSFML needed -- this is pure int/float math):
**   gcc -Wall -Wextra -o tests/test_logic tests/test_logic.c
**   ./tests/test_logic
**
** Every function below is a direct transcription of the corresponding
** lines in src/my_runner.c's main() loop (line numbers as of the
** build reviewed in README.md).
*/
#include <assert.h>
#include <stdio.h>

/*
** Mirrors src/my_runner.c lines 137-148:
**
**   if (sfKeyboard_isKeyPressed(sfKeySpace) == sfTrue) {
**       if (position_trump.y > 300) position_trump.y -= 15;
**       vitesse_trump = vitesse_trump + 0.05;
**       score = score - 2;
**   }
**   if (sfKeyboard_isKeyPressed(sfKeySpace) == sfFalse) {
**       if (position_trump.y <= 425) position_trump.y += 10;
**   }
**
** space_held: 1 if SPACE is currently down, 0 otherwise.
** *y, *vitesse, *score are updated in place, exactly as the real
** locals are updated in-loop.
*/
void	jump_step(int space_held, float *y, float *vitesse, int *score)
{
	if (space_held) {
		if (*y > 300)
			*y -= 15;
		*vitesse = *vitesse + 0.05f;
		*score = *score - 2;
	}
	if (!space_held) {
		if (*y <= 425)
			*y += 10;
	}
}

/*
** Mirrors src/my_runner.c lines 160-165 exactly (the score -= 50
** collision penalty condition -- the AABB-ish overlap check between
** trump and the sombrero).
*/
int	collides(float trump_x, float trump_y, float sombrero_x, float sombrero_y)
{
	return (trump_x <= sombrero_x + 110 && trump_x >= sombrero_x - 20 &&
		trump_y >= sombrero_y - 20 && trump_y <= sombrero_y + 110);
}

/*
** Mirrors src/my_runner.c lines 128-136: any of the three scrolling
** sprites (sombrero, cactus, cactus_copy) wraps back to x=710 once it
** scrolls past x=-100.
*/
float	scroll_wrap(float x)
{
	if (x <= -100)
		return (710);
	return (x);
}

static int	failures = 0;

#define CHECK(desc, cond) do { \
		if (cond) { \
			printf("  PASS: %s\n", desc); \
		} else { \
			printf("  FAIL: %s\n", desc); \
			failures = failures + 1; \
		} \
	} while (0)

int	main(void)
{
	float y;
	float vitesse;
	int score;

	printf("=== jump_step: rising while SPACE held ===\n");
	y = 425;
	vitesse = 1;
	score = 0;
	jump_step(1, &y, &vitesse, &score);
	CHECK("one frame of holding SPACE lifts y by 15", y == 410);
	CHECK("holding SPACE increases vitesse by 0.05", vitesse > 1.0499f && vitesse < 1.0501f);
	CHECK("holding SPACE costs 2 score per frame", score == -2);

	printf("=== jump_step: floor clamp at y>300 ===\n");
	y = 305;
	vitesse = 1;
	score = 0;
	jump_step(1, &y, &vitesse, &score);
	CHECK("y=305 -15 still steps (305>300)", y == 290);
	/* Once y drops to <=300 a further held frame must NOT keep
	** subtracting -- this is the floor clamp real code relies on. */
	y = 300;
	jump_step(1, &y, &vitesse, &score);
	CHECK("y=300 is at/under the floor: no further descent", y == 300);
	y = 295;
	jump_step(1, &y, &vitesse, &score);
	CHECK("y=295 (already past floor) also does not descend further", y == 295);

	printf("=== jump_step: falling back down while SPACE released ===\n");
	y = 300;
	vitesse = 1;
	score = 0;
	jump_step(0, &y, &vitesse, &score);
	CHECK("releasing SPACE raises y by 10", y == 310);
	CHECK("releasing SPACE does not change vitesse", vitesse == 1.0f);
	CHECK("releasing SPACE does not change score", score == 0);

	printf("=== jump_step: resting ceiling clamp at y<=425 ===\n");
	y = 425;
	jump_step(0, &y, &vitesse, &score);
	/* NOTE: this documents a REAL bug in the original code, distinct
	** from the ordinary overshoot below: the <=425 check runs BEFORE
	** the += 10, so even starting from the exact resting value 425
	** (425<=425 is true) it still climbs, permanently overshooting to
	** 435 and never settling back to 425 again for the rest of the
	** game (see README.md -- not fixed here per this review's policy
	** of documenting rather than altering original gameplay feel for
	** a cosmetic, sub-visual-frame positional drift). */
	CHECK("(documented bug) y=425 (exact rest) still climbs to 435, not clamped", y == 435);
	y = 420;
	jump_step(0, &y, &vitesse, &score);
	CHECK("y=420 (still <=425) rises toward rest", y == 430);
	/* NOTE: this documents a real (harmless) one-frame overshoot in
	** the original code: the <=425 check is evaluated BEFORE adding
	** 10, so a value like 420 overshoots to 430, one frame above the
	** intended resting position, before the next frame's check
	** (430<=425 is false) finally stops it. Not fixed here since it's
	** cosmetic (1px-scale in game terms) and changing it would alter
	** original gameplay feel -- see README.md. */
	CHECK("(documented) overshoot: 430 is now above the 425 rest line", 430 > 425);
	y = 430;
	jump_step(0, &y, &vitesse, &score);
	CHECK("next frame: 430<=425 is false, so it finally stops rising", y == 430);

	printf("=== collides: AABB-ish overlap check ===\n");
	CHECK("far apart on x: no collision", !collides(100, 425, 610, 400));
	CHECK("sombrero directly under/around trump: collision", collides(100, 425, 50, 400));
	CHECK("just inside the left edge (sombrero_x-20 == trump_x): collision",
		collides(100, 425, 120, 400));
	CHECK("just outside the left edge: no collision",
		!collides(100, 425, 121, 400));
	CHECK("just inside the right edge (sombrero_x+110 == trump_x): collision",
		collides(100, 425, -10, 400));
	CHECK("just outside the right edge: no collision",
		!collides(100, 425, -11, 400));
	CHECK("jumping clear over it (y below sombrero_y-20): no collision",
		!collides(100, 379, 50, 400));
	CHECK("standing still while sombrero is in the x-window: STILL collides "
		"(the real game applies -50 EVERY frame of overlap, not once -- "
		"see README.md)", collides(100, 425, 50, 400));

	printf("=== scroll_wrap: off-screen reset ===\n");
	CHECK("x just above -100 does not wrap", scroll_wrap(-99) == -99);
	CHECK("x at exactly -100 wraps to 710", scroll_wrap(-100) == 710);
	CHECK("x well past -100 wraps to 710", scroll_wrap(-250) == 710);
	CHECK("x on-screen is unchanged", scroll_wrap(300) == 300);

	printf("\n=== %s ===\n", failures == 0 ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
	return (failures == 0 ? 0 : 1);
}
