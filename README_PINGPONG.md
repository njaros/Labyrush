# pingpong  

This program used to do a link between 2 others programs 'a' and 'b' following those rules :  
-	'b' can have [options] but 'a' can't  
-	pingpong has to be executed like this : ./pingpong + path_to_a + path_to_b + [b options]  
-	to talk to 'b', 'a' has to write in stdout, same for the other way  
-	to listen to 'b', 'a' has to listen to stdin, same for the other way  

# task to do : 
-	signal handler to kill and avoid zomby process

# exemple :

command "make" will create the pingpong binary + 2 binaries "ping" and "pong" to test the program.  

then command "sh script" does exactly the test "./pingpong ping pong"  

Test succeed if terminal output become :  
pingpong : ping start  
pingpong : pong start  
ping : I'm alive !  
pong : Me too !  
pong : ping said to me PING!   
ping : pong said to me PONG!  
pong : ping said to me PING!  
ping : pong said to me PONG!  
pong : ping said to me PING!  
...  
