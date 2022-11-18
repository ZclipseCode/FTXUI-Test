#include "ftxuiAll.h"

int main() {
    using namespace ftxui;
    int mouse_x = 0;
    int mouse_y = 0;

    // A triangle following the mouse, using braille characters.
    auto renderer_line_braille = Renderer([&] {
        auto c = Canvas(100, 100);
        c.DrawText(0, 0, "Several lines (braille)");
        c.DrawPointLine(mouse_x, mouse_y, 80, 10, Color::Red);
        c.DrawPointLine(80, 10, 80, 40, Color::Blue);
        c.DrawPointLine(80, 40, mouse_x, mouse_y, Color::Green);
        return canvas(std::move(c));
        });

    int selected_tab = 12;
    auto tab = Container::Tab(
        {
            renderer_line_braille,
        },
        &selected_tab);

    // This capture the last mouse position.
    auto tab_with_mouse = CatchEvent(tab, [&](Event e) {
        if (e.is_mouse()) {
            mouse_x = (e.mouse().x - 1) * 2;
            mouse_y = (e.mouse().y - 1) * 4;
        }
        return false;
        });

    auto component = Container::Horizontal({
        tab_with_mouse
        });

    // Add some separator to decorate the whole component:
    auto component_renderer = Renderer(component, [&] {
        return hbox({
                   tab_with_mouse->Render(),
            }) |
            border;
        });

    auto screen = ScreenInteractive::FitComponent();
    screen.Loop(component_renderer);

    return 0;
}