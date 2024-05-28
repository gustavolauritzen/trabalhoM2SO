import threading
import time

# Tamanho do vetor e tamanho máximo do buffer
tam_vet = 1000
MAX_BUFFER_SIZE = 100000000

cont_itens = 0
hist_peso = [0] * tam_vet
usando_contagem = threading.Lock()

def esteira1():
    global cont_itens, hist_peso
    while True:
        time.sleep(1)  # 1 segundo
        with usando_contagem:
            if cont_itens < tam_vet - 1:
                cont_itens += 1
                hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 5
            else:
                return

def esteira2():
    global cont_itens, hist_peso
    while True:
        time.sleep(0.5)  # 500 milissegundos
        with usando_contagem:
            if cont_itens < tam_vet - 1:
                cont_itens += 1
                hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 2
            else:
                return

def esteira3():
    global cont_itens, hist_peso
    while True:
        time.sleep(0.25)  # 250 milissegundos
        with usando_contagem:
            if cont_itens < tam_vet - 1:
                cont_itens += 1
                hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 1
            else:
                return

def esteira4():
    global cont_itens, hist_peso
    while True:
        time.sleep(1.5)  # 1.5 segundos
        with usando_contagem:
            if cont_itens < tam_vet - 1:
                cont_itens += 1
                hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 8
            else:
                return

def display():
    global cont_itens, hist_peso
    buffer = []
    while True:
        time.sleep(1)  # 1 segundo
        with usando_contagem:
            buffer.clear()
            buffer.append("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n")
            buffer.append("--MONITORAMENTO DA ESTEIRA--\n\n")
            for i in range(cont_itens + 1):
                buffer.append(f"Quantidade: {i}    Peso: {hist_peso[i]}\n")
                if sum(len(line) for line in buffer) >= MAX_BUFFER_SIZE:
                    print("Buffer overflow")
                    break
            if cont_itens >= tam_vet - 1:
                print("".join(buffer))
                return
        print("".join(buffer))

# Criação das threads
threads = []
threads.append(threading.Thread(target=esteira1))
threads.append(threading.Thread(target=esteira2))
threads.append(threading.Thread(target=esteira3))
threads.append(threading.Thread(target=esteira4))
threads.append(threading.Thread(target=display))

# Inicialização das threads
for t in threads:
    t.start()

# Esperar as threads terminarem
for t in threads:
    t.join()
