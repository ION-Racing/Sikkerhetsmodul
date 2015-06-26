uint8_t CANTx(uint32_t address, uint8_t length, uint8_t data[8]);
void Init_RxMes(CanRxMsg *RxMessage);
void CANsendEcho(void);
uint8_t CANechoSuccess(void);
void CANparseMessage(uint8_t CAN_FIFON);

