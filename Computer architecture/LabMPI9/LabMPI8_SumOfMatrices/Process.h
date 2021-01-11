#pragma once

class Process
{
private:
	int rank;
	int processNumber;
public:
	static const int MasterRank = 0;

	Process(int argc, char **argv);
	virtual ~Process();

	int GetRank() const;
	int GetProcessNumber() const;
	bool IsMaster() const;
};