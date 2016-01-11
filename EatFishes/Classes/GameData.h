#ifndef GAMEDATA_H
#define GAMEDATA_H

const int MAX_LEVEL = 10;
const int LEVEL[MAX_LEVEL + 1] = { 0, 0, 10, 30, 70, 120, 200, 300, 500, 750, 1000};
//const int LEVEL[MAX_LEVEL + 1] = { 0, 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };
//const int MAX_FISHES_NUM = 64;
//const int FISHES_LIST[MAX_LEVEL + 1] = { 0, 15, 13, 10, 8, 7, 5, 3, 2, 1, 0 };


const int FISHES_LIST_01[MAX_LEVEL + 1] = { 0, 15, 10, 8, 7, 5, 2, 0, 0, 0, 0 };
const int FISHES_LIST_02[MAX_LEVEL + 1] = { 0, 3, 4, 5, 7, 12, 10, 5, 3, 1, 0 };
const int FISHES_LIST_03[MAX_LEVEL + 1] = { 0, 1, 2, 3, 5, 6, 7, 8, 10, 8, 2 };

const int FISH_ENERGY[MAX_LEVEL + 1] = { 0, 1, 2, 3, 5, 8, 12, 16, 20, 25, 30 };

// 道具更新时间
const float PROPS_UPDATE_TIME = 10.0f;

// 鱼逃跑距离
const float FISH_ESCAPING_DISTANCE = 50.0f;

#define BGMUSIC ("audios_bg.mp3")
#define EFFECT_BUTTON_CLICK ("audios_btn.wav")
#define EFFECT_GAME_START ("audios_gamestart.mp3")
#define EFFECT_GAME_OVER ("audios_gameover.mp3")
#define EFFECT_PLAYER_UPGRADE ("audios_growth.mp3")

#endif