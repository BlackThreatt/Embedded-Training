# Exercise 1
--
Although both implementations of the register map differ, the machine code is the same. As for struct padding, it wasn't needed as all registers are 4-bytes aligned.

# Exercise 2 
--
Creating macros for bit manipulations make code user friendly and save time during driver development.

# Exercise 4
--
In this exercise, I was able to create an interrupt based uart example from scratch. I had to import CMSIS and some ST's HAL just to focus on the uart and not implementing CMSIS interrupt API from scratch too.
And as can be seen in the source code, it is limited to that. 
This example also helped me detect a defect in GPIO library after making the change to MACROs. 
Finally, this was fun!

