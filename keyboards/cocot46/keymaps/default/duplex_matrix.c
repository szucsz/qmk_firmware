/* Copyright 2021 aki27
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>

#include QMK_KEYBOARD_H
#include "matrix.h"
#include "bmp_matrix.h"
#include "spi.h"

//--------------------------
// for duplex matrix
//--------------------------

static void select_row(uint8_t row)
{
    setPinOutput(BMPAPI->app.get_config()->matrix.row_pins[row]);
    writePinLow(BMPAPI->app.get_config()->matrix.row_pins[row]);
}

static void unselect_row(uint8_t row)
{
    setPinInputHigh(BMPAPI->app.get_config()->matrix.row_pins[row]);
}

static void select_col(uint8_t col)
{
    setPinOutput(BMPAPI->app.get_config()->matrix.col_pins[col]);
    writePinLow(BMPAPI->app.get_config()->matrix.col_pins[col]);
}

static void unselect_col(uint8_t col)
{
    setPinInputHigh(BMPAPI->app.get_config()->matrix.col_pins[col]);
}

static void init_col2row() {
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    for(int i=0; i < config->matrix.device_rows; i++) {
        setPinOd(config->matrix.row_pins[i]);
        writePinHigh(config->matrix.row_pins[i]);
    }

    for(int i=0; i < config->matrix.device_cols; i++) {
        setPinInputHigh(config->matrix.col_pins[i]);
    }
}

static void init_row2col() {
    const bmp_api_config_t *config = BMPAPI->app.get_config();

    for(int i=0; i < config->matrix.device_rows; i++) {
        setPinInputHigh(config->matrix.row_pins[i]);
    }

    for(int i=0; i < config->matrix.device_cols; i++) {
        setPinOd(config->matrix.col_pins[i]);
        writePinHigh(config->matrix.col_pins[i]);
    }
}

static void duplex_matrix_init() {
  init_col2row();
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    // comment out below
    // current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for(uint8_t col_index = 0; col_index < config->matrix.device_cols; col_index++) {

        if (readPin(config->matrix.col_pins[col_index])) {
            // Pin HI, clear col bit
            current_matrix[current_row] &= ~(MATRIX_ROW_SHIFTER << col_index);
        } else {
            // Pin LO, set col bit
            current_matrix[current_row] |= (MATRIX_ROW_SHIFTER << col_index);
        }
        
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < config->matrix.device_rows; row_index++)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        if (readPin(config->matrix.row_pins[row_index])) {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(MATRIX_ROW_SHIFTER << ( current_col + config->matrix.device_cols));
        } else {
            // Pin LO, set col bit
            current_matrix[row_index] |= (MATRIX_ROW_SHIFTER << ( current_col + config->matrix.device_cols));
        }
        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed)) {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

static uint32_t duplex_matrix_get_row() { return BMPAPI->app.get_config()->matrix.rows; };
static uint32_t duplex_matrix_get_col() { return BMPAPI->app.get_config()->matrix.cols; };

static uint32_t duplex_matrix_scan(matrix_row_t *matrix_raw)
{
    const bmp_api_config_t *config = BMPAPI->app.get_config();
    uint32_t changed = 0;

    // Set row, read cols
    init_col2row();
    for (uint8_t current_row = 0; current_row < config->matrix.device_rows; current_row++) {
        changed |= read_cols_on_row(matrix_raw, current_row);
    }
    // Set col, read rows
    init_row2col();
    for (uint8_t current_col = 0; current_col < config->matrix.device_cols; current_col++) {
        changed |= read_rows_on_col(matrix_raw, current_col);
    }

    return changed;
}

static const bmp_matrix_func_t duplex_matrix_func = {
    duplex_matrix_init, duplex_matrix_get_row, duplex_matrix_get_col, duplex_matrix_scan};

const bmp_matrix_func_t *get_matrix_func_user() { return &duplex_matrix_func; }
