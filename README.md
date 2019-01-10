# virustotalcpp

Analyze single files with the help of the virustotal API and c++.
The program computes the sha256 hash of the specified file and, alongside with your API key, queries the virustotal knowledge base
to check if the file has been detected previously as malicious.

## Usage

Malicious file

```
$ ./virustotalcpp <file> <api-key>
[*] Hashing vip.exe: <file size> bytes
[*] Sending data.
[+] Scan rate: <0-100 rate>
[+] First time the file was scanned: <date>
[+] AVs usedd
        [+] <AV name>
         ---> detected: [true|false]
         ---> result: <Variant name>
         ---> update: <AV knowledge base>
         ---> version: <AV version>
        ...
```

Benign file or it hasn't been scanned

```
[*] Hashing virustotalcpp: 39808 bytes
[*] Sending data.
[+] File hash: <file hash>
[+] Message: The requested resource is not among the finished, queued or pending scans
```
