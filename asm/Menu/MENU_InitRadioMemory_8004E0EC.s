	opt	c+, at+, e+, n-
	section .text

	xdef MENU_InitRadioMemory_8004E0EC
MENU_InitRadioMemory_8004E0EC:
	dw 0x3C02800C ; 0x8004E0EC
	dw 0x2442DB38 ; 0x8004E0F0
	dw 0x2403000F ; 0x8004E0F4
	dw 0xA4400000 ; 0x8004E0F8
	dw 0x2463FFFF ; 0x8004E0FC
	dw 0x0461FFFD ; 0x8004E100
	dw 0x24420014 ; 0x8004E104
	dw 0x03E00008 ; 0x8004E108
	dw 0x00000000 ; 0x8004E10C
