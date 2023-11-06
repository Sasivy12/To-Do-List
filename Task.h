#pragma once
#include <vector>
#include <string>

class Task
{
public:
	std::string descr;
	bool done;
};

void SaveTasks(const std::vector<Task>& task, const std::string file);
std::vector<Task> GetTasks(const std::string file);
