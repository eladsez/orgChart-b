#include "Node.hpp"

namespace ariel {

    Node::Node(std::string pos): position(std::move(pos)){}

    void Node::addSon(Node *son) {
        sons.push_back(son);
    }

    void Node::replacePosition(std::string newPos){
        this->position = std::move(newPos);
    }

    std::vector<Node *>& Node::get_sons(){
        return sons;
    }

    std::string& Node::get_pos() {
        return position;
    }

    Node::~Node() {}

}
