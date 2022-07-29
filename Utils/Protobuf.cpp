#include "Protobuf.h"

Protobuf::VarInt Protobuf::Int2Varint(uint64_t l)
{
    VarInt VarInt;
    VarInt.VarInt = new byte[10];
    while (l > 0)
    {
        VarInt.VarInt[VarInt.Length++] = (l & 0x7F) | 0x80;
        l >>= 7;
    }
}

void Protobuf::Int2Varint(uint64_t l, VarInt *VarInt)
{
    VarInt->VarInt = new byte[10];
    while (l > 0)
    {
        VarInt->VarInt[VarInt->Length++] = (l & 0x7F) | 0x80;
        l >>= 7;
    }
}

uint32_t Protobuf::Calculate(Tree *Tree)
{
    uint32_t Length;
    for (auto i : Tree->Child)
    {
        Length += i.Field.Length;
        switch (i.Type)
        {
        case Type::VARINT:
            Length += ((VarInt *)i.Data)->Length;
            break;
        case Type::BIN:
        case Type::BIN_EX:
        case Type::LPBYTE_EX:
            Length += ((BinData *)i.Data)->LengthEx.Length;
            Length += ((BinData *)i.Data)->Length;
            break;
        case Type::TREE:
            Length += Calculate(&i);
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
    for (auto i : Tree->Child)
    {
        Pack->SetBin_(i.Field.VarInt, i.Field.Length);
        switch (i.Type)
        {
        case Type::VARINT:
            SetVarint(Pack, (VarInt *)i.Data);
            break;
        case Type::BIN:
            SetVarint(Pack, &((BinData *)i.Data)->LengthEx);
            Pack->SetBin(((BinData *)i.Data)->Bin);
            break;
        case Type::BIN_EX:
            SetVarint(Pack, &((BinData *)i.Data)->LengthEx);
            Pack->SetBin(((BinData *)i.Data)->Bin);
            delete[](((BinData *)i.Data)->Bin);
            break;
        case Type::LPBYTE_EX:
            SetVarint(Pack, &((BinData *)i.Data)->LengthEx);
            Pack->SetBin(((BinData *)i.Data)->Bin);
            delete[](((BinData *)i.Data)->Bin - 4);
            break;
        case Type::TREE:
            Pack->SetBin_(i.Length.VarInt, i.Length.Length);
            Recurse(Pack, &i);
            break;
        case Type::FIX32:
            Pack->SetInt((int32_t)i.Data);
            break;
        case Type::FIX64:
            Pack->SetLong((int64_t)i.Data);
            break;
        }
    }
};

void Protobuf::WriteVarint(const uint16_t Field, const uint64_t l)
{
    BaseTree->Child.emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::VARINT), Type::VARINT, [&] -> VarInt *
                                      {VarInt * Data=new VarInt;Int2Varint(l,Data);return Data; }()});
}

void Protobuf::WriteFix32(const uint16_t Field, const int32_t i)
{
    BaseTree->Child.emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::FIX32), Type::FIX32, (void *)i});
}

void Protobuf::WriteFix64(const uint16_t Field, const int64_t l)
{
    BaseTree->Child.emplace_back(Tree{GetField(Field, ProtobufStruct::ProtobufStructType::FIX64), Type::FIX64, (void *)l});
}

void Protobuf::WriteStr(const uint16_t Field, const char *str)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=strlen(str);Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)str;return Data; }()});
}

void Protobuf::WriteStr_(const uint16_t Field, char *str)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=strlen(str);Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)str;return Data; }()});
}

void Protobuf::WriteBin(const uint16_t Field, const byte *bin, uint32_t Length)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=Length;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=(byte*)bin;return Data; }()});
}

void Protobuf::WriteBin_(const uint16_t Field, byte *bin, uint32_t Length)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=Length;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin;return Data; }()});
}

void Protobuf::WriteBin(const uint16_t Field, const LPBYTE bin)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=XBin::Bin2Int(bin) - 4;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin + 4;return Data; }()});
}

void Protobuf::WriteBin_(const uint16_t Field, LPBYTE bin)
{
    BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::BIN_EX,
        [&] -> BinData *
        {BinData * Data=new BinData;Data->Length=XBin::Bin2Int(bin) - 4;Int2Varint(Data->Length,&Data->LengthEx); Data->Bin=bin + 4;return Data; }()});
}

void Protobuf::WriteTree(const uint16_t Field, Tree *Tree)
{
    Tree->Field = GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH);
    BaseTree->Child.emplace_back(Tree);
}

void Protobuf::StepIn(const byte Field)
{
    BaseTree = &BaseTree->Child.emplace_back(Tree{
        GetField(Field, ProtobufStruct::ProtobufStructType::LENGTH),
        Type::TREE, BaseTree});
}

void Protobuf::StepOut()
{
    BaseTree = BaseTree->Superior;
}

Protobuf::Tree *Protobuf::GetTree()
{
    return BaseTree;
}

LPBYTE Protobuf::Pack()
{
    ::Pack Pack(Calculate(BaseTree) + 4);
    Recurse(&Pack, BaseTree);
    Pack.SetLength();
    return Pack.GetAll();
}

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

void UnProtobuf::StepIn(const byte Field)
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
        uint32_t len = GetVarint();
        char8_t *str = new char8_t[len + 1];
        memcpy(str, List->UnPack.GetStr(len), len);
        str[len] = 0;
        return str;
    }
    return nullptr;
}

uint32_t UnProtobuf::GetBin(byte *&bin, const byte Field)
{
    if (SkipToField(Field) == ProtobufStruct::ProtobufStructType::LENGTH)
    {
        uint32_t len = GetVarint();
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
        uint32_t len = GetVarint();
        LPBYTE bin = new byte[len + 4];
        memcpy(bin, XBin::Int2Bin(len + 4), len);
        memcpy(bin + 4, List->UnPack.GetBin(len), len);
        return bin;
    }
    return (LPBYTE) "\0\0\0\4";
}