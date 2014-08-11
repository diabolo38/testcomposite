/*
 ============================================================================
 Name        : TestComposite.c
 Author      : michel sanches
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "usbd_def.h"
#include "composite.h"

#define USB_CDC_CONFIG_DESC_SIZ                67
#define TST_CMD_PACKET_SIZE         8   /* packet size fixed */
#define TST_DATA_FS_MAX_PACKET_SIZE  0   /* try auto set */

#define TST_IN_EP                       0x81  /* EP1 for data IN */
#define TST_OUT_EP                      0x01  /* EP1 for data OUT */
#define TST_CMD_EP                      0x82  /* EP2 for TST commands */

/* USB CDC device Configuration Descriptor */
__ALIGN_BEGIN uint8_t USBD_TST_CfgFSDesc[USB_CDC_CONFIG_DESC_SIZ] __ALIGN_END =
{
  /*Configuration Descriptor*/
  0x09,   /* bLength: Configuration Descriptor size */
  USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
  LOBYTE(USB_CDC_CONFIG_DESC_SIZ),         /* wTotalLength:no of returned bytes */
  HIBYTE(USB_CDC_CONFIG_DESC_SIZ),
  0x02,   /* bNumInterfaces: 2 interface */
  0x01,   /* bConfigurationValue: Configuration value */
  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
  0xC0,   /* bmAttributes: self powered */
  0x32,   /* MaxPower 0 mA */

  /*---------------------------------------------------------------------------*/

  /*Interface Descriptor */
  0x09,   /* bLength: Interface Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: Interface */
  /* Interface descriptor type */
  0x00,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x01,   /* bNumEndpoints: One endpoints used */
  0x02,   /* bInterfaceClass: Communication Interface Class */
  0x02,   /* bInterfaceSubClass: Abstract Control Model */
  0x01,   /* bInterfaceProtocol: Common AT commands */
  0x00,   /* iInterface: */

  /*Header Functional Descriptor*/
  0x05,   /* bLength: Endpoint Descriptor size */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x00,   /* bDescriptorSubtype: Header Func Desc */
  0x10,   /* bcdCDC: spec release number */
  0x01,

  /*Call Management Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
  0x00,   /* bmCapabilities: D0+D1 */
  0x01,   /* bDataInterface: 1 */

  /*ACM Functional Descriptor*/
  0x04,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
  0x02,   /* bmCapabilities */

  /*Union Functional Descriptor*/
  0x05,   /* bFunctionLength */
  0x24,   /* bDescriptorType: CS_INTERFACE */
  0x06,   /* bDescriptorSubtype: Union func desc */
  0x00,   /* bMasterInterface: Communication class interface */
  0x01,   /* bSlaveInterface0: Data Class Interface */

  /*Endpoint 2 Descriptor*/
  0x07,                           /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,   /* bDescriptorType: Endpoint */
  TST_CMD_EP,                     /* bEndpointAddress */
  0x03,                           /* bmAttributes: Interrupt */
  LOBYTE(TST_CMD_PACKET_SIZE),     /* wMaxPacketSize: */
  HIBYTE(TST_CMD_PACKET_SIZE),
  0x10,                           /* bInterval: */
  /*---------------------------------------------------------------------------*/

  /*Data class interface descriptor*/
  0x09,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_INTERFACE,  /* bDescriptorType: */
  0x01,   /* bInterfaceNumber: Number of Interface */
  0x00,   /* bAlternateSetting: Alternate setting */
  0x02,   /* bNumEndpoints: Two endpoints used */
  0x0A,   /* bInterfaceClass: CDC */
  0x00,   /* bInterfaceSubClass: */
  0x00,   /* bInterfaceProtocol: */
  0x00,   /* iInterface: */

  /*Endpoint OUT Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  TST_OUT_EP,                        /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(TST_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(TST_DATA_FS_MAX_PACKET_SIZE),
  0x00,                              /* bInterval: ignore for Bulk transfer */

  /*Endpoint IN Descriptor*/
  0x07,   /* bLength: Endpoint Descriptor size */
  USB_DESC_TYPE_ENDPOINT,      /* bDescriptorType: Endpoint */
  TST_IN_EP,                         /* bEndpointAddress */
  0x02,                              /* bmAttributes: Bulk */
  LOBYTE(TST_DATA_FS_MAX_PACKET_SIZE),  /* wMaxPacketSize: */
  HIBYTE(TST_DATA_FS_MAX_PACKET_SIZE),
  0x00                               /* bInterval: ignore for Bulk transfer */
} ;



int  MyCDC_setup(struct  usbfunc_t *f, USBD_SetupReqTypedef *req ){
    return -1;
}
void MyCDC_disable(struct  usbfunc_t *f)
{
}

int  MyCDC_enable(struct  usbfunc_t *f)
{
    return 0;
}

int  MyCDC_set_alt(struct  usbfunc_t *f, int itf, int alt){
    return 0;
}

int  MyCDC_in_data(struct  usbfunc_t *f, int ep){
    return 0;
}
int  MyCDC_out_data(struct  usbfunc_t *f, int ep){
    return 0;
}

struct usbfunc_itf_t MyCDC_Driver= {
        .setup=MyCDC_setup,
        .disable=MyCDC_disable,
        .set_alt=MyCDC_set_alt,
        .in_data=MyCDC_in_data,
        .out_data=MyCDC_out_data
};


int USBD_RegisterClass(void *pdev, void *CDev_Class){
    return 0;
}

USBD_HandleTypeDef MyUSBDev;

struct CDev_t *cdev;
struct  usbfunc_t *f1;
struct  usbfunc_t *f2;
int main(void) {
	puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	cdev=CDev_NewDevice();
	if( cdev !=NULL ){
	    f1=CDev_NewFunc(USBD_TST_CfgFSDesc,USBD_TST_CfgFSDesc, &MyCDC_Driver, CFG_DESC|FORCE_AUTO_EP|FORCE_AUTO_IF);
	    if( f1 ){
	        CDev_AddFunc(cdev, f1, 1,"CDC-1");
	        f2=CDev_NewFunc(USBD_TST_CfgFSDesc,USBD_TST_CfgFSDesc, &MyCDC_Driver, CFG_DESC|FORCE_AUTO_EP|FORCE_AUTO_IF);
	        if( f2){
	            CDev_AddFunc(cdev, f2, 1,"CDC-2");
	            CDev_Register(cdev, &MyUSBDev);
	        }
	    }
	}
	return EXIT_SUCCESS;
}
