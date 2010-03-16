/*
 * (C) Copyright 2008
 * Dirk Behme <dirk.behme@gmail.com>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */
#ifndef _NOWPLUS_H_
#define _NOWPLUS_H_

const omap3_sysinfo sysinfo = {
	DDR_STACKED,
	"OMAP3 Nowplus board",
	"OneNAND",
};

/*
 * IEN  - Input Enable
 * IDIS - Input Disable
 * PTD  - Pull type Down
 * PTU  - Pull type Up
 * DIS  - Pull type selection is inactive
 * EN   - Pull type selection is active
 * M0   - Mode 0
 * The commented string gives the final mux configuration for that pin
 */
#define MUX_NOWPLUS() \
	/* SDRC */ \
	MUX_VAL(CP(SDRC_D0),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D1),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D2),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D3),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D4),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D5),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D6),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D7),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D8),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D9),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D10),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D11),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D12),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D13),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D14),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D15),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D16),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D17),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D18),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D19),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D20),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D21),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D22),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D23),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D24),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D25),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D26),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D27),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D28),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D29),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D30),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_D31),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_CLK),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_DQS0),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(SDRC_DQS1),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(SDRC_DQS2),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(SDRC_DQS3),		(IEN | PTD | EN | M0)) \
	/* GPMC */ \
	MUX_VAL(CP(GPMC_A1),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A2),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A3),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A4),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A5),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A6),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A7),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A8),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A9),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_A10),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_D0),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D1),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D2),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D3),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D4),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D5),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D6),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D7),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D8),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D9),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D10),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D11),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D12),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D13),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D14),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_D15),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_NCS0),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NCS1),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NCS2),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(GPMC_NCS3),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(GPMC_NCS4),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NCS5),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(GPMC_NCS6),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(GPMC_NCS7),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(GPMC_CLK),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(GPMC_NADV_ALE),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NOE),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NWE),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NBE0_CLE),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_NBE1),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(GPMC_NWP),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(GPMC_WAIT0),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(GPMC_WAIT1),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(GPMC_WAIT2),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(GPMC_WAIT3),		(IEN | PTU | EN | M7)) \
	/* DSS */ \
	MUX_VAL(CP(DSS_PCLK),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_HSYNC),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_VSYNC),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_ACBIAS),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA0),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA1),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA2),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA3),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA4),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA5),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA6),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA7),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA8),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA9),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA10),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA11),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA12),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA13),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA14),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA15),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA16),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA17),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA18),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA19),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA20),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA21),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA22),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(DSS_DATA23),		(IDIS | PTD | DIS | M0)) \
	/* Camera */ \
	MUX_VAL(CP(CAM_HS),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_VS),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_XCLKA),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_PCLK),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_FLD),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D0),			(IEN | PTD | EN | M7)) /* gpio_99 - LCD reg. reset */ \
	MUX_VAL(CP(CAM_D1),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D2),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D3),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D4),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D5),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D6),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D7),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D8),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D9),			(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D10),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_D11),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_XCLKB),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_WEN),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CAM_STROBE),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(CSI2_DX0),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CSI2_DY0),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CSI2_DX1),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(CSI2_DY1),		(IEN | PTD | EN | M7)) \
	/* MCBSP2 */ \
	MUX_VAL(CP(MCBSP2_FSX),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(MCBSP2_CLKX),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(MCBSP2_DR),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(MCBSP2_DX),		(IEN | PTD | EN | M0)) \
	/* MMC1 */ \
	MUX_VAL(CP(MMC1_CLK),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_CMD),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT0),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT1),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT2),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT3),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT4),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT5),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT6),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC1_DAT7),		(IEN | PTU | EN | M0)) \
	/* MMC2 */ \
	MUX_VAL(CP(MMC2_CLK),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_CMD),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT0),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT1),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT2),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT3),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT4),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT5),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT6),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MMC2_DAT7),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(MCBSP4_FSX),		(IDIS | PTU | EN | M4)) /* gpio_155 - moviNAND power enable */ \
	/* MCBSP3 */ \
	MUX_VAL(CP(MCBSP3_DX),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(MCBSP3_DR),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(MCBSP3_CLKX),	(IEN | PTD | DIS | M4)) /* gpio_xxx - touchscreen interrupt */ \
	MUX_VAL(CP(MCBSP3_FSX),		(IEN | PTD | EN | M7)) \
	/* UART2 */ \
	MUX_VAL(CP(UART2_CTS),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(UART2_RTS),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(UART2_TX),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(UART2_RX),		(IEN | PTU | EN | M7)) \
	/* UART1 */ \
	MUX_VAL(CP(UART1_TX),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(UART1_RTS),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(UART1_CTS),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(UART1_RX),		(IDIS | PTD | EN | M4)) /* gpio_151 RGB LED reset */ \
	/* MCBSP4 */ \
	MUX_VAL(CP(MCBSP4_CLKX),	(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(MCBSP4_DR),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(MCBSP4_DX),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(MCBSP1_CLKR),	(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(MCBSP1_FSR),		(IEN | PTU | EN | M4)) \
	MUX_VAL(CP(MCBSP1_DX),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(MCBSP1_DR),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(MCBSP_CLKS),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(MCBSP1_FSX),		(IDIS| PTD | DIS | M7)) /* gpio_161 - LCD ID enable */ \
	MUX_VAL(CP(MCBSP1_CLKX),	(IEN | PTD | EN | M7)) \
	/* UART3 */ \
	MUX_VAL(CP(UART3_CTS_RCTX),	(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(UART3_RTS_SD),	(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(UART3_RX_IRRX),	(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(UART3_TX_IRTX),	(IDIS | PTD | DIS | M0)) \
	/* HSUSB */ \
	MUX_VAL(CP(HSUSB0_CLK),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_STP),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DIR),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_NXT),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA0),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA1),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA2),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA3),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA4),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA5),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA6),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(HSUSB0_DATA7),	(IEN | PTD | EN | M0)) \
	/* I2C */ \
	MUX_VAL(CP(I2C1_SCL),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(I2C1_SDA),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(I2C2_SCL),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(I2C2_SDA),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(I2C3_SCL),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(I2C3_SDA),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(HDQ_SIO),		(IDIS | PTD | DIS | M4)) /* gpio_170 - MLCD reset */ \
	/* MCSPI */ \
	MUX_VAL(CP(MCSPI1_CLK),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(MCSPI1_SIMO),	(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(MCSPI1_SOMI),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(MCSPI1_CS0),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(MCSPI1_CS1),		(IDIS | PTU | EN | M7)) \
	MUX_VAL(CP(MCSPI1_CS2),		(IDIS | PTU | EN | M7)) \
	MUX_VAL(CP(MCSPI1_CS3),		(IDIS | PTU | EN | M7)) \
	MUX_VAL(CP(MCSPI2_CLK),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(MCSPI2_SIMO),	(IDIS | PTD | DIS | M1)) \
	MUX_VAL(CP(MCSPI2_SOMI),	(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(MCSPI2_CS0),		(IEN | PTU | EN | M7)) \
	MUX_VAL(CP(MCSPI2_CS1),		(IEN | PTD | EN | M7)) \
	MUX_VAL(CP(SYS_NIRQ),		(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(SYS_CLKOUT2),	(IEN | PTD | EN | M7)) \
	/* D2D */ \
	MUX_VAL(CP(D2D_MCAD0),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD1),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD2),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD3),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD4),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD5),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD6),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD7),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD8),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD9),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD10),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD11),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD12),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD13),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD14),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD15),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD16),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD17),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD18),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD19),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD20),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD21),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD22),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD23),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD24),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD25),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD26),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD27),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD28),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD29),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD30),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD31),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD32),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD33),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD34),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD35),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MCAD36),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_CLK26MI),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_NRESPWRON),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_NRESWARM),	(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(D2D_ARM9NIRQ),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_UMA2P6FIQ),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_SPINT),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_FRINT),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_DMAREQ0),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_DMAREQ1),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_DMAREQ2),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_DMAREQ3),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_N3GTRST),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_N3GTDI),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_N3GTDO),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_N3GTMS),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_N3GTCK),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_N3GRTCK),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_MSTDBY),		(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(D2D_IDLEREQ),	(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_IDLEACK),	(IEN | PTU | EN | M0)) \
	MUX_VAL(CP(D2D_MWRITE),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_SWRITE),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_MREAD),		(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_SREAD),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(D2D_MBUSFLAG),	(IEN | PTD | EN | M0)) \
	MUX_VAL(CP(D2D_SBUSFLAG),	(IEN | PTD | DIS | M0)) \
	/* SDRC clock */ \
	MUX_VAL(CP(SDRC_CKE0),		(IEN | PTD | DIS | M0)) \
	MUX_VAL(CP(SDRC_CKE1),		(IEN | PTD | DIS | M0)) \
	/* ETK */ \
	MUX_VAL(CP(ETK_CLK_ES2),	(IDIS | PTD | DIS | M0)) \
	MUX_VAL(CP(ETK_CTL_ES2),	(IEN | PTU | EN | M4)) \
	MUX_VAL(CP(ETK_D0_ES2),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(ETK_D1_ES2),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(ETK_D2_ES2),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(ETK_D3_ES2),		(IEN | PTU | EN | M4)) \
	MUX_VAL(CP(ETK_D4_ES2),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D5_ES2),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D6_ES2),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D7_ES2),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D8_ES2),		(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D9_ES2),		(IEN | PTD | DIS | M4)) \
	MUX_VAL(CP(ETK_D10_ES2),	(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D11_ES2),	(IEN | PTU | EN | M4)) \
	MUX_VAL(CP(ETK_D12_ES2),	(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D13_ES2),	(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D14_ES2),	(IEN | PTD | EN | M4)) \
	MUX_VAL(CP(ETK_D15_ES2),	(IEN | PTD | EN | M4))
#endif
