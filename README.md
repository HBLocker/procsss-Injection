# Procsess injection
idea is that it detects a VM and wont inject process with shell code. 
Still in Progress:

Needs to detect AMD and intel at runtime if detected it will run otherwise ti will not run. 

I wanted to play around with the idea of how on some level malware works and how it. 
- A How on a broad level does nmalware into procsesses?
- B How it can detect hardwware types and not run if we think about for example Stuxnet.

##### This is very basic example of how this works. As I really wanted to see the broader concepts behind this. 

based form the following:



- Phillip Kemkes.  echniques: Current Use of Virtual Machine Detection Methods. Available: https://www.gdatasoftware.com/blog/2020/05/36068-current-use-of virtual-machine-detection-methods. Last accessed na.

- Predifined Architectures https://sourceforge.net/p/predef/wiki/Architectures/ 



Then the procsess will be added to to auto inject insted of manualy doing it insted of user input:

```bash
gcc -w MyApplicaiton.c -o outfile 
./outfile ProcsessID
````
