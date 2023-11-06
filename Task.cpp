#include "Task.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>

void SaveTasks(const std::vector<Task>& task, const std::string file)
{
	std::ofstream out_file (file);
	out_file << task.size();

	for (const Task& task : task)
	{
		std::string descript = task.descr;
		std::replace(descript.begin(), descript.end(), ' ', '_');

		out_file << "\n" << descript << " " << task.done;
	}
}

std::vector<Task> GetTasks(const std::string file)
{
	std::vector <Task> tasks;
	std::ifstream in_file(file);

	int numOfTasks;
	in_file >> numOfTasks;

	for (int i = 0; i < numOfTasks; i++)
	{
		std::string descript;
		bool done;

		in_file >> descript >> done;
		std::replace(descript.begin(), descript.end(), '_', ' ');
		tasks.push_back(Task{ descript, done });
	}

	return tasks;
}
