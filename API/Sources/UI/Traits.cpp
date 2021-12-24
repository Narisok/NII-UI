#include "NII/UI/Traits.hpp"

#include <NII/UI.hpp>

namespace nii::ui
{
    namespace serialization
    {

    std::unique_ptr<nii::ui::core::Primitive> createPrimitiveFromType(const std::string& type)
    {
        if (type == "widget") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Widget({100.f, 100.f}));
        }
        if (type == "border") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Border);
        }
        if (type == "scroll") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Scroll);
        }
        if (type == "canvas") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Canvas);
        }
        if (type == "list") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::List);
        }
        if (type == "button") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Button);
        }
        if (type == "text") {
            return std::unique_ptr<nii::ui::core::Primitive>(new nii::ui::Text);
        }
        return {};
    }

    }
}
