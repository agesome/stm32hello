#pragma once

#include <array>
#include <stm32h5xx_hal.h>
#include <stm32h5xx_ll_spi.h>

#include "util.h"

#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

template<size_t N>
struct bytes : public std::array<uint16_t, N> {};

template<class... U>
bytes(U...) -> bytes<sizeof...(U)>;

enum class SpiDevice
{
    Display = 0,
    Touch,
    SDcard
};


void spi_init();

void spi_write(uint16_t data);
void spi_write(uint16_t const *data, size_t size);
template<size_t N>
void spi_write(const bytes<N> &data)
{
    spi_write(data.data(), N);
}

// template<size_t N>
// bytes<N> spi_read()
// {
//     extern SPI_HandleTypeDef spi;
//     bytes<N> data;

// #if 1
//     LL_SPI_StartMasterTransfer(spi.Instance);

//     for (auto &byte : data)
//     {
//         while(!LL_SPI_IsActiveFlag_TXP(spi.Instance));
//         LL_SPI_TransmitData8(spi.Instance, 0xff);
//         while(!LL_SPI_IsActiveFlag_RXP(spi.Instance));
//         byte = LL_SPI_ReceiveData8(spi.Instance);
//     }
// #else
//     if (HAL_SPI_Receive(&spi, data.data(), N, kSpiTimeout) != HAL_OK)
//     {
//         message("spi_read %u bytes NOK!", N);
//     }
// #endif
//     return data;
// }

// uint8_t spi_read_byte();

void chipselect_high(SpiDevice);
void chipselect_low(SpiDevice);