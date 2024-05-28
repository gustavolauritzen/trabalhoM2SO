#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static pthread_mutex_t usando_contagem = PTHREAD_MUTEX_INITIALIZER;


#define tam_vet 1000000 // Alterar tamanho do vetor aqui
#define MAX_BUFFER_SIZE 100000000

int cont_itens;
int *hist_peso;

void *esteira1()
{
    while (1)
    {
       usleep(1000000);

        pthread_mutex_lock(&usando_contagem);
        if (cont_itens < tam_vet) {
            cont_itens++;
            hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 5;
        }
        else{
            pthread_mutex_unlock(&usando_contagem);
            return NULL;
        }
        pthread_mutex_unlock(&usando_contagem);
    }
}

void *esteira2()
{
    while (1)
    {
       usleep(500000);

        pthread_mutex_lock(&usando_contagem);
        if (cont_itens < tam_vet)
        {
            cont_itens++;
            hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 2;
        }
        else{
            pthread_mutex_unlock(&usando_contagem);
            return NULL;
        }
        pthread_mutex_unlock(&usando_contagem);
    }
}

void *esteira3()
{
    while (1)
    {
        usleep(250000);

        pthread_mutex_lock(&usando_contagem);
        if (cont_itens < tam_vet) {
            cont_itens++;
            hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 1;
        }
        else{
            pthread_mutex_unlock(&usando_contagem);
            return NULL;
        }
        pthread_mutex_unlock(&usando_contagem);
    }
}

void *esteira4()
{
    while (1)
    {
       usleep(1500000);

        pthread_mutex_lock(&usando_contagem);
        if (cont_itens < tam_vet) {
            cont_itens++;
            hist_peso[cont_itens] = hist_peso[cont_itens - 1] + 8;
        }
        else{
            pthread_mutex_unlock(&usando_contagem);
            return NULL;
        }
        pthread_mutex_unlock(&usando_contagem);
    }
}

void *display()
{
    char *buffer = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
    int offset = 0;
    if (buffer == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para o buffer\n");
        return NULL;
    }
    
    while (1)
    {
        usleep(1000000);
        pthread_mutex_lock(&usando_contagem);
        offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, "--MONITORAMENTO DA ESTEIRA--\n\n");
        for (int i = 0; i <= cont_itens; i++)
        {
            offset += snprintf(buffer + offset, MAX_BUFFER_SIZE - offset, "Quantidade: %d    Peso: %d\n", i, hist_peso[i]);
            if (offset >= MAX_BUFFER_SIZE) {
                fprintf(stderr, "Buffer overflow\n");
                break;
            }
        }
        if(cont_itens >= tam_vet)
        {
            pthread_mutex_unlock(&usando_contagem);
            printf("%s", buffer);
            return NULL;
        }
        
        pthread_mutex_unlock(&usando_contagem);
        printf("%s", buffer);
    }
}

int main()
{
    pthread_t e1, e2, e3, e4, dis;
    cont_itens = 0;

    hist_peso = malloc(tam_vet * sizeof(int));
    if (hist_peso == NULL)
    {
        fprintf(stderr, "Erro ao alocar memoria\n");
        return 1;
    }

    hist_peso[0] = 0;

    pthread_create(&e1, NULL, esteira1, NULL);
    pthread_create(&e2, NULL, esteira2, NULL);
    pthread_create(&e3, NULL, esteira3, NULL);
    pthread_create(&e4, NULL, esteira4, NULL);
    pthread_create(&dis, NULL, display, NULL);

    pthread_join(e1, NULL);
    pthread_join(e2, NULL);
    pthread_join(e3, NULL);
    pthread_join(e4, NULL);
    pthread_join(dis, NULL);

    free(hist_peso);

    return 0;
}