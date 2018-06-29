#pragma once
#include "Vec2.h"
#include <string>
#include <vector>
#include <bitset>

using namespace std;

struct Obj
{
	string name;
	bitset<128> flags;

	Vec2I pos;
	char c;

	virtual void Update(){}
};

struct ObjList
{
	vector<Obj*> list;

	void push_back(Obj* object){ list.push_back(object); }
	Obj* get(int i){ return list[i]; }
	Obj* find(string name)
	{ 
		for each(Obj* obj in list)
		{
			if (obj->name.compare(name) == 0)
			{
				return obj;
			}
		}
		return nullptr;
	}

	vector<Obj*> findAll(string name)
	{
		vector<Obj*> found;
		for each(Obj* obj in list)
		{
			if (obj->name.compare(name) == 0)
			{
				found.push_back(obj);
			}
		}
		return found;
	}
};
