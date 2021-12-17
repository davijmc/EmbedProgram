# EmbedProgram
Projeto desenvolvido para validar a nota dinal das disciplinas de laboratório e teórica de programação embarcada (ECOP14 e ECOP04).
Autor: Davi José Moreira Cunha

-O programa funciona como um jogo onde a partir da placa PQDB você controla um foguete,
com as teclas do teclado "1,2,3,4,5", representadas por "U,L,D,R,S" respectivamente no programa, você consegue simular alguns comandos:
 * Quando a tecla "U" for acionada, com o foguete no solo, a combustão inicia;
 * Quando a tecla "U" for acionada, após o lançamento, o paraquedas abre;
 * Quando a tecla "L" for acionada, a velocidade aumenta em 50m/s com o limite de 450m/s, usando o combustível de manobra e desde que o foguete não tenha alcançado 1500m de altitude;
 * Quando a tecla "D" for acionada, a velocidade reduz em 50m/s, usando o combustível de manobra;
 * Quando a tecla "R" for acionada, a velocidade reduz em 3m/s, usando o combustível de manobra;
 * Quando a tecla "S" for acionada, simula uma falha simples;
 
-O simulador tem algumas informações de status:
 * Altitude do foguete, exibida no LCD como H:'altitude em metros' e atualizada cada segundo sendo que a partir do estagio 2 ela diminui em 10m e em 50m se a velocidade for menor do que 50m/s
 * Estagio do voo, exibido no display de 7 segmentos como "E:(0=parado, 1=combustível principal sendo queimado(duração de 3s), 2=fim da queima de combustível principal, 3=paraquedas abre, 4=foguete pousou com sucesso)"
 * Velociade exibida em m/s no lcd
 * O RGB indica se ocorreu uma falha e o grau da falha (verde=ok, amarelo=falha simples, vermelho=falha grave)
 * Quando o motor ou paraquedas tenta abrir liga um LED pisca;
 
-Casos de falha:
 * Tecla "S" é pressionada;
 * Velocidade menor do que 45m/s enquanto o combustível principal ainda está queimando;
 * Altitude menor do 30m após a queima do combustível principal e sem o paraquedas aberto;
 * O paraquedas abre enquanto ou não se passaram 5 segundos ou a velocidade é maior do que 5m/s ou a altitude é maior do que 1000m;

-O codigo só executa comandos se não houver falha!
-Para ganhar, deve conseguir alcançar o estagio 4 sem falhas!
-Ressalvas: clock utilizado na placa = 40MHz, velocidade computada somente enquanto o foguete se afasta ou tenta se afastar do ponto de lançamento.
