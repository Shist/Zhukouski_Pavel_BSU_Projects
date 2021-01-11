#pragma once
#include "pch.h"
#include <iostream>
#include <string>
#include <thread>
#include <Windows.h>
#include <conio.h>
#include <mutex>
#include <atomic>
using namespace std;

class Mum_Dad
{
public:
	static mutex x;
	static atomic<int> Whole_Count;
	int thr_count;
	string thrdName;
	int amount;
	int time;
	Mum_Dad(string name, int am, int t);
	void Run();
	virtual ~Mum_Dad();
};