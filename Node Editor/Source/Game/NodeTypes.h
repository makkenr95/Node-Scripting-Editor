#pragma once
#include <cassert>
#include "imgui.h"

/**
 * Defines for all DataTypes that can exist in the Graph.
 * This also specifies the type of a Pin on a Node.
 */
enum class DataType
{
	Bool,
	Int,
	Float,
	String,

	FVector,
	// When adding new types do it BEFORE this line
	// and DO NOT change their order.
	Variable = 253,
	Exec = 254,
	Unknown = 255,
};

/**
 * Pins should have different colors so it's easy for the user to identify
 * what goes where. When adding new types it's a good idea to give them a
 * unique color as well. They go in this struct.
 */
struct DataTypeColor
{
	static ImColor Get(DataType aType)
	{
		switch (aType)
		{
			case DataType::Bool:		return ImColor(220, 48, 48);
			case DataType::Int:			return ImColor(68, 201, 156);
			case DataType::Float:		return ImColor(147, 226, 74);
			case DataType::String:		return ImColor(124, 21, 153);
			case DataType::FVector:		return ImColor(255, 200, 0);
			// Add your type above with some fancy color if you don't want
			// it to just appear as white.
			case DataType::Exec:		return ImColor(255, 255, 255);
			case DataType::Unknown:		return ImColor(255, 0, 0);
			default:					return ImColor(100, 100, 100);
		}
	}
};

/**
 * If a pin is an Input or Output pin.
 * Not a bool for readability.
 */
enum class PinDirection
{
	PinDirection_IN,
	PinDirection_OUT
};

/**
 * A data pointer. Responsible for containing data held by node pins and graph variables.
 */
struct DataPtr
{
	/**
	 * Creates a new data pointer of the specified type and the specified size.
	 * @param aType The DataType of this container.
	 * @param someSize The size of the data. This only has an effect when creating
	 * strings or raw pointers.
	 * @returns A new Data container of the specified type and size.
	 */
	static DataPtr Create(DataType aType, size_t someSize = 1)
	{
		DataPtr result;

		switch(aType)
		{
		case DataType::Bool:
			result.Ptr = new bool();
			result.Size = sizeof(bool);
			break;
		case DataType::Int:
			result.Ptr = new int();
			result.Size = sizeof(int);
			break;
		case DataType::Float:
			result.Ptr = new float();
			result.Size = sizeof(float);
			break;
		case DataType::String:
			result.Ptr = new char[someSize]();
			result.Size = someSize;
			break;

		// Add your own types above this line.
		case DataType::Exec:
		case DataType::Unknown:
		case DataType::Variable:
			assert(false && "You cannot create data pointers of non-quantifiable types!");
			break;
		default:
			assert(false && "Unknown data type! Do you need to update NodeTypes.h?");
			break;
		}

		return result;
	}

	/*****************************************************************************
	 *
	 * You shouldn't need to modify anything below this line.
	 *
	 ****************************************************************************/

	// Use the DataPtr::Create method to populate.
	DataPtr() = default;
	
	__forceinline size_t GetSize() const { return Size; }

	template<class T>
	__forceinline T Get()
	{
#if _DEBUG
		assert(Ptr);
#endif
		if (!Ptr)
		{
			return T();
		}
		return *static_cast<T*>(Ptr);
	}

	template<>
	__forceinline std::string Get()
	{
#if _DEBUG
		assert(Ptr);
#endif
		if(!Ptr)
		{
			return std::string();
		}
		return std::string(static_cast<char*>(Ptr));
	}

	template<typename T>
	__forceinline const T* GetPtr() const
	{
		return (T*)Ptr;
	}

	bool operator!() const
	{
		return !Ptr;
	}

	operator bool() const
	{
		return Ptr;
	}

	bool operator== (const DataPtr& anOther) const
	{
		return Ptr == anOther.Ptr && Size == anOther.Size;
	}

	bool operator== (const std::nullptr_t) const
	{
		return Ptr == nullptr;
	}

	bool operator!=(const std::nullptr_t) const
	{
		return Ptr != nullptr;
	}

	bool operator!=(const DataPtr& anOther) const
	{
		return Ptr != anOther.Ptr || Size != anOther.Size;
	}

	// Only internal classes may mess with the pointer.
	// We do NOT want to allow external things to modify
	// it in any fashion.
	friend class GraphNodeBase;
	friend class GraphManager;
	friend class GraphVariable;
	friend struct Payload;

private:
	void* Ptr = nullptr;
	size_t Size = 0;
};

/**
 * Used to provide input data for a Start node that requires it.
 * Example will appear in F3 :).
 */
struct Payload
{
private:
	std::vector<void*> myData;

public:
	Payload() = default;

	template<typename T>
	void AddData(T someData)
	{
		myData.push_back(new T());
		memcpy(myData[myData.size() - 1], &someData, sizeof(someData));
	}

	template<>
	void AddData(std::string& someData)
	{
		myData.push_back(new char[someData.size()]());
		memcpy(myData[myData.size() - 1], someData.c_str(), someData.length());
	}

	size_t Size() const { return myData.size(); }

	template<typename T>
	T GetEntry(unsigned int anIndex) const
	{
		assert(myData.size() > anIndex);
		return *static_cast<const T*>(myData[anIndex]);
	}
};