#include "Protobuf.h"

Protobuf::VarInt Protobuf::Int2Varint(uint64_t l)
{
    VarInt VarInt{new byte[10], 0};
    while (l >= 0x80)
    {
        VarInt.VarInt[VarInt.Length++] = (l & 0x7F) | 0x80;
        l >>= 7;
    }
    VarInt.VarInt[VarInt.Length++] = l;
    return VarInt;
}

void Protobuf::Int2Varint(uint64_t l, VarInt *VarInt)
{
    VarInt->VarInt = new byte[10];
    while (l >= 0x80)
    {
        VarInt->VarInt[VarInt->Length++] = (l & 0x7F) | 0x80;
        l >>= 7;
    }
    VarInt->VarInt[VarInt->Length++] = l;
}

uint32_t Protobuf::Calculate(Tree *Tree)
{
    uint32_t Length = 0;
    for (int i = 0; i < Tree->Child->size(); ++i)
    {
        Length += (*Tree->Child)[i].Field.Length;
        switch ((*Tree->Child)[i].Type)
        {
        case Type::VARINT:
            Length += ((VarInt *)(*Tree->Child)[i].Data)->Length;
            break;
        case Type::BIN:
        case Type::BIN_EX:
        case Type::LPBYTE_EX:
            Length += ((BinData *)(*Tree->Child)[i].Data)->LengthEx.Length;
            Length += ((BinData *)(*Tree->Child)[i].Data)->Length;
            break;
        case Type::TREE:
        {
            uint32_t Length_ = Calculate(&(*Tree->Child)[i]);
            Length += Length_;
            Int2Varint(Length_, (*Tree->Child)[i].Length = new VarInt);
            Length += (*Tree->Child)[i].Length->Length;
        }
        break;
        case Type::FIX32:
            Length += 4;
            break;
        case Type::FIX64:
            Length += 8;
            break;
        }
    }
    return Length;
}

void Protobuf::Recurse(::Pack *Pack, Tree *Tree)
{
    for (int i = 0; i < Tree->Child->size(); ++i)
    {
        SetVarint(Pack, &(*Tree->Child)[i].Field);
        switch ((*Tree->Child)[i].Type)
        {
        case Type::VARINT:
            SetVarint(Pack, (VarInt *)(*Tree->Child)[i].Data);
            delete (VarInt *)(*Tree->Child)[i].Data;
            break;
        case Type::BIN:
            SetVarint(Pack, &((BinData *)(*Tree->Child)[i].Data)->LengthEx);
            Pack->SetBin(((BinData *)(*Tree->Child)[i].Data)->Bin, ((BinData *)(*Tree->Child)[i].Data)->Length);
            delete[](BinData *)(*Tree->Child)[i].Data;
            break;
        case Type::BIN_EX:
            SetVarint(Pack, &((BinData *)(*Tree->Child)[i].Data)->LengthEx);
            Pack->SetBin(((BinData *)(*Tree->Child)[i].Data)->Bin, ((BinData *)(*Tree->Child)[i].Data)->Length);
            delete[](((BinData *)(*Tree->Child)[i].Data)->Bin);
            delete (BinData *)(*Tree->Child)[i].Data;
            break;
        case Type::LPBYTE_EX:
            SetVarint(Pack, &((BinData *)(*Tree->Child)[i].Data)->LengthEx);
            Pack->SetBin(((BinData *)(*Tree->Child)[i].Data)->Bin, ((BinData *)(*Tree->Child)[i].Data)->Length);
            delete[](((BinData *)(*Tree->Child)[i].Data)->Bin - 4);
            delete (BinData *)(*Tree->Child)[i].Data;
            break;
        case Type::TREE:
            SetVarint(Pack, (*Tree->Child)[i].Length);
            Recurse(Pack, &(*Tree->Child)[i]);
            delete (*Tree->Child)[i].Length;
            delete (*Tree->Child)[i].Child;
            break;
        case Type::FIX32:
            Pack->SetInt(*(int32_t *)(*Tree->Child)[i].Data);
            delete (int32_t *)(*Tree->Child)[i].Data;
            break;
        case Type::FIX64:
            Pack->SetLong(*(int64_t *)(*Tree->Child)[i].Data);
            delete (int64_t *)(*Tree->Child)[i].Data;
            break;
        }
    }
};

void Protobuf::WriteVarint(const uint32_t Field, const uint64_t l)
{
    List->BaseTree->Child->emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::VARINT), Type::VARINT, [&] -> VarInt *
                                             {VarInt * Data=new VarInt;Int2Varint(l,Data);return Data; }()});
}

