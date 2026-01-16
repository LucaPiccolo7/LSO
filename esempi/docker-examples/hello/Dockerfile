#separazione build in  due fasi: una fase di compilazione, dove servono librerie ingomgranti anche del SO
#una di runtime, che deve essere lightweight ed includerà solo eseguibile

#si presuppone il filesystem seguente, ed attualmente echo $(pwd) --> /home/luca/Documenti/docker-examples/hello

#/home/luca/Documenti
#└── docker-examples
#    └── hello
#        ├── a.out
#        ├── Dockerfile
#        └── hello.c

#pullo l'immagine più recente di tutto l'SO necessario per la compilazione con gcc
FROM ubuntu:latest AS build

#imposto directory di lavoro dove andranno ad essere eseguiti tutti i comandi
WORKDIR /app

#aggiorno l'SO dall'immagine pullata e scarico gcc
RUN apt update && apt install build-essential -y

#copia il file hello.c dalla working directory dell'HOST (IMPORTANTE!) in /app/hello.c nel FS del container
COPY ./hello.c /app/hello.c

#COMPILA SOLO con gg e crea hello.out all'interno del container
#IMPORTANTE FLAG -static poichè inserisce tutte le librerie nel file oggetto
RUN gcc -static /app/hello.c -o /app/hello.out

#"scratch" è un immagine fantasma vuota molto leggera
#le dimensioni effettive dipenderanno quindi esclusivamente dai file che ci mettiamo noi
FROM scratch

#imposto la directory di lavoro
WORKDIR /app

#come prima, ma al posto di copiare dall'HOST copio dal FS dell'immagine precedente (infatti --from=build)
#--from=build va a vedere lo "stage" precedente, ovvero quello del pull di ubuntu, quindi non la macchina HOST
COPY --from=build /app/hello.out /app/hello.out

#esegue il file hello.out, è importante la notazione ["..."] dove le [] indicano l'esecuzione
CMD ["/app/hello.out"]
