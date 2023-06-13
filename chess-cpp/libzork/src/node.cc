#include "../include/libzork/story/node.hh"

// namespace story

story::choice::choice(const Node* node, const std::string& txt)
    : node(node)
    , txt(txt)
{}

const story::Node* get_node()
{
    return node;
}

const std::string& get_txt()
{
    return txt;
}

story::Node::Node(const std::string& name, const fs::path& script_path)
{
    name_ = name;
    script_path = script_path;
    listv = std::vector<choice>();

    std::string txt;
    std::ifstream file(script_path.string());
    if (file.is_open())
    {
        std::ostringstream os;
        os << file.rdbuf();
        txt = os.str();
    }
} /*
         while (file)
         {
             std::getline(file, str);
         }
         text_ = str;
         name_ = name;
         script_path_ = script_path;
         listv = std::vector<choice>();
     }
 }*/

const std::string story::get_name() const
{
    return name_;
}

const std::string story::get_text() const
{
    return text_;
}

const Node* make_choice(std::size_t index) const
{
    //     auto nd;

    if (index > listv.size())
    {
        return nullptr;
    }
    else
    {
        //   Node* val;
        // for (size_t i; i!=index; i++){}
        return listv[index].get_node();
    }
}

std::vector<std::string> list_choices(bool check_conditions = true) const
{
    std::vector<std::string> listc;
    std::size_t id;
    id = 1;
    for (; id <= listc.size(); id++)
    {
        listc.push_back(listc[id].get_node());
        // std::cout << listv[i].get_txt();
    }
    return listc;
}

void add_choice(const Node* other, const std::string& text,
                const std::vector<Condition>& conditions = {},
                const std::vector<Action>& operations = {})
{
    /* listv.add();
     listv[-1] = &text;
     listv[-1].get_node = *other;*/
    story::choice Ch(other, text);
    listv.push_back(Ch);
}

//} // namespace story
