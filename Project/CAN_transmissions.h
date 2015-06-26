void CAN_Tx(uint16_t ID,uint8_t DLC,uint16_t data[]);
void sendEchoCAN();
CanRxMsg CAN_Rx(void);
void Tx_setDefault_values(CanTxMsg*);
void Rx_setDefault_values(CanRxMsg*);