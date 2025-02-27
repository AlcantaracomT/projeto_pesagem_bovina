# **Projeto Final EmbarcaTech**

Bem-vindo ao repositório do **Projeto Final EmbarcaTech**! Este projeto consiste em um sistema embarcado para pesagem e monitoramento automatizado de gado, desenvolvido com foco em eficiência, baixo custo e facilidade de uso para pequenos e médios produtores rurais.

---

## **Descrição do Projeto**

O sistema utiliza um **Raspberry Pi Pico W** como microcontrolador principal, integrando sensores, displays e módulos de comunicação para fornecer uma solução completa de monitoramento de gado. As principais funcionalidades incluem:

- **Pesagem automatizada** utilizando células de carga.
- **Identificação individual** dos bois por meio de tags RFID.
- **Exibição de dados** em tempo real em um display OLED.
- **Feedback visual** com uma matriz de LEDs.
- **Geração de relatórios** mensais sobre o ganho ou perda de peso do rebanho.

---
# **Video**
- **Link**: https://youtu.be/ItTHcmiJkTo?si=a5t1SdoLDZVL2v_M
---
## **Funcionalidades**

- **Monitoramento de Peso**: Mede o peso dos bois e compara com dados anteriores.
- **Identificação por RFID**: Rastreia cada animal individualmente.
- **Interface Gráfica**: Exibe informações no display OLED (ID do boi, peso atual, diferença de peso).
- **Matriz de LEDs**: Mostra a contagem de gado ou status do sistema.
- **Relatórios Mensais**: Gera relatórios consolidados sobre o desempenho do rebanho.

---

## **Tecnologias Utilizadas**

- **Microcontrolador**: Raspberry Pi Pico W.
- **Sensores**: joystick analógico.
- **Display**: OLED SSD1306 (comunicação I2C).
- **Matriz de LEDs**: ssd1306.
- **Linguagem de Programação**: C (usando o SDK da Raspberry Pi).

---

## **Como Executar o Projeto**

### **Pré-requisitos**
- Raspberry Pi Pico W.
- Display OLED SSD1306.
- Matriz de LEDs NeoPixels.
- Ambiente de desenvolvimento configurado (SDK da Raspberry Pi).

### **Passos para Execução**
1. Clone o repositório:
   ```bash
   git clone https://github.com/seu-usuario/ProjetoFinalEmbarcaTech.git
   ```
2. Abra o projeto no seu ambiente de desenvolvimento.
3. Compile o código:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
4. Carregue o firmware no Raspberry Pi Pico W.
5. Conecte os componentes conforme o esquema de hardware.
6. Execute o sistema e interaja com os botões e joystick.
