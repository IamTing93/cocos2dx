#ifndef GLOBAL_H
#define GLOBAL_H

#define GAME_OVER ("gameOver")
#define GAME_RESTART ("gameRESTART")
#define GAME_PAUSE ("gamePause")
#define GAME_RESUME ("gameResume")
#define GAME_START ("gameStart")

#define PLAYER_UPGRADE ("playerUpgrade")

#define PLAYER_NORMAL (0)
#define PLAYER_BIGGER (1)
#define PLAYER_SMALLER (2)


#define OVER (1)
#define PAUSE (2)
#define START (3)

#define GAME_STATE_01 (1)
#define GAME_STATE_02 (2)
#define GAME_STATE_03 (3)

enum Direction {
	left = -1,
	right = 1,
	up = 2,
	down = -2
};



#endif