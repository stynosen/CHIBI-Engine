//!This class can be used to work with bit flags
/*!It is a wrapper class to use ENUMs as flag parameters.*/
template<typename ENUM>
class Flag
{
public:
	Flag()
	{
		flagData = 0;
	}

	//!Set the flags to a certain combination of flags
	void SetFlags(int flags)
	{
		flagData = flags;
	}

	//!Add a flag
	bool AddFlag(ENUM flag)
	{
		int newFlag = flagData | flag;
		if (newFlag == flagData)
			return false;
		flagData = newFlag;
		return true;
	}

	//!Remove a flag
	bool RemoveFlag(ENUM flag)
	{
		int newFlag = flagData & ~flag;
		if (newFlag == flagData)
			return false;
		flagData = newFlag;
		return true;
	}

	//!Check if the value has a flag
	bool HasFlag(ENUM flag)
	{
		return (flagData&flag)!=0;
	}

private:
	//!The current flag combination
	int flagData;
};