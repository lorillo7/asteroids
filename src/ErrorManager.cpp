#include "../headers/ErrorManager.hpp"

void ErrorManager::addError(const std::string& i_string) {
	m_errorMsgs.push_back(i_string);
}

std::optional<std::string> ErrorManager::getError(const std::size_t i) const {
	try {
		return m_errorMsgs.at(i);
	} catch(const std::out_of_range& e) {
		return {};
	}
}

bool ErrorManager::hasError() const { return m_errorMsgs.size(); }

std::size_t ErrorManager::getErrorCount() const { return m_errorMsgs.size(); }

void ErrorManager::print() const {
	std::cerr << "The folowing error(s) occured:\n";
	for (const std::string& e : m_errorMsgs)
		std::cerr << e << '\n';
}