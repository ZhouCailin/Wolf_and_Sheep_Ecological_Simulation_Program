#include <iostream>
#include <fstream>
#include "StdAfx.h"


using namespace std;


#include "WOLFNSHEEP.h"


World::World(){
	int i,j;
	Time=0;
	for(i=0;i<5;i++)
		for(j=0;j<5;j++)
			grid[i][j]=NULL;
}

void World::zeroAllMark(){
		int i,j;
		Organism* Optr;
		for(i=0;i<M;i++){
			for(j=0;j<M;j++){
				Optr=grid[i][j];
				if(Optr==NULL)continue;
				grid[i][j]->setMark(0);
			}
		}
}

void World::SimulateOneStep(){
	int i,j;
	Organism *Optr;
	
	/*Wolf Move*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			Optr=grid[i][j];
			if(Optr==NULL)continue;
			if(Optr->getMark()==0&&Optr->getType()==2)Optr->move();
		}
	}
	zeroAllMark();
	
	/*Sheep Move*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			Optr=grid[i][j];
			if(Optr==NULL)continue;
			if(Optr->getMark()==0&&Optr->getType()==1)Optr->move();
		}
	}
	zeroAllMark();

	Time++; 
	/*After Time Counted, Breed and Starve Happen*/
	/*Wolf Starve*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			Optr=grid[i][j];
			if(Optr==NULL)continue;
			if(Optr->getMark()==0&&Optr->getType()==2){
				if(Time-Optr->getEatTime()==4)Optr->starve();
			}
		}
	}

	/*Wolf Breed*/
	if(Time!=0 && Time%8==0){
		for(i=0;i<M;i++){
			for(j=0;j<M;j++){
				Optr=grid[i][j];
				if(Optr==NULL)continue;
				if(Optr->getType()==2&&Optr->getMark()==0)Optr->breed();
			}
		}
	}
	zeroAllMark();

	/*Sheep Breed*/
	if(Time!=0 && Time%3==0)
	{
		for(i=0;i<M;i++){
			for(j=0;j<M;j++){
				Optr=grid[i][j];
				if(Optr==NULL)continue;
				if(Optr->getType()==1&&Optr->getMark()==0)Optr->breed();
			}
		}
	}
	zeroAllMark();
	/*Wolf Starve*/
	//grid[1][3]->starve();
	
}

void World::Display(){
	int i,j;
	Organism* Optr;
	cout<<"\n\n************ Time "<<Time<<" *************"<<endl;
	for(i=0;i<M;i++){
		cout<<endl<<"\t";
		for(j=0;j<M;j++){
			Optr=grid[i][j];
			if(Optr==NULL){cout<<"[ ]";continue;}
			if(Optr->getType()==1)cout<<"[O]";
			if(Optr->getType()==2)cout<<"[X]";
		}
	}
}

int World::gridType(int i,int j){
	Organism* Optr;
	Optr=grid[i][j];
	if(Optr==NULL){return 0;}
	if(Optr->getType()==1){return 1;}
	if(Optr->getType()==2){return 2;}
}




void World::write(){
/*	int i,j;
	Organism* Optr;
	ofstream out;
	out.open("Toutput.txt");
	out<<"Time is "<<Time;
	for(i=0;i<M;i++){
		out<<endl;
		for(j=0;j<M;j++){
			Optr=grid[i][j];
			if(Optr==NULL){out<<"[  ]";continue;}
			if(Optr->getType()==1)out<<"[O]";
			if(Optr->getType()==2)out<<"[X]";
		}
	}
	out.close();
	*/
}
	

void Sheep::breed(){
	int arr[4]={0},index=0;
	int ix,iy,idx,ran;
	Sheep* Newsptr;
	Organism* Optr;
	if(x!=0 && world->getAt(x-1,y)==NULL)arr[0]=1,index=1; 
	if(y!=N && world->getAt(x,y+1)==NULL)arr[1]=1,index=1;
	if(x!=N && world->getAt(x+1,y)==NULL)arr[2]=1,index=1;
	if(y!=0 && world->getAt(x,y-1)==NULL)arr[3]=1,index=1;
	
	/*当附近有空格时*/
	if(index){
		do{
			idx=rand()%4;
			ran=arr[idx];
		}
		while(ran==0);
		switch(idx){
		case 0:ix=x-1;iy=y;break; 
		case 1:ix=x;iy=y+1;break;
		case 2:ix=x+1;iy=y;break;
		case 3:ix=x;iy=y-1;break;
		}
		Newsptr=new Sheep(world,ix,iy,1); //mark=1;
		Optr=Newsptr;
		world->setAt(ix,iy,Optr); 
	}
}


