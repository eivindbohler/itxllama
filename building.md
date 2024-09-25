# Building your own ITX-Llama

> **Note**  
> This document is still a work in progress.  
For feedback, suggestions, etc. - please add a post to the [Vogons thread][vogons-thread].

## BOM
There's a BOM file [here][bom], ready to be used with JLCPCB's assembly service.
In addition to the components that can be sourced through JLC/LCSC, you need to order a few extras elsewhere:
- Vortex86EX SOM - [DMP][som]
- Crystal CS4237B - Search for "cs4237b" on [eBay][ebay]
- ATTINY84A-PU - [DigiKey][digikey], [Mouser][mouser], etc

For programming the ATTiny, you need a hardware AVR programmer. There are plenty out there.

If you want emulated modem:
- D1 Mini v4.0.0 (ESP8266) - [AliExpress][d1mini]

[vogons-thread]: https://www.vogons.org/viewtopic.php?t=93480
[bom]: kicad/fabrication/ITX-Llama-v1revE-BOM.xlsx
[som]: https://shop.dmp.com.tw/INT/products/25
[ebay]: https://ebay.com
[digikey]: https://www.digikey.com/en/products/detail/microchip-technology/ATTINY84A-PU/2774082
[mouser]: https://www2.mouser.com/ProductDetail/Microchip-Technology/ATTINY84A-PU?qs=JVB2vxgwrww2b%2Fem%2FNzH9Q%3D%3D
[d1mini]: https://www.aliexpress.com/item/1005001621784437.html