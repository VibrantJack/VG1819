#include "AsyncFileOperations.h"
#include "kitten\K_JobManager.h"
#include <functional>
#include <iostream>
#include <fstream>
#include <ostream>
#include <cassert>

namespace kitten
{
	AsyncFileOperations* AsyncFileOperations::sm_instance = nullptr;

	AsyncFileOperations::AsyncFileOperations()
	{
		std::function<void(std::tuple<int>)> func = BIND_FUNC(AsyncFileOperations, fileOperationCycle);
		m_fileSavingRoutine = K_JobManager::createJob<int>(func, std::make_tuple(0), true);
	}

	AsyncFileOperations::~AsyncFileOperations()
	{
		//We NEED to blocking stop because the coroutine uses member variables. If we are deleted,
		//the routine will still run and try to access our now invalid variables until it gets deleted.

		//The coroutine COULD be changed to take the files to save as parameters, and this could be done
		//asynchronously with K_JobManager::deleteJob() !
		m_fileSavingRoutine->stop();
	}

	void AsyncFileOperations::startService()
	{
		assert(sm_instance == nullptr);
		sm_instance = new AsyncFileOperations();
	}

	void AsyncFileOperations::stopService()
	{
		assert(sm_instance != nullptr);
		delete sm_instance;
		sm_instance = nullptr;
	}

	void AsyncFileOperations::saveToFile(const char* p_pathToFile, bool p_shouldOverwrite, const char* p_contents)
	{
		sm_instance->m_filesToSave.push_back(std::make_tuple(std::string(p_pathToFile), p_shouldOverwrite, std::string(p_contents)));
	}

	void AsyncFileOperations::fileOperationCycle(std::tuple<int> p_params)
	{
		while (!m_filesToSave.empty())
		{
			auto toSave = *m_filesToSave.begin();
			m_filesToSave.pop_front();

			std::string filePath = std::get<0>(toSave);
			bool shouldOverwrite = std::get<1>(toSave);
			std::string fileContents = std::get<2>(toSave);

			if (!shouldOverwrite)
			{
				//check if  file exists before saving
				std::ifstream in(filePath);
				if (in.good()) // file exists
				{
					int fileNameAdditionalSuffix = 0;
					while (std::ifstream(filePath + std::to_string(fileNameAdditionalSuffix)).good())
					{
						++fileNameAdditionalSuffix;
					}
					filePath += std::to_string(fileNameAdditionalSuffix);
				}
			}

			std::ofstream outStream(filePath);
			outStream << fileContents;
			outStream.close();
		}
	}
}
