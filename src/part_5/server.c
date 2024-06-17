#include <fcgi_stdio.h>
#include <stdlib.h>

int main() {
  FCGX_Init();
  int sockfd = FCGX_OpenSocket("127.0.0.1:8080", 100);
  FCGX_Request request;
  FCGX_InitRequest(&request, sockfd, 0);

  while (FCGX_Accept_r(&request) >= 0) {
    FCGX_FPrintF(request.out, "Content-Type: text/html\n\n");
    FCGX_FPrintF(request.out, "<html><head><title>Hello World!</title></head>");
    FCGX_FPrintF(request.out, "<body><h1>Hello World!</h1></body></html>");
    FCGX_Finish_r(&request);
  }

  return 0;
}