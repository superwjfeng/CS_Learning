#pragma once
#include <iostream>
#include <list>
using namespace std;

struct Node
{
	int _value;
	int _in; //入度，有多少个边指向此节点
	int _out;
	list<Node*>* _nexts;
	list<Edge*>* _edges;

	Node(int val)
		:_value(val)
		, _in(0)
		, _out(0)
		, _nexts(nullptr)
		, _edges(nullptr)
	{}

};

struct Edge
{
	int _weight;
	Node* _from;
	Node* _to;

	Edge();
	Edge(int weight, Node* from, Node* to)
		:_weight(weight)
		, _from(from)
		, _to(to)
	{}
};
