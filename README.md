# Interative Environment

_The following project was created for writ105CD_

- The project is an interactive simulated environmnet whereby one can explore different linux-terminal-based programs
- The project is Ubuntu Based

**How to Run**
- If you have WSL or a linux OS, then you can run git clone or fork in order to pull the code
```
git clone https://github.com/LilNemo8/writ105.git
```
- This simulation has a lot of dependencies, so I wrote a bash script that will checks and download them all
- In the linux terminal type *chmod +x depend.sh* and then *. depend.sh*
```
chmod +x depend.sh
. depend.sh
```

- if it prompts for a password, enter your password or press enter (if you password)
- if successful, the bash script will prompt you to run the following

```
All done!
To run the simulation, try:
  ./manager
```
Then just type *./manager*
```
./manager
```


- After this the code should run and you can begin to play


**Deepseek**

- Please note that deepseek does not work out the box. In order to get it to run it must be downloaed seperately
- Therefore in the same terminal type the following *curl -fsSL https://ollama.com/install.sh | sh*

```
curl -fsSL https://ollama.com/install.sh | sh
```

- Now go to https://ollama.com/library/deepseek-r1
- Here you can find the models, run the following *ollama run deepseek-r1:1.5b*

```
ollama run deepseek-r1:1.5b
```

- This should download the model that is specific to this project.
- If you wish to run a higher model then run the same command but with the updated parameter (replace '#' with specific model)

```
ollama run deepseek-r1:#b 
```

- After go to deepseek.cpp and update the following based on the new model you chose
- Make sure to match the parameter
```
execlp("ollama", "ollama", "run", "deepseek-r1:1.5b", (char *)NULL);
to
execlp("ollama", "ollama", "run", "deepseek-r1:#b", (char *)NULL);  (# represents the model)
```

- If you do decided to change or modify the code in any way make sure to run
```
make
```
- This will recomplie the code and make sure that your changes were put into actions 
- Then to play the simulation run this again

```
./manager
```
