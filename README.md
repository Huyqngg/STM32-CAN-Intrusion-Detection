# STM32 CAN Intrusion Detection

An embedded CAN-bus intrusion detection project with two STM32 nodes. An STM32F103C8T6 generates CAN traffic, while an STM32F411CEU6 receives frames through an MCP2515 and runs a neural network using ST's X-CUBE-AI runtime. Classification results are printed over UART as **NORMAL**, **DoS ATTACK**, or **SPOOFING**.

This repository preserves the files supplied with the project, including the STM32CubeIDE projects, drivers, generated AI code, model, dataset, and existing build outputs. This README is the only added file.

## Project contents

| Path | Purpose |
| --- | --- |
| `blackpill/` | STM32F411CEU6 receiver and AI inference project |
| `blackpill/Core/Src/main.c` | MCP2515 setup, frame reception, input normalization, inference, and UART output |
| `blackpill/Core/Src/MCP2515.c` | MCP2515 SPI driver implementation |
| `blackpill/Core/Inc/MCP2515.h` | MCP2515 driver declarations and register definitions |
| `blackpill/X-CUBE-AI/App/` | Generated network implementation, parameters, and generation report |
| `blackpill/Middlewares/ST/AI/` | AI runtime headers and Cortex-M4 GCC library |
| `blackpill/blackpill.ioc` | STM32CubeMX configuration for the receiver |
| `node1/` | STM32F103C8T6 CAN traffic generator project |
| `node1/Core/Src/main.c` | Traffic scenarios selected by `CHEDO_TEST` |
| `node1/node1.ioc` | STM32CubeMX configuration for the transmitter |
| `model_ids_v4_delta (1).tflite` | Supplied TensorFlow Lite model |
| `can_dataset_v4_with_delta.csv` | Labeled CAN dataset |

Both firmware folders contain their original STM32 HAL/CMSIS dependencies, startup code, linker scripts, IDE settings, and `Debug/` output directories.

## Hardware and connections

The project uses an STM32F103C8T6 board, an STM32F411CEU6 Black Pill board, an MCP2515 CAN interface, a CAN transceiver for the STM32F103 node, an ST-Link programmer, and a USB-to-UART adapter for viewing the receiver output. The two CAN interfaces share a CAN bus and ground.

The following pin assignments come from the supplied firmware and peripheral initialization files.

### STM32F103 transmitter

| Pin | Function |
| --- | --- |
| PA11 | CAN RX, connected to the transceiver RXD output |
| PA12 | CAN TX, connected to the transceiver TXD input |
| PC13 | Activity LED toggled by the main loop |

The project configures a 72 MHz system clock and a 36 MHz APB1 clock. CAN uses prescaler 4, BS1 = 15 TQ, and BS2 = 2 TQ, corresponding to 500 kbit/s.

### STM32F411 receiver

| Pin | Function | Connection |
| --- | --- | --- |
| PA5 | SPI1 SCK | MCP2515 SCK |
| PA6 | SPI1 MISO | MCP2515 SO |
| PA7 | SPI1 MOSI | MCP2515 SI |
| PA4 | Chip select | MCP2515 CS |
| PA3 | Active-low interrupt input | MCP2515 INT |
| PA9 | USART1 TX | USB-to-UART adapter RX |
| PA10 | USART1 RX | USB-to-UART adapter TX, if used |

The receiver configures a 100 MHz system clock. UART is **115200 baud, 8 data bits, no parity, 1 stop bit**. MCP2515 timing registers are written directly as `CNF1 = 0x00`, `CNF2 = 0x90`, and `CNF3 = 0x02`; their resulting bitrate depends on the module's oscillator. Confirm that the actual module timing matches the transmitter.

## How the firmware works

1. The transmitter initializes its built-in CAN controller and sends eight-byte data frames according to the selected scenario.
2. The receiver initializes SPI1, USART1, the MCP2515, and the generated AI network.
3. The receiver polls PA3. When the MCP2515 reports data in RXB0, the firmware reads the frame registers.
4. The firmware extracts the identifier and eight payload bytes, normalizes those values, and passes its input buffer to the network.
5. It selects the largest of the three network outputs, prints the corresponding label and score, and clears the RXB0 interrupt flag.

The receiver prints startup messages such as `Node B Ready!` and `AI Core Started!`. Classification lines use this format:

```text
ID:0x<identifier> | <class> | Prob:<score>%
```

The displayed percentage is the largest network output multiplied by 100 and converted to an integer.

