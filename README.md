# 8mu 
**8mu** is a CHIP-8 interpreter I wrote as a project at my university.
It's not yet a 100% compatible with all roms, since there are a lot of edge cases that
I haven't been able to spot or address appropriately.

## What works
At the moment, there are 9 games that work, they are placed in the `roms` folder.
This is a list of working games, along with their control mappings:
- Wipe Off
    - author: [Joseph Weisbecker](https://en.wikipedia.org/wiki/Joseph_Weisbecker)
    - controls:
        - Q - move the paddle left
        - E - move the paddle right
- Brix
    - author: [Andreas Gustafsson](https://www.hpcalc.org/authors/375)
    - controls:
        - Q - move the paddle left
        - E - move the paddle right
- Tank
    - author: _didn't find the author yet_
    - controls: _(for some reason, the movement up and down is reversed non intuitively)_
        - 2 - move the tank down 
        - Q - move the tank left
        - E - move the tank right
        - S - move the tank up
        - W - shoot
- Slippery Slope
    - author: [John Earnest](https://github.com/JohnEarnest)
    - controls:
        - W - move up
        - S - move down
        - A - move left
        - D - move right
        - E - restart level
- Pong
    - author: _didn't find the author yet_
    - controls:
        - 1 - move the paddle up
        - Q - move the paddle down
- Tetris
    - author: Fran Dachille
    - controls:
        - W - move the tetronimo left
        - E - move the tetronimo right
        - Q - rotate the tetronimo
        - A - move the tetronimo down fast
- UFO
    - author: Lutz V.
    - controls:
        - Q - fire to the left
        - W - fire upwards
        - E - fire to the right
- Blitz
    - author: [David Winter](http://www.pong-story.com/)
    - controls:
        - w - drop a bomb
- Flight Runner
    - author: [Tod Hansmann](https://github.com/TodPunk/)
    - controls:
        - W - move up
        - S - move down
        - A - move left
        - D - move right

