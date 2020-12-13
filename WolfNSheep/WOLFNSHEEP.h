#ifndef WOLFNSHEEP_H
#define WOLFNSHEEP_H
#define M 5   /*grid size*/
#define N M-1 /*biggest index*/

#include <iostream>
#include "StdAfx.h" /*MFC头文件勿忘*/
using namespace std;

class Organism; 

class World{
public:
	World();
	void setAt(int x,int y,Organism *org){grid[x][y]=org;} 
	Organism* getAt(int x, int y){return grid[x][y];}
	void SimulateOneStep();
	void Display();
	void write();
	void zeroAllMark(); 
	int getTime(){return Time;}
	int gridType(int ,int);
private:
	Organism* grid[M][M];
	int Time;
};

class Organism:public World{
public:
	Organism(World* wor,int locx, int locy,int mk):world(wor),x(locx),y(locy),mark(mk){};
	virtual void breed()=0;
	virtual void move()=0;
	virtual int getType()=0;
	virtual void starve()=0;
	int getMark(){return mark;} 
	void setMark(int x){mark=x;}
	virtual void setEatTime(int x)=0; 
	virtual int getEatTime()=0;
protected:
	World* world;
	int x;
	int y;
	int mark;  /*在Simulate中做出行为后的标记，防止在一次simulate中无限做出行为*/
};

class Sheep:public Organism{
public:
	Sheep(World* w,int locx,int locy,int mk=0):Organism(w,locx,locy,mk){};
	void breed();
	void move();
	int getType(){return 1;}
	void starve(){};
	void setEatTime(int x){};
	int getEatTime(){return 0;}
};

class Wolf:public Organism{
public:
	Wolf(World *w,int locx,int locy,int mk=0,int et=0):Organism(w,locx,locy,mk),EatTime(et){};
	void breed();
	void move();
	int getType(){return 2;}
	void starve();
	void setEatTime(int x){EatTime=x;}
	int getEatTime(){return EatTime;}
public:
	int EatTime;
};


#endif