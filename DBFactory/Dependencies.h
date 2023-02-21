#pragma once
#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <codecvt>
#include <locale.h>
#define MAX_CHARACTERS 40
#ifdef SQLFACTORY_API_EXPORTS
#define SQLFACTORY_API __declspec(dllexport)
#else
#define SQLFACTORY_API __declspec(dllimport)
#endif
using namespace std;

template<typename T>

using SQL_order_map = unordered_map<size_t, T>;

enum Languages
{
	HEB,
	ARAB,
};