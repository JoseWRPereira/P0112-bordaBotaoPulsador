/*
 * File:   delay.c
 * Author: josewrpereira
 *
 * Created on 13 de Agosto de 2020, 17:32
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
 * ------------------------------------------------- 
 */
#include <xc.h>
#include "config.h"
#include "delay.h"

#define QTD_DIGITOS         2
#define BASE                10

#define DISP7SEG_BUS( x )   PORTB = x
#define HAB_DEZENA( x )     PORTDbits.RD7 = x
#define HAB_UNIDADE( x )    PORTDbits.RD6 = x


char digitos7seg[16] = {    0x3F, 0x06, 0x5B, 0x4F, 
                            0x66, 0x6D, 0x7D, 0x07, 
                            0x7F, 0x6F, 0x77, 0x7C, 
                            0x39, 0x5E, 0x79, 0x71  };

void disp7segX2_init( void )
{
    ANSELH = 0;
    TRISB = 0x00;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    
    HAB_DEZENA( 1 );
    HAB_UNIDADE( 1 );
    DISP7SEG_BUS(0xFF);    delay(500);
    DISP7SEG_BUS(0x00);    delay(500);
    DISP7SEG_BUS(0xFF);    delay(500);
    DISP7SEG_BUS(0x00);    delay(500);
}

unsigned char posicao = 0;
void disp7segX2( unsigned char num )
{
    switch( posicao )
    {
        case 0: // Unidade
                HAB_DEZENA( 0 );
                DISP7SEG_BUS( digitos7seg[num % BASE] );
                HAB_UNIDADE( 1 );
                break;

        case 1: // Dezena
                HAB_UNIDADE( 0 );
                DISP7SEG_BUS( digitos7seg[(num / BASE) % BASE] );
                HAB_DEZENA( 1 );
                break;
    }
    posicao = ++posicao % QTD_DIGITOS;
}