void Protobuf::WriteFix32(const uint32_t Field, const int32_t i)
{
    List->BaseTree->Child->emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::FIX32), Type::FIX32, [&] -> void *
                                             {int32_t *i_ = new int32_t;*i_=i; return i_; }()});
}

void Protobuf::WriteFix64(const uint32_t Field, const int64_t l)
{
    List->BaseTree->Child->emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::FIX64), Type::FIX64, [&] -> void *
                                             {int64_t *l_ = new int64_t;*l_=l; return l_; }()});
}

void Protobuf::WriteStr(const uint32_t Field, const char8_t *str)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=strlen((char*)str);Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)str;return Data; }()});
}

void Protobuf::WriteStr_(const uint32_t Field, char8_t *str)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=strlen((char*)str);Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)str;return Data; }()});
}

void Protobuf::WriteBin(const uint32_t Field, const byte *bin, uint32_t Length)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=Length;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)bin;return Data; }()});
}

void Protobuf::WriteBin_(const uint32_t Field, byte *bin, uint32_t Length)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=Length;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin;return Data; }()});
}

void Protobuf::WriteBin(const uint32_t Field, const LPBYTE bin)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=XBin::Bin2Int(bin) - 4;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin + 4;return Data; }()});
}

void Protobuf::WriteBin_(const uint32_t Field, LPBYTE bin)
{
    List->BaseTree->Child->emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=XBin::Bin2Int(bin) - 4;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin + 4;return Data; }()});
}

void Protobuf::StepIn(const uint32_t Field)
{
    List->BaseTree->Child->emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH), Type::TREE});
    List = new LinkList{&List->BaseTree->Child->back(), List};
    List->BaseTree->Child = new std::vector<Tree>;
}

void Protobuf::StepOut()
{
    LinkList *tmp = List->Superior;
    delete List;
    List = tmp;
}

LPBYTE Protobuf::Pack()
{
    ::Pack Pack(Calculate(List->BaseTree) + 4, true);
    Recurse(&Pack, List->BaseTree);
    List->BaseTree->Child->resize(0);
    Pack.SetLength();
    return Pack.GetAll();
}

uint32_t Protobuf::Pack(byte *&Bin)
{
    ::Pack Pack(Calculate(List->BaseTree));
    Recurse(&Pack, List->BaseTree);
    List->BaseTree->Child->resize(0);
    return Pack.GetAll(Bin);
}

uint64_t UnProtobuf::GetVarint()
{
    uint64_t l = 0;
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

ProtobufStruct::ProtobufStructType UnProtobuf::SkipToField(const uint32_t Field)
{
    while (true)
    {
        uint32_t key = GetVarint();
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
    uint32_t key = GetVarint();
    List->UnPack = UnPack;
    return key >> 3;
}

void UnProtobuf::StepIn(const uint32_t Field)
{
    if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
    {
        uint32_t len = GetVarint();
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

uint64_t UnProtobuf::GetVarint(const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::VARINT)
            return GetVarint();
    }
    catch (...)
    {
        return 0;
    }
}

char8_t *UnProtobuf::GetStr(const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
        {
            uint32_t len = GetVarint();
            char8_t *str = new char8_t[len + 1];
            memcpy(str, List->UnPack.GetStr(len), len);
            str[len] = 0;
            return str;
        }
    }
    catch (...)
    {
        return nullptr;
    }
}

uint32_t UnProtobuf::GetBin(byte *&bin, const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
        {
            uint32_t len = GetVarint();
            bin = new byte[len];
            memcpy(bin, List->UnPack.GetBin(len), len);
            return len;
        }
    }
    catch (...)
    {
        return 0;
    }
}

LPBYTE UnProtobuf::GetBin(const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
        {
            uint32_t len = GetVarint();
            LPBYTE bin = new byte[len + 4];
            memcpy(bin, XBin::Int2Bin(len + 4), len);
            memcpy(bin + 4, List->UnPack.GetBin(len), len);
            return bin;
        }
    }
    catch (...)
    {
        return nullptr;
    }
}

int32_t UnProtobuf::GetFix32(const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::FIX32)
            return (int32_t)List->UnPack.GetInt();
    }
    catch (...)
    {
        return 0;
    }
}

int64_t UnProtobuf::GetFix64(const uint32_t Field)
{
    try
    {
        if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::FIX64)
            return (int32_t)List->UnPack.GetLong();
    }
    catch (...)
    {
        return 0;
    }
}