#pragma once

template<class T>
class TArray
{
	friend class FString;

public:
	TArray(){ Count = Max = 0; };

	T& operator[](int i) const { return Data[i];};

	T* Data;
	inline int Num() const
	{
		return Count;
	};
	unsigned int Count;
	unsigned int Max;
};