## Traffic scenarios

`CHEDO_TEST` in `node1/Core/Src/main.c` selects a scenario at compile time. Its supplied value is **1**.

| Value | Implemented behavior | Delay between send attempts |
| --- | --- | --- |
| `0` | Alternates identifiers `0x103` and `0x030`; generates small changing payload values | 100 ms |
| `1` | Assigns `0x999` to `TxHeader.StdId`; generates random payload bytes | 200 ms |
| `2` | Uses identifier `0x103` with payload values from 200 to 254 | 150 ms |
| `3` | Uses identifier `0x000` with eight `0xFF` bytes | 5 ms |

The original comments also describe mode `4`, but the supplied switch statement only implements modes `0` through `3`. Mode `1` assigns `0x999` while `CAN_ID_STD` is selected; this exceeds the 11-bit standard identifier range, so it should not be treated as a verified on-bus identifier. The original assignment is preserved.

## AI model and dataset

The generated network declares **10 float inputs** and **3 float outputs**. Its dense layers have widths 32, 16, and 3. The included generation report lists 931 parameters, 3,724 bytes of weights, 192 bytes of activation memory, and 1,024 MACC operations. These are model-generation figures, not measured end-to-end throughput or detection accuracy.

The firmware maps output indices as follows:

| Index | Printed label |
| --- | --- |
| `0` | `DoS ATTACK` |
| `1` | `NORMAL` |
| `2` | `SPOOFING` |

The CSV contains **8,665 rows**:

| Label | Rows |
| --- | --- |
| Normal | 3,695 |
| Spoofing | 2,553 |
| DoS | 2,417 |

Its columns are `Timestamp`, `ID`, `DLC`, `Data0` through `Data7`, `Label`, and `Delta_Time`.

The receiver contains Min-Max normalization arrays with ten entries. The identifier range is 1,000, each payload-byte range is 255, and the tenth range is 6,743; all minima are zero. **The supplied inference loop only assigns the first nine inputs: the identifier and eight payload bytes.** It updates `last_msg_time` but does not compute or write a `Delta_Time` feature into the tenth input. Because the input array is global, its untouched tenth element remains zero. This difference between the model interface and the preprocessing code is retained as supplied.

The archive includes the model and generated inference code, but no training script, notebook, evaluation script, or measured accuracy results.

## Open, build, and flash

### Development environment

Use STM32CubeIDE with its Arm GNU toolchain and ST-Link support. The supplied project metadata records:

| Component | Recorded version |
| --- | --- |
| STM32CubeMX | 6.15.0 |
| STM32Cube firmware package for F1 | 1.8.6 |
| STM32Cube firmware package for F4 | 1.28.0 |
| X-CUBE-AI | 10.2.0 |
| ST Edge AI Core in the generation report | 2.2.0 |

The original AI runtime library is included at `blackpill/Middlewares/ST/AI/Lib/NetworkRuntime1020_CM4_GCC.a`.

### Build procedure

1. Clone or download this repository.
2. In STM32CubeIDE, choose **File > Import > General > Existing Projects into Workspace**.
3. Select the repository directory, search its subdirectories, and import `blackpill` and `node1`.
4. Build each project using its **Debug** configuration.
5. Connect the corresponding board through ST-Link and flash each project using its debug/run configuration.
6. Open the receiver's serial port at **115200, 8-N-1** and observe its startup and classification output.

To select another implemented traffic scenario, change `CHEDO_TEST` locally, rebuild `node1`, and flash that board again. The repository retains the original value.

The supplied `Debug/` folders contain existing ELF files, object files, and generated makefiles. These are the original build outputs; they are not evidence of a new build or hardware test.

### Existing machine-specific paths

The original IDE, debug, build, and AI configuration files retain paths from the development computer. In particular, the AI configuration refers to a model named `model_ids_v4_delta.tflite` at an absolute Windows path, while the supplied file at the repository root is named `model_ids_v4_delta (1).tflite`. If regenerating AI code, point the configuration to the supplied model on your own machine. Review local debug/programmer paths when importing the projects.

## Scope of this snapshot

This is the supplied embedded prototype. Its receiver classifies frames and reports results over UART; it does not implement a GUI or active traffic blocking. Build success, physical CAN communication, model accuracy, and timing must be evaluated with the original development environment and hardware. No source-code fixes, additional features, training utilities, or automated tests have been added.

Existing STMicroelectronics, CMSIS, X-CUBE-AI, and Microchip notices and license files remain with their respective components.
