#pragma once
#include "logger.h"


void Logger::log_element_parameters(std::vector<int> elementIds) {

		this->logElementParameters = true;
		this->logElementParametersIdsArr = elementIds;

}

Logger logger;