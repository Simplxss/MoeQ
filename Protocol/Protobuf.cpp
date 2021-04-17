#include "Protobuf.h"

long long int UnProtobuf::GetVarint()
{
	long long int l = 0;
	for (size_t i = 0; i < 9; i++)
	{
		byte b = List->UnPack.GetByte();
		l |= (b & 0x7f) << (7 * i);
		if ((b & 0x80) != 0x80)
			goto end;
	}
	throw "len is too long";
end:
	return l;
}

void UnProtobuf::SkipField(ProtobufStruct::ProtobufStructType type)
{
	switch (type)
	{
	case ProtobufStruct::ProtobufStructType::VARINT:
		GetVarint();
		break;
	case ProtobufStruct::ProtobufStructType::FIX64:
		List->UnPack.Skip(8);
		break;
	case ProtobufStruct::ProtobufStructType::LENGTH:
		List->UnPack.Skip(GetVarint());
		break;
	case ProtobufStruct::ProtobufStructType::FIX32:
		List->UnPack.Skip(4);
		break;
	}
}

ProtobufStruct::ProtobufStructType UnProtobuf::SkipToField(const byte Field)
{
	while (true)
	{
		uint key = GetVarint();
		if ((key >> 3) < Field)
		{
			SkipField(static_cast<ProtobufStruct::ProtobufStructType>(key & 0x07));
			continue;
		}
		else if ((key >> 3) == Field)
			return static_cast<ProtobufStruct::ProtobufStructType>(key & 0x07);
		else
			throw "Field not find";
	}
}

byte UnProtobuf::GetField()
{
	UnPack UnPack(List->UnPack);
	uint key = GetVarint();
	List->UnPack = UnPack;
	return key >> 3;
}

void UnProtobuf::StepIn(const byte Field)
{
	if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
	{
		uint len = GetVarint();
		LinkList *tmp = new LinkList{{List->UnPack.GetCurrentPoint(), len}, List};
		List->UnPack.Skip(len);
		List = tmp;
	}
}

void UnProtobuf::StepOut()
{
	if (List->Superior != nullptr)
	{
		LinkList *tmp = List->Superior;
		delete List;
		List = tmp;
	}
}

bool UnProtobuf::IsEnd()
{
	return !List->UnPack.GetLeftLength();
}

long long int UnProtobuf::GetVarint(const byte Field)
{
	if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::VARINT)
		return GetVarint();
	return 0;
}

char8_t *UnProtobuf::GetStr(const byte Field)
{
	if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
	{
		uint len = GetVarint();
		char8_t *str = new char8_t[len + 1];
		memcpy(str, List->UnPack.GetStr(len), len);
		str[len] = 0;
		return str;
	}
	return nullptr;
}

uint UnProtobuf::GetBin(byte *&bin, const byte Field)
{
	if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
	{
		uint len = GetVarint();
		bin = new byte[len];
		memcpy(bin, List->UnPack.GetBin(len), len);
		return len;
	}
	return 0;
}

LPBYTE UnProtobuf::GetBin(const byte Field)
{
	if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
	{
		uint len = GetVarint();
		LPBYTE bin = new byte[len + 4];
		memcpy(bin, XBin::Int2Bin(len + 4), len);
		memcpy(bin + 4, List->UnPack.GetBin(len), len);
		return bin;
	}
	return (LPBYTE)"\0\0\0\4";
}

void Protobuf::SetBin(LPBYTE bin)
{
	Pack::SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
}

void Protobuf::SetBin_(LPBYTE bin)
{
	Pack::SetBin(bin + 4, XBin::Bin2Int(bin) - 4);
	delete bin;
}

LPBYTE Protobuf::Int2Varint(long long int l)
{
	byte Varint[10], i = 0;
	while (l > 0x7F)
	{
		Varint[i] = (l & 0x7F) | 0x80;
		l >>= 7;
		++i;
	}
	Varint[i++] = l;
	LPBYTE Varint_ = new byte[i + 4];
	memcpy(Varint_, XBin::Int2Bin(i + 4), 4);
	memcpy(Varint_ + 4, Varint, i);
	return Varint_;
}

int Protobuf::Int2Varint_len(long long int l)
{
	int i = 0;
	while (l > 127)
	{
		l >>= 7;
		++i;
	}
	return ++i;
}

LPBYTE Protobuf::Field2Key(int Field, ProtobufStruct::ProtobufStructType ProtobufStructType)
{
	return Int2Varint(Field << 3 | static_cast<int>(ProtobufStructType));
}

uint Protobuf::FirstProcess(ProtobufStruct::TreeNode *First)
{
	uint size = 0;
	ProtobufStruct::TreeNode *This = First;
	while (This != nullptr)
	{
		if (This->child != nullptr)
		{
			uint s = FirstProcess(This->child);
			This->Data = Int2Varint(s);
			size += XBin::Bin2Int((byte *)This->Data) - 4;
			size += s;
		}
		else
		{
			switch (This->ProtobufStructType)
			{
			case ProtobufStruct::ProtobufStructType::VARINT:
				This->Data = Int2Varint((long long int)This->Data);
				size += XBin::Bin2Int((byte *)This->Data) - 4;
				break;
			case ProtobufStruct::ProtobufStructType::FIX64:
				size += 8;
				break;
			case ProtobufStruct::ProtobufStructType::LENGTH:
			{
				int len = XBin::Bin2Int((byte *)This->Data) - 4;
				size += Int2Varint_len(len);
				size += len;
			}
			break;
			case ProtobufStruct::ProtobufStructType::FIX32:
				size += 4;
				break;
			}
		}
		This->Field = (long long int)Field2Key(This->Field, This->ProtobufStructType);
		size += XBin::Bin2Int((byte *)This->Field) - 4;
		This = This->brother;
	}
	return size;
}

void Protobuf::SecondProcess(ProtobufStruct::TreeNode *First)
{
	ProtobufStruct::TreeNode *This = First;
	while (This != nullptr)
	{
		SetBin_((LPBYTE)This->Field);
		if (This->child != nullptr)
		{
			SetBin_((LPBYTE)This->Data);
			SecondProcess(This->child);
		}
		else
		{
			switch (This->ProtobufStructType)
			{
			case ProtobufStruct::ProtobufStructType::VARINT:
				SetBin_((LPBYTE)This->Data);
				break;
			case ProtobufStruct::ProtobufStructType::FIX64:
				SetLong((uint64_t)This->Data);
				break;
			case ProtobufStruct::ProtobufStructType::LENGTH:
				SetBin_(Int2Varint(XBin::Bin2Int((byte *)This->Data) - 4));
				SetBin((LPBYTE)This->Data);
				break;
			case ProtobufStruct::ProtobufStructType::FIX32:
				SetInt((uint64_t)This->Data);
				break;
			}
		}
		This = This->brother;
	}
}

LPBYTE Protobuf::Pack(ProtobufStruct::TreeNode *First)
{
	Expansion(FirstProcess(First));
	SecondProcess(First);
	SetLength();
	return GetAll();
}