void Sheep::move(){
	//纯虚函数可以直接使用基类的private??
	int idx,ix,iy,ran;
	int arr[4]={0},index=0;
	Organism* Nptr=NULL;

	if(x!=0 && world->getAt(x-1,y)==NULL)arr[0]=1,index=1; //记得是world->getAt，如果直接getAt就是这个对象构造的基类World类，不是private成员world！调试发现地址不一样
	if(y!=N && world->getAt(x,y+1)==NULL)arr[1]=1,index=1;
	if(x!=N && world->getAt(x+1,y)==NULL)arr[2]=1,index=1;
	if(y!=0 && world->getAt(x,y-1)==NULL)arr[3]=1,index=1;

	if(index){
		do{
			idx=rand()%4;
			ran=arr[idx];
		}
		while(ran==0);
		switch(idx){
		case 0:ix=x-1;iy=y;break; 
		case 1:ix=x;iy=y+1;break;
		case 2:ix=x+1;iy=y;break;
		case 3:ix=x;iy=y-1;break;
		}//0~3，不是1~4，卡了很久
		world->setAt(x,y,Nptr);//原格置空
		x=ix;//记得更新xy
		y=iy;
		mark=1; //!
		Organism* ptr=this;//Organsim*(this)?不可以,this不能强制转换 !!!
		world->setAt(ix,iy,ptr);//新格
	}
}


void Wolf::breed(){
	int arr[4]={0},index=0;
	int ix,iy,idx,ran;
	Wolf* Newsptr;
	Organism* Optr;
	int tm=world->getTime();
	if(x!=0 && world->getAt(x-1,y)==NULL)arr[0]=1,index=1; 
	if(y!=N && world->getAt(x,y+1)==NULL)arr[1]=1,index=1;
	if(x!=N && world->getAt(x+1,y)==NULL)arr[2]=1,index=1;
	if(y!=0 && world->getAt(x,y-1)==NULL)arr[3]=1,index=1;
	
	/*当附近有空格时*/
	if(index){
		do{
			idx=rand()%4;
			ran=arr[idx];
			if(ran==1)break;
		}
		while(ran==0);
		switch(idx){
		case 0:ix=x-1;iy=y;break; 
		case 1:ix=x;iy=y+1;break;
		case 2:ix=x+1;iy=y;break;
		case 3:ix=x;iy=y-1;break;
		}
		Newsptr=new Wolf(world,ix,iy,1,tm);//mark=1
		Optr=Newsptr;
		world->setAt(ix,iy,Optr); 
	}
}

void Wolf::move(){
	int idx,ix,iy,ran;
	int arr[4]={0},brr[4]={0},index=0;
	int gt;
	int tm=world->getTime();
	Organism* Nptr=NULL;
	Organism* Optr;

	/*Wolf's Eat*/
	/*Up*/
	if(x!=0){
		if(world->getAt(x-1,y)==NULL){/*卡了很久，漏world->*/
			arr[0]=1,index=1;
		}
		else{
			Optr=world->getAt(x-1,y);
			if(Optr!=NULL){         /*如果这里不判断，下一步空指针的getType()会报错*/
				gt=Optr->getType(); /*判断是否为羊,value=1*/
				if(gt==1){ 
					ix=x,iy=y;
					x=x-1;
					mark=1; //!!
					EatTime=tm;
					Optr=this;
					world->setAt(ix-1,iy,Optr);/*羊格设为此格Organz指针*/
					world->setAt(ix,iy,Nptr);  /*此格设空*/
					return;
				}
			}
		}
	}
	/*Right*/
	if(y!=N){
		if (world->getAt(x,y+1)==NULL){
			arr[1]=1,index=1;
		}
		else{
			Optr=world->getAt(x,y+1);
			if(Optr!=NULL){
				gt=Optr->getType();
				if(gt==1){
					ix=x,iy=y;
					y=y+1;
					mark=1;
					EatTime=tm;
					Optr=this;
					world->setAt(ix,iy+1,Optr);
					world->setAt(ix,iy,Nptr);
					return;
				}
			}
		}
	}
	/*Down*/
	if(x!=N){
		if(world->getAt(x+1,y)==NULL){
			arr[2]=1,index=1;
		}
		else{
			Optr=world->getAt(x+1,y);
			if(Optr!=NULL){
				gt=Optr->getType();
				if(gt==1){
					ix=x,iy=y;
					x=x+1;
					mark=1;
					EatTime=tm;
					Optr=this;
					world->setAt(ix+1,iy,Optr);
					world->setAt(ix,iy,Nptr);
					return;
				}
			}
		}
	}
	/*Left*/
	if(y!=0){
		if(world->getAt(x,y-1)==NULL){
			arr[3]=1,index=1;
		}
		else{
			Optr=world->getAt(x,y-1);
			if(Optr!=NULL){
				gt=Optr->getType();
				if(gt==1){
					ix=x,iy=y;
					y=y-1;
					mark=1;
					EatTime=tm;
					Optr=this;
					world->setAt(ix,iy-1,Optr);
					world->setAt(ix,iy,Nptr);
					return;
				}
			}
		}
	}
	
	/*Wolf's Move without Eating*/
	if(index){
		do{
			idx=rand()%4;
			ran=arr[idx];
			if(ran==1)break;
		}
		while(ran==0);
		switch(idx){
		case 0:ix=x-1;iy=y;;break; 
		case 1:ix=x,iy=y+1;break;
		case 2:ix=x+1;iy=y;break;
		case 3:ix=x;iy=y-1;break;
		}
		world->setAt(x,y,Nptr);
		x=ix;
		y=iy;
		mark=1;
		Organism* ptr=this;
		world->setAt(ix,iy,ptr);
	}
}

void Wolf::starve(){
	Organism* Nptr=NULL;
	world->setAt(x,y,Nptr);
}