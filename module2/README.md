# Blinking LED

In this exercise, we will make the Green LED on the ST Board blink.

1. **Add CMSIS Solution** in your VS Code Extension and add a new project.

2. **Select B-L475E-IOT01A1** in your project.  
   *(You will need to add STM32L4xx_DFP first. Check [CMSIS Pack](https://www.keil.arm.com/packs/stm32l4xx_dfp-keil/overview/) and [CMSIS-Toolbox](https://open-cmsis-pack.github.io/cmsis-toolbox/installation/#vcpkg-setup-in-vs-code))*

3. **Install** [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html) and [ST-LINK](https://www.st.com/en/development-tools/stsw-link009.html#get-software).

4. **Choose BasicCubeMX solution** as our template and create the project.

5. After you create a project, move to the CMSIS Solution and **Run Configuration Generator** by pressing the icon next to `Device:CubeMX`.

6. We will set **pin A5 as the GPIO_Output** as it is the pin for the green LED on the Board.

   ![module2-peripherals.png](images/module2-peripherals.png)

7. After we set this pin, we will generate the code.

8. In the `main.c` file created under `Device:CubeMX/'CubeMX generate'/CubeMX`, you can see all the peripherals are initialized by the generator. We just need to add the blinking logic to control the LED. In the `while` loop, we will use `GPIO_Write_Pin` to control the LED.
