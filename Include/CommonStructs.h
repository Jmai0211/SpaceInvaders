#pragma once
#pragma execution_character_set("utf-8")
#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

struct Resolutions
{
	int width;
	int height;
};

struct TextData
{
	const char* englishText;
	const char* chineseText;
};

// Data table for resolutions
const Resolutions resolutionTable[] = {
    {640, 360},
    {1024, 576},
    {1280, 720},
	{1366, 768},
    {1920, 1080},
	{2560, 1440},
	{3840, 2160}
};

// Data table for text in different languages
const TextData textDataTable[] = {
	{"Space Invaders", "太空侵略者"},
	{"Start Game", "开始游戏"},
	{"Exit Game", "退出游戏"},
	{"Score: ", "分数："},
	{"Record: ", "记录："},
	{"Health: ", "生命："},
	{"Options", "设置"},
	{"Language", "语言"},
	{"English", "中文"},
	{"Resolution", "分辨率"},
	{"Fullscreen", "全屏"},
	{"Game Over", "游戏结束"},
	{"Press A to restart", "按下A重新开始游戏"},
	{"Press ESC to restart", "按下ESC重新开始游戏"}
};

#endif // COMMONSTRUCTS_H