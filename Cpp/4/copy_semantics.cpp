#include <cstdio>
#include <cstring>
#include <stdexcept>

struct SimpleString {
	SimpleString(size_t max_size)
		: max_size{ max_size },
			length{} {
		buffer = new char[max_size];
		buffer[0] = 0;
	}

	// Copy constructor
	SimpleString (const SimpleString& other) 
		: max_size{ other.max_size },
		buffer{ new char[other.max_size] },
		length{ other.length } {
			std::strncpy(buffer, other.buffer, max_size);
	}
	
	// Copy assignment operator	
	SimpleString& operator=(const SimpleString& other) {
		if  (this == &other) return *this;
		const auto new_buffer = new char[other.max_size];
		delete[] buffer;
		buffer = new_buffer;
		length = other.length;
		max_size = other.max_size;
		std::strncpy(buffer, other.buffer, max_size);
		return *this;
	}

	void print(const char* tag) const {
		printf("%s: %s", tag, buffer);
	}

	bool append_line(const char* x) {
		const auto x_len = strlen(x);
		if (x_len + length + 2 > max_size) return false;
		std::strncpy(buffer + length, x, max_size - length);
		length += x_len;
		buffer[length++] = '\n';
		buffer[length] = 0;
		return true;
	}

	~SimpleString() {
		delete[] buffer;
	}
			
	private:
		size_t max_size;
		char* buffer;
		size_t length;
};

int main() {
	SimpleString a { 50 };
	a.append_line("This is the original object or its copy");
	a.print("A: ");
	SimpleString b { 50 };
	
	SimpleString a_deep_copy{ a };
	a_deep_copy.append_line("This is a deep copy");
	a_deep_copy.print("B: ");

	b = a;
	b.print("C: ");

	return 0;
}
