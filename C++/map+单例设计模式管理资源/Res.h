#pragma once
#include"graphics.h"
#include<iostream>
#include"string"
#include<map>

using namespace std;

class Res{
public:
	~Res();
	//实现单例模式的关键点
	static Res* GetRes();
	//资源管理
	//单张图片
	static map<string, IMAGE*> layout; 
	//多张图片
	static map<string, pair<int,IMAGE*>> action;
	static void ShowLayout(int x,int y,string name);
	static void ShowAction(int x,int y,string name,int frame);
private:
	Res();
};
