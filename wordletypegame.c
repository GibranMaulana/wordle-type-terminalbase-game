#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char* PemilihanSesiJawaban () {
   
   srand(time(NULL));

   char* listJawaban[] = {
      "absen", "asbak", "antik","badai","badut","bagus",
      "bahas","bahan","bahwa","balok","bantu","bapak",
      "baris","batas","batik","beras","biasa","bidan",
      "bisik","butir","canda","catat","celah","cemas",
      "citra","damai","datar","debut","dekat","denda",
      "darah","dunia","enzim","etika","fakta","fokus",
      "gagal","ganda","garam","gelar","gempa","goyah",
      "hadir","harga","hasil","hujan","iklan","indah",
      "jarak","jenuh","kabar","kadal","kawat","kenal",
      "kolam","kotak","lihat","lidah","macan","mandi",
      "maret","minta","mobil","nanti","nyata","ombak",
      "pahat","pasti","petir","pinus","pulau","ramah",
      "rapat","rehat","rumah","sahur","senam","siang",
      "susun","tanda","tebal","tipis"
   };

   int jumlahListJawaban = sizeof(listJawaban) / sizeof(listJawaban[0]);

   char* sesiJawaban = listJawaban[rand() % jumlahListJawaban];

   return sesiJawaban;
}

void printHeader () {
 
   for (int i = 0; i < 3; i++) {
   
      if (i == 1) {
         
         printf("GAME TEBAK KATA\n");
      
      } else {
         
         for (int j = 0; j < 15; j++) {
      
            printf("=");
      
         }
      
         printf("\n");
      }
   }

      printf("RULES PERMAINAN : \n");
      printf("-PEMAIN HARUS MENEBAK SEBUAH KATA YANG TERDIRI 5 HURUF \n");
      printf("-PEMAIN HANYA BISA MENEBAK KATA SEBANYAK 7 KALI \n");
      printf("-PEMAIN BISA MENEBAK KATA DENGAN PETUNJUK-PETUNJUK YANG MUNCUL DI TERMINAL SETELAH PEMAIN MEMASUKKAN KATA TEBAKAN PERTAMA\n");
      printf("-KETERANGAN :\n");
      printf("V => HURUF ADA DI JAWABAN DAN LETAK NYA SUDAH TEPAT\n");
      printf("! => HURUF ADA DI JAWABAN TAPI LETAKNYA MASIH SALAH\n");
      printf(". => HURUF TIDAK ADA DIJAWABAN\n");
      printf("SELAMAT BERMAIN\n");
      
}

char* inputDanPemvalidasianInput () {

   char* tebakkanUser = (char*)malloc(100 * sizeof(char));

   while(1) {

      printf("masukkan 5 huruf kata : ");
   
      fgets(tebakkanUser, 7, stdin);
   
      tebakkanUser[strcspn(tebakkanUser, "\n")] = 0;
   
      if (strlen(tebakkanUser) == 5) {
         
         return tebakkanUser;
      
      } else if (strlen(tebakkanUser) < 5) {

         printf("inputan tidak valid! coba lagi\n\n");

      }else {
      
         printf("inputan tidak valid! coba lagi\n\n");
         int c;
         while ((c = getchar()) != '\n' && c != EOF);
      }
   }
}

int prosesPengecekan (char* jawaban, char* tebakkanUser) {

   char pengecekanJawaban[6];
   strncpy(pengecekanJawaban, jawaban, 5);
   pengecekanJawaban[5] = '\0';

   char kondisi[] = {'.', '.', '.', '.', '.'};

   for (int i = 0; i < 5; i++) {
      
      if (pengecekanJawaban[i] == tebakkanUser[i]) {

         kondisi[i] = 'V';
         pengecekanJawaban[i] = '-';
      }
   }

   for (int i = 0; i < 5; i++) {
   
      if (kondisi[i] != 'V') {

         for (int j = 0; j < 5; j++) {

            if (tebakkanUser[i] == pengecekanJawaban[j]) {

               kondisi[i] = '!'; 
               pengecekanJawaban[j] = '-';
               break;
            }
         }
      }
   }

   for (int i = 0; i < 5; i++) {

      printf("%c", kondisi[i]);
      fflush(stdout);
      usleep(500000);
   }

   printf("\n\n");

   if (strcmp(jawaban, tebakkanUser) == 0) {
      
      return 1;
   
   } else {

      return 0;
   }
}

int ngecekCharacterAdaDiString (char hurufDiTebakkan, char* jawaban) {

   int status = 0;

   for (int i = 0; i < 5; i++) {

      if (hurufDiTebakkan == jawaban[i]) {

         status = 1;
      }   
   }

   return status;
}

void kondisiKeyboardDanPrintKeyboard (char* tebakkanUser, char keyboard[3][10], char* jawaban) {

   for (int i = 0; i < strlen(tebakkanUser); i++) {
      
      char hurufDiTebakkan = tebakkanUser[i];

      for (int j = 0; j < 3; j++) {

         for (int k = 0; k < 10; k++) {

            if ((ngecekCharacterAdaDiString(hurufDiTebakkan, jawaban) == 0) && hurufDiTebakkan == keyboard[j][k]) {
            
               keyboard[j][k] = '_';
            }
         }
      }
   }  

   for (int i = 0; i < 3; i++) {

      for (int j = 0; j < 10; j++) {

         if (keyboard[i][j] != '\0') {

            printf("%c ", keyboard[i][j]);
         }
      }

      printf("\n");
   }

   printf("\n");

}

void printPenutup () {

   for (int i = 0; i < 3; i++) {

      if (i == 1) {

         printf("TERIMA KASIH SUDAH BERMAIN\n");

      } else {

         for (int j = 0 ; j < 26; j++) {

            printf("=");
         }
         printf("\n");
      }
   }
}

void game () {

   char keinginanUserMengulang;

   do {
      char keyboard [3][10] = {
         {'q', 'w', 'e', 'r', 't','y', 'u', 'i', 'o', 'p'}, 
         {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '\0'}, 
         {'z', 'x', 'c', 'v', 'b', 'n', 'm', '\0', '\0', '\0'}};
      
      printHeader();
      char* jawaban = PemilihanSesiJawaban();

      int jumlahTebakkan = 0;

      while(1) {

         char* tebakkanUser = inputDanPemvalidasianInput();
         printf("%s\n", tebakkanUser);

         if (prosesPengecekan(jawaban, tebakkanUser) == 1) {

            printf("SELAMAT ANDA MENANG || (%s)\n", jawaban);
            free(tebakkanUser);
            break;
         };

         printf("sisa tebakkan (%d)\n", 6 - jumlahTebakkan);

         kondisiKeyboardDanPrintKeyboard(tebakkanUser, keyboard, jawaban);
         jumlahTebakkan++;

         if (jumlahTebakkan >= 7) {

            printf("YAHH ANDA KALAH || (%s)\n", jawaban);
            free(tebakkanUser);
            break;
         }

         free(tebakkanUser);
      }

      printf("RESTAR THE GAME?\n");
      printf("'y' atau 'Y' untuk MENGULANG game (tekan tombol apa saja selain 'y' atau 'Y' untuk KELUAR dari game) => ");
      scanf(" %c", &keinginanUserMengulang);
      int c;
      while ((c = getchar()) != '\n' && c != EOF);

   } while (keinginanUserMengulang == 'y' || keinginanUserMengulang == 'Y');

   printPenutup();
}

int main () {
   
   game();

   return 0;
}