#include "tree_visualization.h"

#include <filesystem>
#include <fstream>
#include <functional>


namespace automat
{
    void tree_visualization::exportTreeToDot(const syntaxTreeNode* node)
    {
        std::string pathToDir = "../src/visualization/tree_visualization";

        if (!std::filesystem::exists(pathToDir))
        {
            std::filesystem::create_directory(pathToDir);
        }
        static int counter = 0;
        std::string dotPath = pathToDir + "/tree" + std::to_string(counter) + ".dot";
        std::string pngPath = pathToDir + "/tree" + std::to_string(counter) + ".png";

        std::ofstream file(dotPath);
        if (!file.is_open())
        {
            throw std::runtime_error("Could not open file " + dotPath);
        }

        file << "digraph tree {\n";
        file << "   rankdir=TB;\n";
        file << "node [shape=circle];\n";

        std::function<void(const syntaxTreeNode*)> visitor = [&](const syntaxTreeNode* root)
        {
            if (!root) return;

            if (root->left)
            {
                file << "    \"" << root << "\" [label=\"" << root->symbol << "\"];\n";
                file << "    \"" << root->left << "\" [label=\"" << root->left->symbol << "\"];\n";
                file << "    \"" << root << "\" -> \"" << root->left << "\";\n";
                visitor(root->left);
            }

            if (root->right)
            {
                file << "    \"" << root->right << "\" [label=\"" << root->right->symbol << "\"];\n";
                file << "    \"" << root << "\" -> \"" << root->right << "\";\n";
                visitor(root->right);
            }
        };

        visitor(node);

        file << "}\n";
        file.close();
        std::string command = "dot -Tpng \"" + dotPath + "\" -o \"" + pngPath + "\"";
        system(command.c_str());
        std::filesystem::path toDelete = dotPath;
        std::filesystem::remove(toDelete);
        counter++;
    }

}
