# Exercise 1
--
This exercise taught me that correct pointer manipulation and understanding is crucial. 
The developed functions can be improved to incorporate memory alignment, save cpu cycles by sending data in QUADS instead of Bytes...

# Exercise 2
-- 
This exercise taught me why every peripheral register pointer should be volatile with some registers having an additional const in front to signify that they're read only. The combination ensures that software can't write it but the compiler still must re-read it every time as hardware can change it asynchronously.

## Register layer functions
- GPIO_Pin_Write / GPIO_Pin_Read => single-bit read-modify-write.
- GPIO_Set_Config / GPIO_Get_Config => correct multi-bit-field (2-bit and 4-bit) masking, both directions (insert and extract).
