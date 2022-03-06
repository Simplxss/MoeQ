#pragma once
#include "Pack.h"

namespace JceStruct
{
	enum class JceStructType
	{
		BYTE = 0,
		SHORT = 1,
		INT = 2,
		LONG = 3,
		FLOAT = 4,
		DOUBLE = 5,
		STRING1 = 6,
		STRING4 = 7,
		MAP = 8,
		LIST = 9,
		STRUCT_BEGIN = 10,
		STRUCT_END = 11,
		ZERO_TAG = 12,
		SIMPLE_LIST = 13,
	};

	template <typename _Key, typename _Value>
	struct Map
	{
		_Key	Key;
		_Value Value;
	};
};

class Jce :
	private Pack
{
public:
	Jce(bool Length = false) :Pack(300U, Length) {};
private:
	void WriteHead(const JceStruct::JceStructType type, const byte tag);
public:
	void Write(const char i, const byte tag);
	void Write(const short i, const byte tag);
	void Write(const int i, const byte tag);
	void Write(const long long i, const byte tag);
	void Write(const float f, const byte tag);
	void Write(const double d, const byte tag);
	void Write(const char* str, const byte tag);
	void Write(const wchar_t* str, const byte tag);
	void Write(const LPBYTE bin, const byte tag);
	void Write(const byte* bin, const uint32_t len, const byte tag);
	template <typename Key, typename Value>
	void Write(const std::vector<JceStruct::Map<Key, Value>>* map, const byte tag)
	{
		WriteHead(JceStruct::JceStructType::MAP, tag);
		uint32_t length = (*map).size();
		Write(length, 0);
		for (size_t i = 0; i < length; i++)
		{
			Write((*map)[i].Key, 0);
			Write((*map)[i].Value, 1);
		}
	};
	template<typename Te>
	void Write(const std::vector<Te>* T, const byte tag)
	{
		WriteHead(JceStruct::JceStructType::LIST, tag);
		uint32_t length = (*T).size();
		Write(length, 0);
		for (size_t i = 0; i < length; i++)
		{
			Write((*T)[i], 0);
		}
	};
	void Write(Jce* Jce, const byte tag);
	void Write(const bool b, const byte tag);
	void Write(const uint32_t i, const byte tag);
	LPBYTE GetAll();
	uint32_t GetAll(byte*& bin);
	LPBYTE GetAll_(bool Length = false);
	uint32_t GetAll_(byte*& bin, bool Length = false);
	void Clean(bool Length);
};

class UnJce :
	private UnPack
{
public:
	UnJce(const byte* buffer, const uint32_t bufferlen) :UnPack(buffer, bufferlen) {}
	UnJce(const LPBYTE buffer) :UnPack(buffer) {}
	UnJce() :UnPack(0, 0) {}
private:
	void SkipField(JceStruct::JceStructType type);
	JceStruct::JceStructType SkipToTag(const byte tag);
public:
	void Reset(const LPBYTE buffer);
	void Reset(const byte* buffer, const uint32_t bufferlen);
	template <typename T>
	typename std::enable_if < std::is_same<byte, T>::value
		|| std::is_same<short, T>::value
		|| std::is_same<int, T>::value
		|| std::is_same<long long, T>::value, void > ::type
		Read(T& digital, const byte tag)
	{
		switch (SkipToTag(tag))
		{
		case JceStruct::JceStructType::BYTE:
			digital = GetByte();
			break;
		case JceStruct::JceStructType::SHORT:
			digital = (short)GetShort();
			break;
		case JceStruct::JceStructType::INT:
			digital = (int)GetInt();
			break;
		case JceStruct::JceStructType::LONG:
			digital = (long long)GetLong();
			break;
		case JceStruct::JceStructType::ZERO_TAG:
			digital = 0;
			break;
		default:
			throw "Not digital type";
			break;
		}
	};
	void Read(float& f, const byte tag);
	void Read(double& d, const byte tag);
	void Read(char*& str, const byte tag);
	void Read(char8_t*& str, const byte tag);
	void Read(LPBYTE& bin, const byte tag);
	template <typename Key, typename Value>
	void Read(std::vector<JceStruct::Map<Key, Value>>& Map, const byte tag)
	{
		if (SkipToTag(tag) != JceStruct::JceStructType::MAP) throw "type error";
		int len = 0;
		Read(len, 0);
		Map.resize(len);
		for (size_t i = 0; i < len; i++)
		{
			Read(Map[i].Key, 0);
			Read(Map[i].Value, 1);
		}
	};
	template<typename Te_>
	void Read(std::vector<Te_>& Te, const byte tag)
	{
		if (SkipToTag(tag) != JceStruct::JceStructType::LIST) throw "type error";
		int len;
		Read(len, 0);
		Te.resize(len);
		for (size_t i = 0; i < len; i++)
		{
			Read(Te[i], 0);
		}
	};
	void Read(UnJce& UnJce, const byte tag);
};
