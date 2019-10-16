#include "set_airspaces.h"

#include "../gui_list.h"
#include "../gui_value.h"
#include "../gui_dialog.h"
#include "../gui_storage.h"
#include "gui_accel_calib.h"

#include "../../fc/conf.h"

void gui_set_airspaces_init()
{
	gui_list_set(gui_set_airspaces_item, gui_set_airspaces_action, 4, GUI_SETTINGS);
}


void gui_set_airspaces_warning_cb(float val)
{
    gui_switch_task(GUI_SET_AIRSPACE);

    config.airspaces.warning_m = val;
    eeprom_busy_wait();
    eeprom_update_word(&config_ee.airspaces.warning_m, config.airspaces.warning_m);
}

void gui_set_airspaces_reset_cb(uint8_t ret)
{
	if (ret == GUI_DIALOG_YES)
	{
		char path[32];

		strcpy_P(path, PSTR("/AIR/IGN_SOFT"));
		f_delete_node(path, sizeof(path));
		strcpy_P(path, PSTR("/AIR/IGN_HARD"));
		f_delete_node(path, sizeof(path));

	    memset((void *)&fc.airspace.ignore, 0, sizeof(fc.airspace.ignore));
	}

	gui_switch_task(GUI_SET_AIRSPACE);
}

void gui_set_airspaces_action(uint8_t index)
{
	switch(index)
	{
		case(0):
				gui_switch_task(GUI_SET_AIRSPACE_CLASS);
		break;

		case(1):
				gui_value_conf_P(PSTR("Alert near"), GUI_VAL_NUMBER_DISABLE, PSTR("%0.0f m"), config.airspaces.warning_m, 0, 3000, 100, gui_set_airspaces_warning_cb);
				gui_switch_task(GUI_SET_VAL);
		break;

		case(2):
				config.airspaces.alert_on = !config.airspaces.alert_on;
				eeprom_busy_wait();
				eeprom_update_byte((uint8_t *)&config_ee.airspaces.alert_on, config.airspaces.alert_on);
		break;

		case(3):
				gui_dialog_set_P(PSTR("Confirm"), PSTR("Reset airspace\nignore list?"), GUI_STYLE_YESNO, gui_set_airspaces_reset_cb);
				gui_switch_task(GUI_DIALOG);
		break;
	}
}

void gui_set_airspaces_item(uint8_t index, char * text, uint8_t * flags, char * sub_text)
{
	switch (index)
	{
		case (0):
			strcpy_P(text, PSTR("Enabled classes"));
			*flags |= GUI_LIST_FOLDER;
		break;

		case (1):
			strcpy_P(text, PSTR("Alert near"));
			*flags |= GUI_LIST_SUB_TEXT;
			strcpy_P(sub_text, PSTR("500m"));
		break;

		case (2):
			strcpy_P(text, PSTR("Alert inside"));

			if (config.airspaces.alert_on)
				*flags |= GUI_LIST_CHECK_ON;
			else
				*flags |= GUI_LIST_CHECK_OFF;

		break;

		case (3):
			strcpy_P(text, PSTR("Reset ignore list"));
			*flags |= GUI_LIST_FOLDER;
		break;
	}
}

