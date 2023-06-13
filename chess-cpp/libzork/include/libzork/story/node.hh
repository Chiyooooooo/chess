#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../variables/action.hh"
#include "../variables/condition.hh"

namespace fs = std::filesystem;

namespace story
{
    struct choice;
    class Node
    {
    public:
        Node(const std::string& name, const fs::path& script_path);

        const std::string& get_name() const;
        const std::string& get_text() const;

        const Node* make_choice(std::size_t index) const;
        std::vector<std::string>
        list_choices(bool check_conditions = true) const;
        void add_choice(const Node* other, const std::string& text,
                        const std::vector<Condition>& conditions = {},
                        const std::vector<Action>& operations = {});

    private:
        std::string name_;
        fs::path script_path_;
        std::string txt_;
        std::vector<choice> listv;
    };

    struct choice
    {
        choice(const Node* node, const std::string& txt);

        const Node* get_node() const;
        const std::string& get_txt() const;
        std::string txt;
        const Node* node;
    };

} // namespace story
