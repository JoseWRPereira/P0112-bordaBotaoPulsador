/*
 * File:   main.c
 * Author: josewrpereira
 *
 * Created on 13 de Agosto de 2020, 23:02:21
 *
 * -------------------------------------------------
 *          MAPA DE ENTRADAS E SAIDAS
 * -------------------------------------------------
 *  Pinos   |nº     |Conexão
 * ---------|-------|-------------------------------
 *  RB0     |33     | Segmento a
 *  RB1     |34     | Segmento b
 *  RB2     |35     | Segmento c
 *  RB3     |36     | Segmento d
 *  RB4     |37     | Segmento e
 *  RB5     |38     | Segmento f
 *  RB6     |39     | Segmento g
 *  RB7     |40     | Segmento p
 *  RD7     |30     | Hab. Dezena (Catodo comum)
 *  RD6     |29     | Hab. Unidade (Catodo comum)
 * ---------|-------|-------------------------------
 *  RD2     |21     | Botão -1
 *  RD3     |22     | Botão +1
 * -------------------------------------------------
 * -------------------------------------------------
 */

#include <xc.h>
#include "config.h"
#include "delay.h"
#include "disp7seg.h"
#include "botao.h"

void main(void)
{
    char num = 0;

    disp7segX2_init();
    botao_init();

    while( 1 )
    {
        disp7segX2( num );

        if( b1_bordaSubida() )
            num = ++num % 100;
        if( b0_bordaDescida() )
            num = num==0 ? 99 : num-1;

        delay(1);
    }
    return;
}
