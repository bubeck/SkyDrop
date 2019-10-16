#include "settings.h"

#include "../gui_list.h"
#include "gui_filemanager.h"
#include "logger.h"

void gui_settings_init()
{
	gui_list_set(gui_settings_item, gui_settings_action, 9, GUI_PAGES);
}

void gui_settings_item(uint8_t index, char * text, uint8_t * flags, char * sub_text)
{
	switch (index)
	{
		case (0):
			strcpy_P(text, PSTR("Vario"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (1):
			strcpy_P(text, PSTR("Altimeters"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (2):
			strcpy_P(text, PSTR("Logger"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (3):
			strcpy_P(text, PSTR("Flight logs"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (4):
			strcpy_P(text, PSTR("Navigation"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (5):
			strcpy_P(text, PSTR("Airspaces"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (6):
			strcpy_P(text, PSTR("GPS"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (7):
			strcpy_P(text, PSTR("Bluetooth"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (8):
			strcpy_P(text, PSTR("Settings"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (9):
			strcpy_P(text, PSTR("Debug"));
			*flags |= GUI_LIST_FOLDER;
		break;
	}
}


void gui_settings_action(uint8_t index)
{
	switch (index)
	{
	case (0):
		gui_switch_task(GUI_SET_VARIO);
		break;

	case (1):
		gui_switch_task(GUI_SET_ALTIMETERS);
		break;

	case (2):
		gui_switch_task(GUI_SET_LOGGER);
		break;

	case (3):
		gui_filemanager_set_dir((char *) LOG_DIR_ABS);
		gui_filemanager_level = 0;
		gui_filemanager_set_tasks(GUI_FLIGHTDETAIL, GUI_SETTINGS);
		gui_switch_task(GUI_FILEMANAGER);
		break;

	case (4):
		gui_switch_task(GUI_HOME);
		break;

	case (5):
		gui_switch_task(GUI_SET_AIRSPACE);
		break;

	case (6):
		gui_switch_task(GUI_SET_GPS);
		break;

	case (7):
		gui_switch_task(GUI_SET_BLUETOOTH);
		break;

	case (8):
		gui_switch_task(GUI_SET_SYSTEM);
		break;

	case (9):
		gui_switch_task(GUI_SET_DEBUG);
		break;
	}
}
