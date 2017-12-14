/*
 * Copyright (C) 2017 Rasmus Antons <r.antons@tu-bs.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    idealvolting IdealVolting implementation for RIOT
 * @ingroup     boards_inga_common
 * @brief       Idealvolting implementation.
 * @{
 *
 * @file
 * @brief       Idealvolting implementation.
 *
 * @author      Rasmus Antons <r.antons@tu-bs.de>
 *
 * @}
 */

#ifndef IDEALVOLTING_CONFIG_H
#define IDEALVOLTING_CONFIG_H

#define SI_I2C_DEV        I2C_DEV(0)
#define SI_I2C_ADDR       0x2d
#define SI_REG_LOCK       0
#define SI_REG_REPLY      0x01
#define SI_BUSY           0
#define SI_READY          1
#define SI_BOOTING        2

#define IV_RESET_VREG     0

#endif /* IDEALVOLTING_CONFIG_H */
