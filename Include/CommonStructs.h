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
	{"Space Invaders", "̫��������"},
	{"Start Game", "��ʼ��Ϸ"},
	{"Exit Game", "�˳���Ϸ"},
	{"Score: ", "������"},
	{"Record: ", "��¼��"},
	{"Health: ", "������"},
	{"Options", "����"},
	{"Language", "����"},
	{"English", "����"},
	{"Resolution", "�ֱ���"},
	{"Fullscreen", "ȫ��"},
	{"Game Over", "��Ϸ����"},
	{"Press A to restart", "����A���¿�ʼ��Ϸ"},
	{"Press ESC to restart", "����ESC���¿�ʼ��Ϸ"}
};

#endif // COMMONSTRUCTS_H