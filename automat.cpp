#include "automat.h"

namespace automat {
	baseAutomat::baseAutomat(State* start, State* end) : startState(start), finalState(end) {}

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

	automat baseAutomat::createBaseAutomat(const char symbol) { // TODO: must fix bugs with shared pointers
		if (symbol == '\0' || std::iscntrl(symbol))
		{
			throw std::invalid_argument("Invalid symbol");
		}
		std::unique_ptr<State> start, accept;

		try
		{
			start.reset(this->createState());
			accept.reset(this->createState());
		} catch (const std::bad_alloc& e)
		{
			std::cout << "Error, bad alloc in function createBaseAutomat: " << e.what() << std::endl;
			throw;
		}

		start->transitions.insert({symbol, accept.get()});
		return {start.get(), accept.get()};
	}
}