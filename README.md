# file client-server
Fake ftp client-server

## Build
```bash
git clone https://github.com/vladimirfilosof/file-client-server.git
cd file-client-server/build
make
```

## Using server
```bash
./server
```

## Using client
```bash
./client server-ip command [path/to/file] [dir/on/server]
```

Now supporting theese commands:
sendfile path/to/file [dir/on/server]

