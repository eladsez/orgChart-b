#ifndef ORGCHART_A_NODE_H
#define ORGCHART_A_NODE_H

#include <iostream>
#include <vector>
#include <string>

namespace ariel {

    class Node {
    private:
        std::string position;
        std::vector<Node *> sons;

    public:
        Node(std::string pos);

        Node(Node& node) = default;

        Node(Node&& node) = default;

        void addSon(Node *son);

        void replacePosition(std::string newPos);

        std::vector<Node *> &get_sons();

        std::string &get_pos();

        Node& operator=(const Node &node) = default;
        Node& operator=(Node &&node) = default;

        ~Node();
    };
}


#endif //ORGCHART_A_NODE_H
