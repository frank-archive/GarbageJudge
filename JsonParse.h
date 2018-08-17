#pragma once
#include"toolkit.h"
class JSONObj {
	std::string val;
public:
	JSONObj();
	JSONObj(std::string v);
	std::string asString();
	bool asBool();
	int asInteger();
	int *asArr();
};
class JSON {
	std::unordered_map<std::string, JSONObj>pool;
public:
	friend JSON JsonParse(std::string json);
	JSONObj &operator [](std::string key);
};
JSON JsonParse(std::string json);