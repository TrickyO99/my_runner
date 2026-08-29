# my_runner

An endless-runner / obstacle-dodging game written in C on top of CSFML
("Donald Trump jumping on ugandan knuckles", per the original commit
message). You control a running sprite that must jump (SPACE) over a
scrolling sombrero obstacle while cactus sprites scroll by in the
background; your score climbs automatically over time, drops while you're
airborne, and drops sharply on a sombrero collision — the game ends when the
window is closed, Escape is pressed, or the score goes negative. This is the
Epitech school project `my_runner_2017`.

## Build

The project lives in the `my_runner_2017/` subfolder and ships a Makefile:

```sh
cd my_runner_2017
mingw32-make
```

### Windows build notes — FIXED, builds and runs

The Makefile originally had two bugs preventing a Windows build:

1. `SRC = src/*.c` was never wrapped in `$(wildcard ...)`, so Make treated it
   as one literal filename instead of expanding it — and `*` isn't a legal
   Windows filename character, so the build blew up trying to create a file
   literally named `src/*.o`. Fixed to `SRC = $(wildcard src/*.c)`.
2. It linked against `-l c_graph_prog`, an Epitech-internal helper library
   not installed anywhere and not present in this repo. Since
   `src/my_runner.c` only actually calls real **CSFML** functions
   (`sfRenderWindow_create`, `sfSprite_*`, `sfTexture_*`, `sfMusic_*`,
   `sfClock_*`, `sfKeyboard_isKeyPressed`, ...), the fix was to install CSFML
   2.5.1 into the MinGW-w64 toolchain and change the link line to:

```make
gcc -o $(NAME) $(OBJ) -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -Wall -Wextra
```

Because this game plays two looping `.ogg` tracks, `csfml-audio-2.dll` is
actually loaded at runtime, which in turn needs **OpenAL32.dll** — not
provided by Windows or by the CSFML package. This was installed too (OpenAL
Soft's `soft_oal.dll`, renamed `OpenAL32.dll`, dropped into the MinGW
toolchain's `bin/`).

`mingw32-make` now builds `my_runner.exe` cleanly with no source changes
needed, and it launches correctly.

**Note:** if you run it from Git Bash (`./my_runner.exe`), you may see a
misleading `error while loading shared libraries: api-ms-win-crt-*.dll`
message — this is a false negative in Git Bash/MSYS's own dependency
pre-checker, not a real missing dependency (confirmed: the same binary
launches fine from PowerShell, `cmd`, or double-click in Explorer).

Also note: the `my_runner` binary previously committed in this folder was a
**Linux ELF 64-bit executable** and would not run on Windows — the fresh
`mingw32-make` build above replaces it with a real Windows `.exe`.

## Usage

```sh
./my_runner
./my_runner -h    # prints a short in-terminal usage/help blurb, then still launches the game
```

Controls (from the in-game help text and `src/my_runner.c`):

| Key | Action |
|-----|--------|
| SPACE (held) | Jump — trumps position rises while held, speed increases the longer you hold it, and score ticks down while airborne |
| ESCAPE | Quit / end the run |
| (window close button) | Quit / end the run |

The terminal also prints the running score every 10 frames and a final
`Final score : N done in T seconds.` line when the game ends.

## How it works

Everything lives in a single `main()` in `src/my_runner.c` (no separate game
struct/state files, unlike `my_rpg`):

- **Window/assets**: opens an 800x600 CSFML window titled "My Runner",
  loads `assets/background.png`, `assets/cactus.png` (used twice, for a
  looping pair of cacti), `assets/trump_run.png` (a run-cycle spritesheet)
  and `assets/sombrero.png` (the obstacle spritesheet), plus two looping
  `.ogg` tracks (`ugandan_cluk.ogg`, `do_you_know_da_wae.ogg`) played
  simultaneously via `sfMusic_play`.
- **Sprite animation**: `rect_trump` and `rect_sombrero` are `sfIntRect`
  windows into their spritesheets, advanced by a fixed pixel offset
  (`rect_trump.left += 100`, `rect_sombrero.left += 110`) every ~0.2 real
  seconds (measured with `sfClock_getElapsedTime`), cycling through 3 trump
  run frames and 2 sombrero frames before wrapping back to 0.
  `sfSprite_setTextureRect` applies the current frame each tick.
  Set `vitesse_trump` (a scroll-speed float, starts at 1) increases by 0.05
  every frame Space is held, which speeds up both the trump run-cycle
  intent and the horizontal scroll of the cactus/sombrero sprites.
- **Scrolling obstacles**: `position_cactus`, `position_cactus_copy` and
  `position_sombrero` all move left each frame by `vitesse_trump`-scaled
  deltas; once a sprite's `x` drops below `-100` it's reset back off the
  right edge of the screen (`710`), creating a simple infinite parallax
  loop with two cacti (background decoration) and one sombrero (the actual
  obstacle).
- **Jump physics**: while `sfKeySpace` is held, `position_trump.y` decreases
  (rises) by 15px/frame down to a floor of `y > 300`, and score decreases by
  2/frame (a cost for jumping); when Space is released, `position_trump.y`
  increases (falls) by 10px/frame back down to its resting `y <= 425`.
- **Scoring & collision**: score increases by 1 every frame regardless,
  minus the jump cost above. A simple AABB-ish overlap check between
  `position_trump` and `position_sombrero` (with small margins) subtracts
  50 points on collision. The game loop's exit condition
  (`sfEvtClosed` / Escape pressed / `score < 0`) stops music, closes the
  window, and prints "GAME OVER".
- **Homemade libc**: `src/my_printf.c` (+ `my_putchar.c`, `my_putstr.c`,
  `my_put_nbr_base.c`, `my_put_unsigned_int.c`, `my_put_pointer.c`,
  `my_put_spe_str.c`, `my_strlen.c`, `my_getnbr.c`) reimplements a small
  `printf`-like formatter (`%d %i %o %x %X %u %c %s %S %p %b %#o %#x %#X`)
  from scratch instead of using the real `<stdio.h>`, standard for Epitech
  "no-libc" project rules.

## Other contents

- `bonus/my_hunter_example.zip` and `Runner.zip` are archived reference/
  submission material, not part of the active source tree.
