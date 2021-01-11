#pragma once

class Process
{
private:
	int rank;
	int processNumber;
	int vectorLength;
public:
	static const int MasterRank = 0;

	Process(int argc, char **argv);
	virtual ~Process();

	int GetRank() const;
	int GetProcessNumber() const;
	int GetVectorLength() const;
	bool IsMaster() const;
};