/*
 *  HID driver for "PHILIPS MCE USB IR Receiver- Spinel plusf0r ASUS" remotes
 *
 *  Copyright (c) 2010 Panagiotis Skintzos
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

#include <linux/device.h>
#include <linux/input.h>
#include <linux/hid.h>
#include <linux/module.h>

#include "mappings.h"

#define USB_VENDOR_ID_PHILIPS       0x0471
#define USB_DEVICE_ID_PHILIPS_MCE_USB_IR_RECEIVER_SPINEL_PLUS_FOR_ASUS 0x206c

#define pa_map_key(c)	set_bit(EV_REP, hi->input->evbit); \
						hid_map_usage_clear(hi, usage, bit, max, EV_KEY, (c))

static int philips_asus_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	switch (usage->hid) {
	/* Power button */
	case 0x00010082:	pa_map_key(BUTTON_POWER);			break;

	/* Play, rewind, forward buttons */
	case 0x000c00b4:	pa_map_key(BUTTON_REWIND);			break;
	case 0x000c00cd:	pa_map_key(BUTTON_PLAYPAUSE);		break;
	case 0x000c00b3:	pa_map_key(BUTTON_FORWARD);			break;

	/* Previous, stop, next buttons */
	case 0x000c00b6:	pa_map_key(BUTTON_PREVIOUS);		break;
	case 0x000c00b7:	pa_map_key(BUTTON_STOP);			break;
	case 0x000c00b5:	pa_map_key(BUTTON_NEXT);			break;

	/* Volume buttons */
	case 0x000c00e2:	pa_map_key(BUTTON_MUTE);			break;
	case 0x000c00e9:	pa_map_key(BUTTON_VOLUMEUP);		break;
	case 0x000c00ea:	pa_map_key(BUTTON_VOLUMEDOWN);		break;

	/* Arrow buttons */
	case 0x0007004f:	pa_map_key(BUTTON_RIGHT);			break;
	case 0x00070050:	pa_map_key(BUTTON_LEFT);			break;
	case 0x00070051:	pa_map_key(BUTTON_DOWN);			break;
	case 0x00070052:	pa_map_key(BUTTON_UP);				break;

	/* Ok button */
	case 0x00070028:	pa_map_key(BUTTON_OK);				break;

	/* Back button */
	case 0x000c0224:	pa_map_key(BUTTON_BACK);			break;

	/* Special buttons from left to right counter clockwise*/
	case 0xffbc0038:	pa_map_key(BUTTON_HOME);			break;
	case 0xffbc0035:	pa_map_key(BUTTON_WINDOWS);			break;
	case 0xffbc003a:	pa_map_key(BUTTON_RADIO);			break;
	case 0xffbc0039:	pa_map_key(BUTTON_MUSIC);			break;
	case 0xffbc0037:	pa_map_key(BUTTON_DTS);				break;
	case 0xffbc0036:	pa_map_key(BUTTON_TRANQUIL);		break;
	case 0xffbc0027:	pa_map_key(BUTTON_FULLSCREEN);		break;

	/* Middle special button */
	case 0xffbc0024:	pa_map_key(BUTTON_HOMETHEATER);		break;

	default:
		return 0;
	}
	return 1;
}

static int philips_asus_probe(struct hid_device *hdev,
		const struct hid_device_id *id)
{
	int ret;
	/* Connect only to hid input (not hiddev & hidraw)*/
	unsigned int cmask = HID_CONNECT_HIDINPUT;

	ret = hid_parse(hdev);
	if (ret) {
		dev_err(&hdev->dev, "parse failed\n");
		goto err_free;
	}

	ret = hid_hw_start(hdev, cmask);
	if (ret) {
		dev_err(&hdev->dev, "hw start failed\n");
		goto err_free;
	}

	return 0;
err_free:
	return ret;
}

static const struct hid_device_id philips_asus_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOR_ID_PHILIPS,
		USB_DEVICE_ID_PHILIPS_MCE_USB_IR_RECEIVER_SPINEL_PLUS_FOR_ASUS) },
	{ }
};
MODULE_DEVICE_TABLE(hid, philips_asus_devices);

static struct hid_driver philips_asus_driver = {
	.name = 			"philips_asus",
	.id_table = 		philips_asus_devices,
	.input_mapping = 	philips_asus_input_mapping,
	.probe = 			philips_asus_probe,
};

static int __init philips_asus_init(void)
{
	return hid_register_driver(&philips_asus_driver);
}

static void __exit philips_asus_exit(void)
{
	hid_unregister_driver(&philips_asus_driver);
}

module_init(philips_asus_init);
module_exit(philips_asus_exit);
MODULE_LICENSE("GPL");
