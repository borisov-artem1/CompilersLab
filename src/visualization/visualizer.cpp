#include "visualizer.h"
#include <iterator>


namespace automat
{
    void visualizer::exportToDot(const automat& Automat, const std::string& filename)
    {
        std::ofstream file(filename);

        if (!file.is_open())
        {
            std::cerr << "Error in function exportToDot" << std::endl;
            throw std::runtime_error("Could not open file " + filename);
        }

        file << "digraph Automaton {\n";
        file << "   rankdir=LR;\n";
        file << "node [shape=circle];\n";

        file << "  start [shape=none, label=\"start\"];\n";
        file << "  start -> " << Automat.start->id << " [style=dashed];\n";

        std::set<State*> visited;
        std::function<void(State*)> graph = [&](State* state)
        {
            if (visited.contains(state)) { return; }
            visited.insert(state);

            for (const auto& [symbol, nextState] : state->transitions)
            {
                file << "    " << state->id << " -> " << nextState->id
                << " [label=\"" << (symbol == '\0' ? "eps" : std::string(1, symbol)) << "\"];\n";
                graph(nextState);
            }
        };

        graph(Automat.start);

        file << "    " << Automat.accept->id << " [shape=doublecircle];\n";
        file << "}\n";

        file.close();
    }



}