#include "button Mappings.h"
#include <map>

static std::map<int, const char*> buttons = {
		{0x4000,"Square"},
		{0x1000,"Cross"},
		{0x2000,"Circle"},
		{0x8000,"Triangle"},
		{0x0100,"Left Shoulder"},
		{0x0200,"Right Shoulder"},
		{0x0020,"Select"},
		{0x0010,"Start"},
		{0x0040,"Left Thumb"},
		{0x0080,"Right Thumb"},
};

static const int buttonsKeys[10]{ 0x4000,0x1000,0x2000,0x8000,0x0100,0x0200,0x0020,0x0010,0x0040,0x0080 };

void buttonMappingEditor(bool& makerOpen, int* buttonProfile) {
	extern int buttonMapping[11];
	extern bool gameProfileSet;

	for (int i = 0; i < 11; i++) buttonMapping[i] = buttonProfile[i];
	gameProfileSet = true;

	if (ImGui::Begin("Button Remapper", &makerOpen)) {

		for (short int i = 0; i < IM_ARRAYSIZE(buttonsKeys); i++) {
			ImGui::PushID(&buttonProfile[i]);
			ImGui::Text(buttons[buttonsKeys[i]]);
			ImGui::SameLine();
			if(ImGui::BeginCombo("##Change Button", std::format("{}", buttons[buttonProfile[i]]).c_str())) {
				for (short int j = 0; j < IM_ARRAYSIZE(buttonsKeys); j++) if (ImGui::Selectable(buttons[buttonsKeys[j]])) buttonProfile[i] = buttonsKeys[j];
				ImGui::EndCombo();
			}
			ImGui::PopID();
		}
		if (ImGui::RadioButton("Map dpad to joysticks", buttonProfile[10]))
			buttonProfile[10] = 1 * (buttonProfile[10] <= 0);
	}
	ImGui::End();
}