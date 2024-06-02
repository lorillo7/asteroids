#pragma once

#include <vector>
#include <string>
#include <optional>
#include <iostream>

class ErrorManager {
public:
	explicit ErrorManager() = default;
	~ErrorManager() = default;

	void addError(const std::string& i_string);
	std::optional<std::string> getError(const std::size_t i) const;
	bool hasError() const;
	std::size_t getErrorCount() const;
	
	void print() const;

private:
	std::vector<std::string> m_errorMsgs;
};