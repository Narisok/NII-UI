#include <iostream>
#include <NII/Utility/Event.hpp>

int main(int argc, char **argv)
{
    nii::util::Event event;
    nii::util::Listener listener;
    listener.listen(event);

    event.call();
    std::cout << "Nothing Is Impossible!" << std::endl;
    return 0;
}