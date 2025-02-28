#include "automat.h"

#include "../../visualization/visualizer.h"

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



	void automat::deleteStates(State* state, std::set<State*>& visited)
	{
		if (!state || visited.contains(state)) {return;}
		visited.insert(state);

		for (auto& transition : state->transitions)
		{
			deleteStates(transition.second, visited);
		}

		delete state;
		state = nullptr;
	}

	void automat::clearAuto()
	{
		std::set<State*> visited;
		deleteStates(start, visited);

		start = nullptr;
		accept = nullptr;
	}

}
