#include "set_audio.h"

#include "../gui_list.h"
#include "../gui_value.h"

#include "../../fc/conf.h"

void gui_set_audio_init()
{
	gui_list_set(gui_set_audio_item, gui_set_audio_action, 1, GUI_SET_SYSTEM);
}

void gui_set_audio_stop() {}

void gui_set_audio_loop()
{
	gui_list_draw();
}

void gui_set_audio_irqh(uint8_t type, uint8_t * buff)
{
	gui_list_irqh(type, buff);
}

void gui_set_audio_vol_cb(float val)
{
	gui_switch_task(GUI_SET_AUDIO);
	eeprom_busy_wait();
	uint8_t tmp = val;
	eeprom_update_byte(&config.audio_profile.volume, tmp);
	fc.audio_volume = tmp;
}

void gui_set_audio_action(uint8_t index)
{
	switch(index)
	{
		case(0):
			gui_value_conf_P(PSTR("General volume"), GUI_VAL_VOLUME, PSTR("%0.0f %%"), fc.audio_volume, 0, 100, 5, gui_set_audio_vol_cb);
			gui_switch_task(GUI_SET_VAL);
		break;
	}
}

void gui_set_audio_item(uint8_t index, char * text, uint8_t * flags, char * sub_text)
{
	switch (index)
	{
		case (0):
			sprintf_P(text, PSTR("General volume"));
			sprintf_P(sub_text, PSTR("%d %%"), fc.audio_volume);
			*flags |= GUI_LIST_SUB_TEXT;
		break;
	}
}

