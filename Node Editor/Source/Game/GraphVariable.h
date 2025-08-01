#pragma once
#include "NodeTypes.h"
#include "UID.h"

class GraphVariable
{
	friend class GraphManager;

	UID myUID;
	std::string myName;
	// The currently held value, changed by the graphs flow.
	DataPtr myValue;
	// The value we have at the start of execution.
	DataPtr myStartValue;
	DataType myType;
	size_t mySize;

	GraphVariable() = default;

	GraphVariable(std::string& aName, DataType aType, DataPtr aDataPointer, bool aCreateNewUID = true)
	{
		myUID = UID(aCreateNewUID);
		myName = aName;
		myType = aType;
		myStartValue = DataPtr::Create(myType);
		memcpy(myStartValue.Ptr, &aDataPointer.Ptr, aDataPointer.Size);
	}

public:

	template<typename T>
	GraphVariable(std::string& aName, DataType aType, T someData, bool aCreateNewUID = true)
	{
		myUID = UID(aCreateNewUID);
		myName = aName;
		myType = aType;
		myStartValue = DataPtr::Create(myType);
		memcpy(myStartValue.Ptr, &someData, sizeof(T));
	}

	template<>
	GraphVariable(std::string& aName, DataType aType, std::string someData, bool aCreateNewUID)
	{
		myUID = UID(aCreateNewUID);
		myName = aName;
		myType = aType;
		myStartValue = DataPtr::Create(myType, someData.length() + 1);
		memcpy(myStartValue.Ptr, someData.c_str(), someData.length());
	}

	void Initialize()
	{
		if(!myValue)
		{
			myValue = DataPtr::Create(myType, sizeof(myStartValue));
			memcpy(myStartValue.Ptr, &myStartValue, sizeof(myStartValue));
		}
	}

	DataType GetType() { return myType; }

	const UID GetUID() { return myUID; }

	template<typename T>
	void Set(T someNewData)
	{
		memcpy(myValue, &someNewData, sizeof(T));
	}

	template<>
	void Set(std::string someNewData)
	{
		char* ptr = new char[someNewData.length() + 1]();
		memcpy(ptr, someNewData.c_str(), someNewData.length());
	}

	template<typename T>
	T Get()
	{
		return *((T*)myValue);
	}

	template<>
	std::string Get()
	{
		return std::string(myValue.GetPtr<char>());
	}

	template<typename Writer>
	void Serialize(Writer& writer) const
	{
		writer.StartObject();
		writer.Key("UID");
		writer.Int(myUID.ToUInt());
		writer.Key("Name");
		writer.String(myName.c_str());
		writer.Int((int)myType);

		writer.Key("DATA");
		std::vector<char> data((char*)myStartValue.Ptr, (char*)myStartValue.Ptr + myStartValue.Size);
		writer.StartArray();
		for(auto& d : data)
		{
			writer.Int(d);
		}
		writer.EndArray();
		writer.Key("DATA_TYPE");
		writer.Uint((unsigned int)myType);

		writer.EndObject();
	}
};
