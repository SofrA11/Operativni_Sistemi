/*Napisati program na C-u koji simulira problem proizvođač/potrošač korišćenjem datavoda. 
Glavni program se deli u dva procesa. Prvi proces (proizvođač) kreira N slučajnih pozitivnih celih brojeva i šalje ih drugom procesu. 
Broj N unosi korisnik sa tastature. Po završetku slanja, prvi proces šalje -1 kao kod za kraj.
 Drugi proces (potrošač) preuzima poslate brojeve iz datavoda i upisuje ih u datoteku tmp.txt. */
 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//Kreiranje datavoda
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PIPE_BUF_SIZE 100

void producer(int n, int write_fd) {
    // Simulacija proizvođača
    for (int i = 0; i < n; ++i) {
        int random_number = rand() % 100; // Generisanje slučajnog broja
        write(write_fd, &random_number, sizeof(random_number));
    }

    // Slanje -1 kao kod za kraj
    int end_signal = -1;
    write(write_fd, &end_signal, sizeof(end_signal));

    // Zatvaranje datavoda za pisanje
    close(write_fd);
}

void consumer(int read_fd) {
    // Otvori datoteku za pisanje
    FILE *output_file = fopen("tmp.txt", "w");
    if (output_file == NULL) {
        perror("Unable to open tmp.txt for writing");
        exit(EXIT_FAILURE);
    }

    // Simulacija potrošača
    int received_number;
    while (read(read_fd, &received_number, sizeof(received_number)) > 0) {
        if (received_number == -1) {
            // Kraj signala
            break;
        }
        // Upis broja u datoteku
        fprintf(output_file, "%d\n", received_number);
    }

    // Zatvaranje datavoda za čitanje i datoteke
    close(read_fd);
    fclose(output_file);
}

int main() {
    int pipe_fd[2];

    // Kreiranje datavoda
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Unos broja N od strane korisnika
    int n;
    printf("Unesite broj N: ");
    scanf("%d", &n);

    // Fork za stvaranje procesa proizvođača i potrošača
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        // Proces dete (proizvođač)
        close(pipe_fd[0]); // Zatvori čitanje
        producer(n, pipe_fd[1]);
        exit(EXIT_SUCCESS);
    } else {
        // Proces roditelj (potrošač)
        close(pipe_fd[1]); // Zatvori pisanje
        consumer(pipe_fd[0]);

        // Čekanje na završetak detetovog procesa
        wait(NULL);

        printf("Izvrseno\n");  // Pomereno ispisivanje izvan bloka čekanja
        exit(EXIT_SUCCESS);
    }

    return 0;
}

