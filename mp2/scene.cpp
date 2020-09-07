#include "scene.h"

using namespace std;


Scene::Scene(int max)
{
	images = new Image *[max];
	for(int i=0;i<max;i++)
		images [i]=NULL;
	xcord = new int [max];
	ycord = new int [max];
	max_lyr=max;
	
	//code here
}

Scene::~Scene()
{
	clear();//code here
}
Scene::Scene(const Scene & source)
{
	copy(source);//code here
}
const Scene & Scene::operator=(const Scene & source)
{
	if(this != &source)
	{
		clear();
		copy(source);
	}
	return *this;//code
}
void Scene::changemaxlayers(int newmax)
{
	if(newmax<max_lyr){
		for(int i=newmax;i<max_lyr;i++)
			if(images[i]!=NULL){
				cout<<"invaild newmax"<<endl;//code
				return; }	
		}
	Scene * temp = new Scene(newmax);
	for(int i=0;i<this->max_lyr;i++)
		if(images[i]!=NULL)
			*(temp->images[i])=*images[i];
	this->copy(*temp);
}
void Scene::addpicture(const char * FileName, int index, int x, int y)
{
	if(index<0||index>max_lyr-1){
                cout<<"index out of bounds"<<endl;
		return;
	}
	if(images[index]!=NULL)
		deletepicture(index);
	images[index]=new Image();
	images[index]->readFromFile(FileName);
	xcord[index]=x;
	ycord[index]=y;//code
}
void Scene::changelayer(int index, int newindex)
{	
	if(index==newindex)
		return;
	if(images[newindex]!=NULL)
		deletepicture(newindex);
	if(index<0||index>max_lyr-1||newindex<0||newindex>max_lyr-1){
                cout<<"invalid index"<<endl;
		return;
	}
	images[index]= new Image();
	images[newindex]=images[index];
	images[index]=NULL;
	return;//code
}
void Scene::translate(int index, int x, int y)
{
	if(index<0||index>max_lyr-1||images[index]==NULL){
                cout<<"invalid index"<<endl;
		return;
	}
	xcord[index]=x;
	ycord[index]=y;
	return;
	//code
}
void Scene::deletepicture(int index)
{
	if(index<0||index>max_lyr-1||images[index]==NULL){
		cout<<"invalid index"<<endl;
		return;
	}
	delete images[index];
	images[index]=NULL;
	return;//code
}
Image * Scene::getpicture(int index) const
{
	if(index<0||index>max_lyr-1){
                cout<<"invalid index"<<endl;
		return NULL;
	}
	if(images[index]==NULL)
		return NULL;
	return images[index];//code
}
Image Scene::drawscene() const
{
	Image  FImage= Image();
	for(int i=0;i<max_lyr;i++){
	if(images[i]!=NULL){
	FImage.resize(max(FImage.width(),xcord[i]+images[i]->width()),max(FImage.height(),ycord[i]+images[i]->height()));
	for(int x=xcord[i];x<xcord[i]+images[i]->width();x++)
		for(int y=ycord[i];y<ycord[i]+images[i]->height();y++){
			FImage(x,y)->red=(*images[i])(x-xcord[i],y-ycord[i])->red;
			FImage(x,y)->green=(*images[i])(x-xcord[i],y-ycord[i])->green;
			FImage(x,y)->blue=(*images[i])(x-xcord[i],y-ycord[i])->blue;
}
}
			
			



	}
	return FImage;//code
}
 
void Scene::clear()
{
	for(int i=0;i<max_lyr;i++)
	if(images[i]!=NULL)
		delete images[i];
	delete []images;
	delete []xcord;
	delete []ycord;

}
void Scene::copy(const Scene & source)
{
	max_lyr = source.max_lyr;
	xcord = new int [max_lyr];
		for(int i =0; i<max_lyr; i++)
			
			xcord[i]=source.xcord[i];
	ycord = new int [max_lyr];
		for(int i=0; i<max_lyr; i++)
		
			ycord[i]=source.ycord[i];
	images = new Image* [max_lyr];
		for(int i=0; i<max_lyr; i++){
			images[i]=new Image();
			if(source.images[i]!=NULL)
			*images[i]=*source.images[i];
		}
		
}


