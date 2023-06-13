#include "../include/libzork/story/node.hh"

int main
{
    story::Node hello("hello_node", "hello.txt");
    story::Node world("world_node", "world.txt");
    hello.add_choice(&hello, "self reference");
    hello.add_choice(&world, "<random text>");
    const auto also_world = hello.make_choice(1);
    std::cout << hello.get_name() << ": " << hello.get_text() << "\n";
    std::cout << also_world->get_name() << ": " << also_world->get_text()
              << "\n";
    for (const std::string& choice : hello.list_choices())
        std::cout << hello.get_name() << " -> " << choice << "\n";
}
