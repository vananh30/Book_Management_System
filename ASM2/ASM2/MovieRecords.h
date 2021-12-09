#pragma once
#include<string>
#include "Item.h"
using namespace std;
class MovieRecords : public Item
{
private:
	string genres;
public:
	/*getter*/
	string getGenres();
	/*setter*/
	void setGenres(string genres);
	/*Constructor*/
	MovieRecords();
	MovieRecords(Item *item);
	~MovieRecords();
	/*Override toString()*/
	virtual string toString();
};

