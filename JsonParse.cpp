#include "JsonParse.h"
using namespace std;

JSONObj::JSONObj() { }
JSONObj::JSONObj(std::string v) {
	val = v;
}
string JSONObj::asString() {
	if (val.find("\"") == -1)return "";
	val = val.substr(val.find("\"") + 1);
	val = val.substr(0, val.find("\""));
	return val;
}

bool JSONObj::asBool() {
	if (val.find("true") != -1)return true;
	return false;
}

int JSONObj::asInteger() {
	return atoi(trim(val).c_str());
}

JSON JsonParse(string json) {
	JSON ret;
	json = json.substr(json.find('{'));
	json = json.substr(0, json.find('}')+1);
	int commark, mark;
	while ((commark = json.find(',')) != -1) {
		string object = json.substr(0, commark);
		mark = -1; while (object[++mark] != '"'&&mark < object.size());
		string key = object.substr(mark + 1); key = key.substr(0, key.find('"'));
		string val = trim(object.substr(object.find(':') + 1));
		ret[key] = { val };
		json = json.substr(commark + 1);
	}
	if ((commark = json.find('}')) != -1) {
		string object = json.substr(0, commark);
		mark = -1; while (object[++mark] != '"'&&mark < object.size());
		string key = object.substr(mark + 1); key = key.substr(0, key.find('"'));
		string val = trim(object.substr(object.find(':') + 1));
		ret[key] = { val };
		json = json.substr(commark + 1);
	}
	else return JSON();
	return ret;
}

JSONObj &JSON::operator[](std::string key) {
	return pool[key];
}
