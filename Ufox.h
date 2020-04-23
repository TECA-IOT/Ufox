/*
Derechos Reservados "Teca" 2020, autor Marco A. Caballero Rev.1.2
*/
#ifndef UFOX_H
#define UFOX_H
#include <Arduino.h>

class Ufox
{
  public:
    Ufox();
    Ufox(bool _dbg);
    Ufox(bool _dbg, uint8_t _rst_ws);
    void debug(bool _dbg);
    void begin(uint16_t _baudio);
    String comand(String _cmd);
    String ID();
    String PAC();
    uint16_t TEMP();
    uint16_t VOLT();
    void RST();
    String SLEEP();
    String SEND(uint32_t _dataint);
    String SEND(String _datastr);
    String SEND_RCV(uint32_t _dataint_rcv);
    String SEND_RCV(String _datastr_rcv);
    
  private:
    #define baud_ws 9600
    uint8_t pin_rst_wisol=12;
    String ATS = "AT$";
    String ENV = "env:> ";
    String RCV = "<rec: "; 
    char caracter = 0x00;
    char cadena_cad[40]= " ";
    uint8_t i;
    String comand2(String _cmd);
    bool dbg;
    uint8_t rst_ws;
    uint32_t dato;
    uint16_t baudio;
    String cmd;
    uint32_t dataint;
    String datastr;
    uint32_t dataint_rcv;
    String datastr_rcv;
};

#endif
