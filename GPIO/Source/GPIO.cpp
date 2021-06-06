void pinMode( uint8_t pin , uint8_t volatile *pin_data_direction_register, bool Mode )
{
	if(Mode==OUTPUT)
	*pin_data_direction_register|= (1 << pin);
	else if(Mode==INPUT)
	*pin_data_direction_register&= ~(1 << pin);
}
//PORTB
void digitalWrite( uint8_t pin ,uint8_t volatile *port_data_pin_register, bool state)
{
	if(state==HIGH)
	*port_data_pin_register|= (1 << pin);
	else if(state==LOW)
	*port_data_pin_register&= ~(1 << pin);
}
//PINx
uint8_t digitalRead( uint8_t pin , uint8_t volatile *port_input_pin_register)
{
	return ((*port_input_pin_register) & (1<<pin));
}