#pragma once
#include "Pack.h"

namespace ProtobufStruct
{
	enum class ProtobufStructType
	{
		VARINT = 0,
		FIX64 = 1,
		LENGTH = 2,
		//3,4 was deprecated
		FIX32 = 5,
	};
	struct TreeNode
	{
		TreeNode* child;
		TreeNode* brother;

		long long int Field;
		ProtobufStruct::ProtobufStructType ProtobufStructType;
		void* Data;
	};
};

class Protobuf :Pack
{
public:
	Protobuf() : ::Pack(4, true) {};
private:
	void SetBin(LPBYTE bin);
	void SetBin_(LPBYTE bin);
	LPBYTE Int2Varint(long long int l);
	int Int2Varint_len(long long int l);
	LPBYTE Field2Key(int Field, ProtobufStruct::ProtobufStructType ProtobufStructType);
	uint FirstProcess(ProtobufStruct::TreeNode* First);
	void SecondProcess(ProtobufStruct::TreeNode* First);
public:
	LPBYTE Pack(ProtobufStruct::TreeNode* First);
};

class UnProtobuf
{
private:
	struct LinkList
	{
		UnPack UnPack;
		LinkList* Superior = nullptr;
	};
	LinkList* List;
public:
	UnProtobuf(const LPBYTE bin)
	{
		List = new LinkList{ bin };
	};
	UnProtobuf(const byte* bin,const uint Length)
	{
		List = new LinkList{ UnPack(bin,Length) };
	};
	~UnProtobuf()
	{
		delete List;
	}
private:
	long long int GetVarint();
	void SkipField(ProtobufStruct::ProtobufStructType type);
	ProtobufStruct::ProtobufStructType SkipToField(const byte Field);
public:
	byte GetField();
	void StepIn(const byte Field);
	void StepOut();
	bool IsEnd();
	long long int GetVarint(const byte Field);
	char8_t* GetStr(const byte Field);
	uint GetBin(byte*& bin, const byte Field);
	LPBYTE GetBin(const byte Field);
	template <typename T>
	typename std::enable_if < std::is_same<int, T>::value
		|| std::is_same<uint, T>::value
		|| std::is_same<float, T>::value, void > ::type
		GetFix32(T& digital, const byte Field)
	{
		switch (SkipToField(Field))
		{
		case ProtobufStruct::ProtobufStructType::FIX32:
			digital = List->UnPack.GetInt();
			break;
		default:
			throw "Not FIX32 type";
			break;
		}
	};
};

