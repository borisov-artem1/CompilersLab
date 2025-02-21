#include "automat.h"

namespace automat {
	baseAutomat::baseAutomat(State* start, State* end) : start(start), accept(end) {}

	State* baseAutomat::createState() {
		try
		{
			return new State{counter++, {}};
		} catch (const std::bad_alloc& e)
		{
			std::cout << "Error, bad alloc in function createState: " << e.what() << std::endl;
			throw;
		}
	}

	automat baseAutomat::createBaseAutomat(const char symbol) {
		if (symbol == '\0' || std::iscntrl(symbol))
		{
			throw std::invalid_argument("Invalid symbol");
		}
		start = createState();
		accept = createState();

		start->transitions.insert({symbol, accept});
		return {start, accept};
	}
}