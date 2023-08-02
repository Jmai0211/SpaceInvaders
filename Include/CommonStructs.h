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
    {800, 600},
    {1024, 768},
    {1280, 720},
    {1920, 1080},
};

// Data table for text in different languages
const TextData textDataTable[] = {
	{"Space Invaders", "̫��������"},
	{"Start Game", "��ʼ��Ϸ"},
	{"Exit Game", "�˳���Ϸ"},
	{"Score: ", "������"},
	{"Health: ", "������"},
	{"Options", "����"},
	{"Language", "����"},
	{"English", "����"},
	{"Resolution", "�ֱ���"},
	{"Fullscreen", "ȫ��"}
};

#endif // COMMONSTRUCTS_H