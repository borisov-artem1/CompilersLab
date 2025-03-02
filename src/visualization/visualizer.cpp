#include "visualizer.h"

#include <filesystem>
#include <iterator>


namespace automat
{
    void visualizer::exportToDot(State* start, State* accept, const std::string& filename)
    {

        std::string pathToDir;
        if (filename == "NFA")
        {
            pathToDir = "../src/visualization/NFA_images";
        } else if (filename == "DFA")
        {
            pathToDir = "../src/visualization/DFA_images";
        } else
        {
            throw std::invalid_argument("Wrong file name");
        }
        static int counterForNFA = 0;
        static int counterForDFA = 0;
        if (!std::filesystem::exists(pathToDir))
        {
            std::filesystem::create_directory(pathToDir);
        }
        std::string dotPath;
        std::string pngPath;

        if (filename == "NFA")
        {
            dotPath = pathToDir + "/" + filename + std::to_string(counterForNFA) + ".dot";
            pngPath = pathToDir + "/" + filename + std::to_string(counterForNFA) + ".png";
        } else if (filename == "DFA")
        {
            dotPath = pathToDir + "/" + filename + std::to_string(counterForDFA) + ".dot";
            pngPath = pathToDir + "/" + filename + std::to_string(counterForDFA) + ".png";
        }

        std::ofstream file(dotPath);
        if (!file.is_open())
        {
            std::cerr << "Error in function exportToDot" << std::endl;
            throw std::runtime_error("Could not open file " + dotPath);
        }

        file << "digraph Automat {\n";
        file << "   rankdir=LR;\n";
        file << "node [shape=circle];\n";

        file << "  start [shape=none, label=\"start\"];\n";
        file << "  start -> " << start->id << " [style=dashed];\n";

        std::set<State*> visited;
        std::function<void(State*)> graph = [&](State* state)
        {
            if (visited.contains(state)) { return; }
            visited.insert(state);

            if (filename == "DFA" && state->isAccept)
            {
                file << "    " << state->id << " [shape=doublecircle];\n";
            }

            for (const auto& [symbol, nextState] : state->transitions)
            {
                file << "    " << state->id << " -> " << nextState->id
                << " [label=\"" << (symbol == '\0' ? "eps" : std::string(1, symbol)) << "\"];\n";
                graph(nextState);
            }
        };

        graph(start);

        if (accept != nullptr)
        {
            file << "    " << accept->id << " [shape=doublecircle];\n";
        }
        file << "}\n";

        file.close();

        std::string command = "dot -Tpng " + dotPath + " -o " + pngPath;
        system(command.c_str());
        std::filesystem::path toDelete = dotPath;
        std::filesystem::remove(toDelete);
        if (filename == "NFA")
        {
            counterForNFA++;
        } else if (filename == "DFA")
        {
            counterForDFA++;
        }
    }

}