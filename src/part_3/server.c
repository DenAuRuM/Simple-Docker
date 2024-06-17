#include <fcgi_stdio.h>
#include <stdio.h>

int main() {
  while (FCGI_Accept() >= 0) {
      printf("Status: 200 OK\r\n");
      printf("Content-Type: text/html\n\n\r\n");
      printf("<H1>Hello world!</H1>\n");
  }
}