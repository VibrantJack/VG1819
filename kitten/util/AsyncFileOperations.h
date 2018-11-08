#pragma once

#include "kitten\K_Job.h"
#include <tuple>
#include <list>
#include <string>

namespace kitten
{
	class K_Instance;

	class AsyncFileOperations
	{
		friend class K_Instance;
	private:
		AsyncFileOperations();
		~AsyncFileOperations();
		static AsyncFileOperations* sm_instance;

		K_Job* m_fileSavingRoutine;
		std::list<std::tuple<std::string, bool, std::string>> m_filesToSave;

		void fileOperationCycle(std::tuple<int> p_params);

		static void startService();
		static void stopService();
	public:
		static void saveToFile(const char* p_pathToFile, bool p_shouldOverwrite, const char* p_contents);
	};
}
