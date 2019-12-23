/**
  Defining the types of functions that will receive the states.
*/

#define STX 0x02
#define ETX 0x03

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef void (*Action_t)(void *, unsigned char);
typedef void (*Callback_t)(unsigned char *);

typedef enum{
  ST_STX,
  ST_ADDR,
  ST_QTD,
  ST_DADOS,
  ST_CHK,
  ST_ETX,
  ST_END
}state_t;

/**
  Union ---> Variables that have same memory space
  Variables with different representations but with the same memory space
  union{
    short addr16[2];
    int addr;
    uchar addr8[4];
  }addr_u
*/

/**
  Data Types:
  STX: 1 byte (Transmission Start) (0x02)
  ADDR: 2 bytes - little endian -> Address
  QTD_DADOS: 1 byte -> Amount of data transmitted
  DADOS: N Bytes -> Data up to 128 bytes, as determined by QTD_DADOS
  CHK: 1 Byte --> Transmission Checksum -> Sum from address to data must equal checksum.
  ETX: 1 Byte --> End of Transmission (0x03).
*/
typedef struct StateMachine{
  state_t state;
  Action_t action[ST_END];

  //Endereco
  unsigned short     addr;
  unsigned short addr_rec;

  //Checksum
  unsigned char     chk;
  unsigned char chk_rec;

  //Dados
  unsigned char buffer[128];
  unsigned char   qtd_dados;
  unsigned char     qtd_rec;

  Callback_t callback;
}sm_t;

/**
  Functions Headers
*/

void initSM(sm_t *sm, unsigned short addr, Callback_t callback);
void execSM(sm_t *sm, unsigned char data);
void ExecSM(sm_t *sm, unsigned char *data, unsigned short size);