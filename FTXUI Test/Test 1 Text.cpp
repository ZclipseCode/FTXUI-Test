#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

int main() {
	ftxui::Element document =
		ftxui::hbox({
			ftxui::text("Helllo lads")
		});

	auto screen = ftxui::Screen::Create(
		ftxui::Dimension::Full(),       // Width
		ftxui::Dimension::Fit(document) // Height
	);
	Render(screen, document);
	screen.Print();

	return 0;
}