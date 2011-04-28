/***************************************************
 * Button mappings
 *
 * Change the key values according to linux/input.h
 * and then rebuild the driver
 ***************************************************/

/* Power button */
//#define BUTTON_POWER		KEY_POWER
#define BUTTON_POWER		KEY_S

/* Play, rewind, forward buttons */
#define BUTTON_REWIND		KEY_REWIND
#define BUTTON_PLAYPAUSE	KEY_PLAYPAUSE
//#define BUTTON_PLAYPAUSE	KEY_SPACE
#define BUTTON_FORWARD		KEY_FASTFORWARD

/* Previous, stop, next buttons */
#define BUTTON_PREVIOUS		KEY_PREVIOUS
#define BUTTON_STOP			KEY_STOP
#define BUTTON_NEXT			KEY_NEXT

/* Volume buttons */
#define BUTTON_MUTE			KEY_MUTE
#define BUTTON_VOLUMEUP		KEY_VOLUMEUP
#define BUTTON_VOLUMEDOWN	KEY_VOLUMEDOWN

/* Arrow buttons */
#define BUTTON_RIGHT		KEY_RIGHT
#define BUTTON_LEFT			KEY_LEFT
#define BUTTON_DOWN			KEY_DOWN
#define BUTTON_UP			KEY_UP

/* OK button */
//#define BUTTON_OK			KEY_OK
#define BUTTON_OK      KEY_ENTER

/* Back button */
#define BUTTON_BACK			KEY_BACKSPACE

/* Special buttons from left to right counter clockwise*/
//#define BUTTON_HOME			KEY_ESC
#define BUTTON_HOME			KEY_BACKSPACE
//#define BUTTON_WINDOWS		KEY_PROGRAM
#define BUTTON_WINDOWS		KEY_I
//#define BUTTON_RADIO		KEY_MEDIA
#define BUTTON_RADIO		KEY_SPACE
//#define BUTTON_MUSIC		KEY_LANGUAGE
#define BUTTON_MUSIC		KEY_L
//#define BUTTON_DTS			KEY_SUBTITLE
#define BUTTON_DTS			KEY_T
#define BUTTON_TRANQUIL		KEY_Q // sleep
//#define BUTTON_FULLSCREEN	KEY_ZOOM
#define BUTTON_FULLSCREEN	KEY_TAB

/* Middle special button */
//#define BUTTON_HOMETHEATER	KEY_MENU
#define BUTTON_HOMETHEATER	KEY_C
