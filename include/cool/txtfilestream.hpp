#pragma once
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <string_view>

namespace cool {

class Line {
	public:
		std::size_t size() const {return m_line.size();}
		void readNextLine(std::istream& str) {
			std::getline(str, m_line);
		}
		
		std::string operator* () const {
			return m_line;
		}

	private:
		std::string m_line;
};

std::istream& operator>> (std::istream& str, Line& line) {
	line.readNextLine(str);
	return str;
}

class FileIterator {
	public:
		using value_type = Line;
		using pointer = value_type*;
		using reference = value_type&;
		using iterator_category = std::input_iterator_tag;
		using difference_type = std::size_t;

		FileIterator(std::istream& str): m_str(str.good() ? &str : NULL) {
			++(*this);
		}
		FileIterator(): m_str(NULL) {}

		FileIterator& operator++() {
			if (m_str) {
				if (!((*m_str) >> m_line)) {
					m_str = NULL;
				}
			}
			return *this;
		}
		
		FileIterator operator++(int) {
			FileIterator temp(*this);
			++(*this);
			return temp;
		}

		Line const& operator* () const {
			return m_line;
		}

		Line const* operator-> () const {
			return &m_line;
		}	

		bool operator== (FileIterator const& rhs) {
			return ((this == &rhs) || (this->m_str == NULL) && (rhs.m_str == NULL));
		}

		bool operator!= (FileIterator const& rhs) {
			return !((*this) == rhs);
		}
	private:
		std::istream* m_str;
		Line m_line;	
};

class IteratorRange {
	private:
		std::istream& stream;
	public:
		IteratorRange(std::istream& str):stream(str) {
		}
		
		FileIterator begin() const {
			return FileIterator{stream};
		}

		FileIterator end() const {
			return FileIterator{};
		}
};

}// cool
