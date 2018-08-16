#include "JsonParse.h"
using namespace std;
JSONObj::JSONObj(std::string v) {
	val = v;
}
string JSONObj::asString() {
	if (val.find("\"") == -1)return "";
	val = val.substr(val.find("\""));
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
	int commark;
	while ((commark = json.find(',')) != -1) {
		string obj = json.substr(0, commark);
		string key = trim(obj.substr(0, obj.find(':')));
		key = key.substr(1, key.size() - 2);
		ret.pool[key] = { trim(obj.substr(obj.find(':') + 1)) };
		json = json.substr(commark + 1);
	}
	if ((commark = json.find('}')) != -1) {
		string obj = json.substr(0, commark);
		string key = trim(obj.substr(0, obj.find(':')));
		key = key.substr(1, key.size() - 2);
		ret.pool[key] = { trim(obj.substr(obj.find(':') + 1)) };
		json = json.substr(commark + 1);
	}
	else return JSON();
	return ret;
}

JSONObj &JSON::operator[](std::string key) {
	return pool[key];
}
