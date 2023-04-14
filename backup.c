
int init(){
    printf("init()\n");
    int sd;
    struct sockaddr_in server_addr;
    struct hostent *hp;

// 1.-Create socket for client
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0){
            perror("Error in socket");
            exit(1);
    }
    char *ip;
    char *portEnv;
    ip = getenv("IP_TUPLAS");
    if (ip == NULL){
            perror("IP_TUPLAS not found\n");
            exit(1);
    }
    hp = gethostbyname (ip);
    portEnv = getenv("PORT_TUPLAS");
    if (portEnv == NULL){
            perror("PORT_TUPLAS not found\n");
            exit(1);
    }
    int port = atoi(portEnv);
    printf("Env read, ip: %s, port: %d\n", ip, port);


// Obtain Server address 
    bzero((char *)&server_addr, sizeof(server_addr));
    //gethostbyname() is used to obtain the IP address of the hostname of the server, which in this case would be localhost
    //gethostname obtains the the name of current host instead

    /*
    struct hostent {
            char    *h_name;        // official name of host
            char    **h_aliases;    // alias list
            int     h_addrtype;     // host address type
            int     h_length;       // length of address
            char    **h_addr_list;  // list of addresses
    }*/
    if (hp == NULL) {
            perror("Error en gethostbyname");
            exit(1);
    }

    /*
    struct sockaddr_in {
            short   sin_family;
            u_short sin_port;
            struct  in_addr sin_addr; this determines the IP address
            char    sin_zero[8];
    };*/
memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = AF_INET;
    //htons converts a port number in host byte order to a port number in network byte order
    server_addr.sin_port = htons(port);

// Complete.....
//2.- Connect to the server
    printf("Connecting to server...\n");
    if (connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr))<0){
            perror("Error in connect");
            exit(1);
    }
    printf("Connected to server\n");

//void parseRequest(char *buf, int *request_op, int *request_key, int *request_key2, char *request_value1, int *request_value2, double *request_value3) {
//receives a string like: "2,3,5,hello,5,2.5" 6 tokens
    char buf[MAX];
    strcpy(buf, "0");   
    if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
        perror("Error sending message");
        exit(1);
    }
    printf("enviado: %s\n", buf);
    //receive message from server using recvMessage
//        if (recvMessage(sd, buf, MAX_LINE) < 0) {
//         perror("Error receiving message"); 
//        exit(1);
    //}
    //printf("recibido: %s\n", buf);
    //receive reply from, the server using readLine
    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        exit(1);
    }
    printf("recibido: %s\n", buf);
    //close socket

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 1){
        return 1;
    }
    return(0);

    }




int initialize_socket(char *ip, int port) {
    
    int sd;
    struct sockaddr_in server_addr;
    struct hostent *hp;

    // 1.-Create socket for client
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sd < 0){
        perror("Error in socket");
        exit(1);
    }

    hp = gethostbyname(ip);
    if (hp == NULL) {
        perror("Error en gethostbyname");
        exit(1);
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    //2.- Connect to the server
    printf("Connecting to server...\n");
    if (connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Error in connect");
        exit(1);
    }
    printf("Connected to server\n");

    return sd;
}

int getIpPort(char ** ip, int * port) {

    char *portEnv;

    *ip = getenv("IP_TUPLAS");
    if (*ip == NULL){
        perror("IP_TUPLAS not found\n");
        exit(1);
    }

    
    portEnv = getenv("PORT_TUPLAS");
    if (portEnv == NULL){
        perror("PORT_TUPLAS not found\n");
        exit(1);
    }
    
    printf("portEnv: %s\n", portEnv);
    
    *port = atoi(portEnv);
    printf("Env read, ip: %s, port: %d\n", *ip, *port);
}



int init(){
    printf("init()\n");
    int sd;
    struct sockaddr_in server_addr;
    struct hostent *hp;
    char *ip;
    int port;
    char buf[MAX];

    
    getIpPort(&ip, &port);
    
    sd = initialize_socket(ip, port);


    strcpy(buf, "0");   
    if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
        perror("Error sending message");
        exit(1);
    }
    printf("enviado: %s\n", buf);
    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        exit(1);
    }
    printf("recibido: %s\n", buf);
    //close socket

    close(sd);
    // now inside buf contains the reply from the server sth like "1,3,a,5"?
    parseReply(buf, &reply_success, &reply_value1, &reply_value2, &reply_value3);
    if (reply_success == 1){
        return 1;
    }
    return(0);

    }




        getIpPort(&ip, &port);
    sd = initialize_socket(ip, port);


    sprintf(buf, "1,%d,%s,%d,%f", key, value1, value2, value3);
    if (sendMessage(sd, buf, sizeof(buf)+1) < 0) {
        perror("Error sending message");
        exit(1);
    }
    printf("enviado: %s\n", buf);

    if(readLine(sd, buf, MAX) < 0){
        perror("Error receiving message");
        exit(1);
    }
