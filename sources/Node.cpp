#include "Node.hpp"

namespace ariel {

    Node::Node(std::string pos, Node *dad) {
        this->dad = dad;
        this->position = pos;
        this->sons = std::vector<Node *>();
    }

    void Node::addSon(Node *son) {
        sons.push_back(son);
    }

    void Node::replaceDad(Node *dad) {
        this->dad = dad;
    }

    void Node::replacePosition(std::string newPos){
        this->position = newPos;
    }

    std::vector<Node *>& Node::get_sons(){
        return sons;
    }

    std::string& Node::get_pos() {
        return position;
    }

    Node::~Node() {}

}
