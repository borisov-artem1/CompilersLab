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
        } else if (filename == "MinDFA")
        {
            pathToDir = "../src/visualization/MinDFA_images";
        } else if (filename == "DFA_from_rgx")
        {
            pathToDir = "../src/visualization/DFA_from_rgx";
        }
        static int counterForNFA = 0;
        static int counterForDFA = 0;
        static int counterForMinDFA = 0;
        static int counterForDFAFromRGX = 0;
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
        } else if (filename == "MinDFA")
        {
            dotPath = pathToDir + "/" + filename + std::to_string(counterForMinDFA) + ".dot";
            pngPath = pathToDir + "/" + filename + std::to_string(counterForMinDFA) + ".png";
        } else if (filename == "DFA_from_rgx")
        {
            dotPath = pathToDir + "/" + filename + std::to_string(counterForDFAFromRGX) + ".dot";
            pngPath = pathToDir + "/" + filename + std::to_string(counterForDFAFromRGX) + ".png";
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

            if ((filename == "DFA" || filename == "MinDFA" || filename == "DFA_from_rgx") && state->isAccept)
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
        } else if (filename == "MinDFA")
        {
            counterForMinDFA++;
        } else if (filename == "DFA_from_rgx")
        {
            counterForDFAFromRGX++;
        }
    }

}