#define LAN_WIZ 1

#ifndef LAN_WIZ
#include "usbd_if.h"
#include "usbd_cdc_if.h"

#if ARDUINO < 10900

void USBD_reenumerate(void)
{
#ifndef USBD_REENUM_DISABLED
  /* Re-enumerate the USB */
#ifdef USB_DISC_PIN
  pinMode(USB_DISC_PIN, OUTPUT);
  digitalWrite(USB_DISC_PIN, HIGH);
  delay(10);
  digitalWrite(USB_DISC_PIN, LOW);
#else
#ifdef USE_USB_HS_IN_FS
  PinName pinDP = USB_OTG_HS_DP;
#elif defined(USB_OTG_FS)
  PinName pinDP = USB_OTG_FS_DP;
#else /* USB */
  PinName pinDP =  USB_DP;
#endif
  pin_function(pinDP, STM_PIN_DATA(STM_MODE_OUTPUT_PP, GPIO_NOPULL, 0));
  digitalWriteFast(pinDP, LOW);
  delay(USBD_ENUM_DELAY);
  pin_function(pinDP, STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, 0));
  /*delay(USBD_ENUM_DELAY);*/
#endif /* USB_DISC_PIN */
#endif /* USBD_REENUM_DISABLED */
#endif /* LAN_WIZ */
}

#endif