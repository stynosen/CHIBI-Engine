//This class can be used to work with bitflags
//It is a wrapper class to use ENUMs as flag parameters.

template<typename ENUM>
class Flag
{
public:
	Flag()
	{
		flagData = 0;
	}

	void SetFlags(int flags)
	{
		flagData = flags;
	}

	bool AddFlag(ENUM flag)
	{
		int newFlag = flagData | flag;
		if (newFlag == flagData)
			return false;
		flagData = newFlag;
		return true;
	}

	bool RemoveFlag(ENUM flag)
	{
		int newFlag = flagData & ~flag;
		if (newFlag == flagData)
			return false;
		flagData = newFlag;
		return true;
	}

	bool HasFlag(ENUM flag)
	{
		return (flagData&flag)!=0;
	}

private:
	int flagData;
};