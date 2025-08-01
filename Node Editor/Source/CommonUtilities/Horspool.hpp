#pragma once
#include <string>

namespace CommonUtilities
{
	namespace CU = CommonUtilities;

	inline int Horspool(const std::string& aNeedle, const std::string& aHaystack)
	{
		if (aNeedle == "" || aHaystack == "")
		{
			return -1;
		}
		int table[255];

		const int needleLength = aNeedle.length();
		const int haystackLength = aHaystack.length();
		int count;

		for (count = 0; count < 255; count++)
		{
			table[count] = needleLength;
		}

		for (int j = 0; j < needleLength - 1; j++)
		{
			table[static_cast<unsigned char>(aNeedle[j])] = needleLength - 1 - j;
		}

		count = needleLength - 1;

		while (count <= haystackLength - 1)
		{
			int countCheck = 0;
			while (countCheck <= needleLength - 1 && aNeedle[needleLength - 1 - countCheck] == aHaystack[count -
				countCheck])
			{
				countCheck++;
			}

			if (countCheck == needleLength)
			{
				return count - needleLength + 1;
			}

			count = count + table[static_cast<unsigned char>(aHaystack[count])];
		}
		return -1;
	}
}
